#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\sejong_small.jpg");
	CvSize size = cvGetSize(img);
	//cvShowImage("original",img);

	//(5) sample5
	IplImage *sample5 = cvCreateImage(size,8,3);

	for (int x=0; x<size.width; x++)
    {
		for (int y=0; y<size.height; y++)
       {
			float a=size.width/2;
			float b=size.height/2;
			float gapwdh=(float)size.width/20;
			float gaphgt=(float)size.height/20;
			CvScalar h = cvGet2D(img, y, x);

           if (((x-a)*(x-a)/(gapwdh*10*gapwdh*10)+(y-b)*(y-b)/(gaphgt*10*gaphgt*10) > 1)
             && ((x-a)*(x-a)/(gapwdh*11*gapwdh*11)+(y-b)*(y-b)/(gaphgt*11*gaphgt*11) <= 1))
             cvSet2D(sample5, y, x, h);
          if (((x-a)*(x-a)/(gapwdh*12*gapwdh*12)+(y-b)*(y-b)/(gaphgt*12*gaphgt*12) > 1)
             && ((x-a)*(x-a)/(gapwdh*13*gapwdh*13)+(y-b)*(y-b)/(gaphgt*13*gaphgt*13) <= 1))
             cvSet2D(sample5, y, x, h);
       }
    }
	for(int cnt=0; cnt<10; cnt+=2)
	{
		float gapwdh=(float)size.width/20;
		float gaphgt=(float)size.height/20;
		float fx=(float)size.width/2;
		float fy=(float)size.height/2;
		for(int x=gapwdh*cnt; x<size.width; x++)
		{	
			for(int y=gaphgt*cnt; y<size.height; y++)
			{
				float area = (((fx-x)*(fx-x))/((fx-gapwdh*cnt)*(fx-gapwdh*cnt)) + ((fy-y)*(fy-y))/((fy-gaphgt*cnt)*(fy-gaphgt*cnt)));
				if(area<1)
				{
					CvScalar i = cvScalar(0,0,0);
					cvSet2D(sample5, y,x,i);
				}
			}		
		}
		for(int x=gapwdh*(cnt+1); x<size.width-gapwdh*(cnt+1); x++)
		{
			for(int y=gaphgt*(cnt+1); y<size.height-gaphgt*(cnt+1); y++)
			{
				float area = (((fx-x)*(fx-x))/((fx-gapwdh*(cnt+1))*(fx-gapwdh*(cnt+1)))) + (((fy-y)*(fy-y))/((fy-gaphgt*(cnt+1))*(fy-gaphgt*(cnt+1))));
				if(area<1)
				{
					CvScalar j = cvGet2D(img, y, x);
					cvSet2D(sample5, y,x,j);
				}
			}
		}
	}
	cvShowImage("(5)",sample5);


	cvWaitKey();
	cvReleaseImage(&img);
	cvReleaseImage(&sample5);

	return 0;
}