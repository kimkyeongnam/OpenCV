#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\sejong_small.jpg");
	CvSize size = cvGetSize(img);
	//cvShowImage("original",img);


	//(2) sample2
	IplImage *sample2 = cvCreateImage(size,8,3);
	for(int x=0; x<size.width; x++)
	{
		for(int y=0; y<size.height; y++)
		{
			int fx = size.width/2;
			CvScalar b = cvGet2D(img, y,x);
			if(x<fx)
				cvSet2D(sample2, y, fx+x, b);
			else
				cvSet2D(sample2, y, x-fx, b);
		}
	}
	cvShowImage("(2)",sample2);
	cvWaitKey();
	cvReleaseImage(&img);
	cvReleaseImage(&sample1);

	return 0;
}