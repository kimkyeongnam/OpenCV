
#include <opencv2\opencv.hpp>

IplImage * g_img;
IplImage * g_buf;

CvPoint g_st;
CvPoint g_ed;
CvPoint g_pivot;

float g_theta = 0;

void rotateImage(IplImage * src, IplImage * dst, float angle)
{
	cvSet(dst, cvScalar(0,0,0));
	for(float x2=0; x2<dst->width; x2++)
		for(float y2=0; y2<dst->height; y2++)
		{
			float x1 = (x2-g_pivot.x)*cos(-angle) - (y2-g_pivot.y)*sin(-angle) + g_pivot.x;
			float y1 = (x2-g_pivot.x)*sin(-angle) + (y2-g_pivot.y)*cos(-angle) + g_pivot.y;

			if(x1<0 || x1>src->width-1) continue;
			if(y1<0 || y1>src->height-1) continue;

			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);

//			cvGet2D와 cvSet2D는 매우 느리므로, 위 두줄 대신 다음 코드를 이용하면 속도를 높일 수 있음
/*
			uchar* ptr1 = (uchar *)(src->imageData) + ((int)y1*src->widthStep + (int)x1*src->nChannels);
			uchar* ptr2 = (uchar *)(dst->imageData) + ((int)y2*dst->widthStep + (int)x2*dst->nChannels);
			ptr2[0] = ptr1[0];
			ptr2[1] = ptr1[1];
			ptr2[2] = ptr1[2];
*/

		}
}

float getRotatingAngle(CvPoint p, CvPoint q, CvPoint pv)
{
	float ax = p.x - pv.x;
	float ay = p.y - pv.y;
	float bx = q.x - pv.x;
	float by = q.y - pv.y;

	float dot_product = ax*bx + ay*by;
	float cross_product = ax*by - ay*bx;

	float angle = atan2(cross_product, dot_product);
	return angle;

//  또는 수업시간에 다룬 다음 코드를 이용해도 됨
/*
	float phi1 = atan2(p.y, p.x);
	float phi2 = atan2(q.y, q.x);

	float angle = phi2-phi1;
	return angle;
*/
}

void myMouse(int event, int x, int y, int flags, void * param)
{
	if(event == CV_EVENT_LBUTTONDOWN)
	{
		g_st = cvPoint(x, y);
	}
	else if(event == CV_EVENT_MOUSEMOVE && (flags&CV_EVENT_FLAG_LBUTTON)!=0)
	{
		g_ed = cvPoint(x,y);

		float dt = getRotatingAngle(g_st, g_ed, g_pivot);
		g_theta += dt;

		rotateImage(g_img, g_buf, g_theta);
		cvShowImage("image", g_buf);

		g_st = g_ed;
	}
}
int main()
{
	printf("Example for the final exam: \n");
	printf("Rotating an Image around its center by using the mouse: \n");

	g_img = cvLoadImage("lena.png");
	g_buf = cvCreateImage(cvGetSize(g_img), 8, 3);

	g_pivot = cvPoint(g_img->width/2, g_img->height/2);
	
	cvShowImage("image", g_img);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	cvReleaseImage(&g_img);
	cvReleaseImage(&g_buf);



	return 0;
}
