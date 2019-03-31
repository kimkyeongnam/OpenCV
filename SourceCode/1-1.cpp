#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\sejong_small.jpg");
	CvSize size = cvGetSize(img);
	//cvShowImage("original",img);


	//(1) sample1
	IplImage *sample1 = cvCreateImage(size,8,3);
	for(int x=0; x<size.width; x++)
	{
		for(int y=0; y<size.height; y++)
		{
			CvScalar a = cvGet2D(img, y, x);
			cvSet2D(sample1,size.height-1-y,x,a);
		}
	}
	cvShowImage("(1)",sample1);
	cvWaitKey();
	cvReleaseImage(&img);
	cvReleaseImage(&sample1);

	return 0;
}