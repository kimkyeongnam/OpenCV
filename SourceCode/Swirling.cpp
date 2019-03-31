#include <opencv2\opencv.hpp>

int main()
{
	IplImage * src = cvLoadImage("lena.png");
	IplImage * dst = cvCreateImage(cvGetSize(src), 8, 3);

	printf("Example for the final exam: \n");
	printf("A Swirling Image: \n");

	CvPoint center = cvPoint(dst->width/2, dst->height/2);
	
	float angle_range = 0;
	float d_angle = 10;
	while(true)
	{
		cvSet(dst, cvScalar(0,0,0));
		for(float x2=0; x2<dst->width; x2++)
			for(float y2=0; y2<dst->height; y2++)
			{
				// distance from the center;
				float distance = (x2-center.x)*(x2-center.x) 
								+(y2-center.y)*(y2-center.y);
				distance = sqrt(distance);

				float max_distance = dst->width*sqrt(2.0f)/2;
				float angle = (1-distance/max_distance) * angle_range;
				float rad = angle*3.141592/180.0f;
			
				float x1 = cos(-rad)*(x2-center.x) - sin(-rad)*(y2-center.y)+center.x;
				float y1 = sin(-rad)*(x2-center.x) + cos(-rad)*(y2-center.y)+center.y;

				if(x1<0 || x1>src->width-1) continue;
				if(y1<0 || y1>src->height-1) continue;
			
				CvScalar f = cvGet2D(src, y1, x1);
				cvSet2D(dst, y2, x2, f);
			}
		cvShowImage("image", dst);
		
		if(cvWaitKey(30)!=-1) break;

		angle_range += d_angle;
		if(angle_range>360 || angle_range<-360) d_angle = - d_angle;

	}
	return 0;
}