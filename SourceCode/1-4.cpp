#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\sejong_small.jpg");
	CvSize size = cvGetSize(img);
	//cvShowImage("original",img);

	//(4) sample4
	IplImage *sample4 = cvCreateImage(size,8,3);
	for(int x=0; x<size.width; x++)
	{
		for(int y=0; y<size.height; y++)
		{
			float fx=(float)size.width/2;
			float fy=(float)size.height/2;
			float area = (((fx-x)*(fx-x))/(fx*fx)) + (((fy-y)*(fy-y))/(fy*fy));

			CvScalar e = cvGet2D(img, y,x);
			if(area > 1)
			{
				int bri=e.val[0]+e.val[1]+e.val[2];
				CvScalar f = cvScalar(bri/3, bri/3, bri/3);
				cvSet2D(sample4, y,x,f);
			}
			else
				cvSet2D(sample4, y,x,e);
		}
	}
	cvShowImage("(4)",sample4);


	cvWaitKey();
	cvReleaseImage(&img);
	cvReleaseImage(&sample4);

	return 0;
}