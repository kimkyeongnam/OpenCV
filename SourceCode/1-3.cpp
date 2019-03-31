#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\sejong_small.jpg");
	CvSize size = cvGetSize(img);
	//cvShowImage("original",img);

	//(3) sample3
	IplImage *sample3 = cvCreateImage(size,8,3);
	for(int x=0; x<size.width; x++)
	{
		for(int y=0; y<size.height; y++)
		{
			float fx=(float)size.width/2;
			float fy=(float)size.height/2;

			CvScalar c = cvGet2D(img, y,x);
			if(x<fx&&y<fy) //왼쪽위
			{
				float a=-fy/fx;	
				if(a*x+size.height/2 > y)
				{
					int bri=c.val[0]+c.val[1]+c.val[2];
					CvScalar d = cvScalar(bri/3, bri/3, bri/3);
					cvSet2D(sample3, y, x, d);
				}
				else
					cvSet2D(sample3, y, x, c);
			}
			else if(x>=fx&&y<fy) //오른쪽위
			{
				float a=fy/fx;
				if(a*x-size.height/2 > y)
				{
					int bri=c.val[0]+c.val[1]+c.val[2];
					CvScalar d = cvScalar(bri/3, bri/3, bri/3);
					cvSet2D(sample3, y, x, d);
				}
				else
					cvSet2D(sample3, y, x, c);
			}
			else if(x<fx&&y>=fy) //왼쪽아래
			{
				float a=fy/fx;
				if(a*x+size.height/2 < y)
				{
					int bri=c.val[0]+c.val[1]+c.val[2];
					CvScalar d = cvScalar(bri/3, bri/3, bri/3);
					cvSet2D(sample3, y, x, d);
				}
				else
					cvSet2D(sample3, y, x, c);
			}
			else if(x>=fx&&y>=fy) //오른쪽아래
			{
				float a=(fy-size.height)/(size.width-fx);
				if(a*x+(size.height/2)+size.height < y)
				{
					int bri=c.val[0]+c.val[1]+c.val[2];
					CvScalar d = cvScalar(bri/3, bri/3, bri/3);
					cvSet2D(sample3, y, x, d);
				}
				else
					cvSet2D(sample3, y, x, c);
			}
		}
	}
	cvShowImage("(3)", sample3);


	
	cvWaitKey();
	cvReleaseImage(&img);
	cvReleaseImage(&sample3);

	return 0;
}