#include <opencv2\opencv.hpp>

CvScalar myGet2D(IplImage * img, float y, float x)
{
	 int i = (int)x;
	 int j = (int)y;
	 float a = x - i;
	 float b = y - j;

	 int i2 = i+1; if(i2>img->width-1) i2 = i;
	 int j2 = j+1; if(j2>img->height-1) j2 = j;
 
	 CvScalar f1 = cvGet2D(img, j, i);
	 CvScalar f2 = cvGet2D(img, j, i2);
	 CvScalar f3 = cvGet2D(img, j2, i);
	 CvScalar f4 = cvGet2D(img, j2, i2);

	 CvScalar f;
	 for(int k=0; k<3; k++)
		  f.val[k] =   (1-a)*(1-b) * f1.val[k]
					+  (a)*(1-b) * f2.val[k]
					+(1-a)*(b)   * f3.val[k]
					+  (a)*(b)   * f4.val[k];
	 return f;
}

int main()
{
	IplImage * src = cvLoadImage("lena.png");
	IplImage * dst = cvCreateImage(cvGetSize(src), 8, 3);

	printf("Example for the final exam: \n");
	printf("A Bilinear Interpolation for magnifying 5 times: \n");

	float scale = 5.0f;

	CvPoint pivot = cvPoint(src->width/2, src->height/2);
	for(float x2=0; x2<dst->width; x2++)
		for(float y2=0; y2<dst->height; y2++)
		{
			float x1 = (x2-pivot.x)/scale + pivot.x;
			float y1 = (y2-pivot.y)/scale + pivot.y;
			
			if(x1<0 || x1>src->width-1) continue;
			if(y1<0 || y1>src->height-1) continue;

			CvScalar f = myGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);
		}

	cvShowImage("image", dst);
	cvWaitKey();

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
}

