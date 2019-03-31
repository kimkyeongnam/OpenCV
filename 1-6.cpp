#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\sejong_small.jpg");
	CvSize size = cvGetSize(img);
	//cvShowImage("original",img);

	//(6) sample6
	IplImage *sample6 = cvCreateImage(size,8,3);
	for(int x=0; x<size.width; x++)
	{
		for(int y=0; y<size.height; y++)
		{
			CvScalar k = cvGet2D(img, y, x);
			cvSet2D(sample6, y, x, k);
		}
	}

	for(int wd=0; wd<10; wd++)
	{ 
		float fx=(float)size.width/10;
		float fy=(float)size.height/10;

		for(int x=fx*wd; x<fx*(wd+1); x++)
		{
			int ht;
			if(wd%2==0) ht=0;
			else ht=1;

			for(ht; ht<10; ht+=2)
			{
				for(float y=fy*ht; y<fy*(ht+1); y++)
				{
					CvScalar l = cvScalar(0,0,0);
					cvSet2D(sample6,y,x,l);
				}
			}
		}
	}
	cvShowImage("(6)",sample6);
	cvWaitKey();
	cvReleaseImage(&sample6);

	return 0;
}