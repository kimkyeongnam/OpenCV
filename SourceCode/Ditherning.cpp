#include <opencv2\opencv.hpp>

int main()
{
	printf("Example for the final exam: \n");
	printf("Dithering: \n");

	IplImage * src = cvLoadImage("lena.png");
	CvSize size = cvGetSize(src);
	IplImage * dst = cvCreateImage(size, 8, 3);

	for(int y = 0; y<size.height; y++)
		for(int x = 0; x<size.width; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;
			int bri = (f.val[0]+f.val[1]+f.val[2])/3;
			if(bri>128)
				g = cvScalar(255,255,255);
			else
				g = cvScalar(0,0,0);
			cvSet2D(dst, y, x, g);

			CvScalar d;  // d = f - g;
			for(int k=0; k<3; k++) d.val[k] = f.val[k] - g.val[k];

			CvScalar f1, f2, f3, f4;
			if(x<size.width-1)
			{
				f1 = cvGet2D(src, y, x+1);
				for(int k=0; k<3; k++) 	
					f1.val[k] += d.val[k] * 7/16.0f;
				cvSet2D(src, y, x+1, f1);
			}
			if(x>0 && y<size.height-1)
			{
				f2 = cvGet2D(src, y+1, x-1);
				for(int k=0; k<3; k++) 	
					f2.val[k] += d.val[k] * 3/16.0f;
				cvSet2D(src, y+1, x-1, f2);
			}
			if(y<size.height-1)
			{
				f3 = cvGet2D(src, y+1, x);
				for(int k=0; k<3; k++)  
					f3.val[k] += d.val[k] * 5/16.0f;
				cvSet2D(src, y+1, x, f3);   
			}
			if(x<size.width-1 && y<size.height-1)
			{
				f4 = cvGet2D(src, y+1, x+1);
				for(int k=0; k<3; k++)  
					f4.val[k] += d.val[k] * 1/16.0f;
				cvSet2D(src, y+1, x+1, f4);   
			}
		}

	cvShowImage("dst", dst);
	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return 0;
}