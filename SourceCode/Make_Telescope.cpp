#include <opencv2\opencv.hpp>

IplImage * g_img;
IplImage * g_buf;
CvPoint g_pt;
int g_size = 50;

void drawMagnifier(IplImage * img, IplImage * buf, CvPoint pt)
{
	cvCopy(img, buf);

	for(int x2=pt.x-g_size; x2<pt.x+g_size+1; x2++)
		for(int y2=pt.y-g_size; y2<pt.y+g_size+1; y2++)
		{
			if(x2<0 || x2>buf->width-1) continue;
			if(y2<0 || y2>buf->height-1) continue;
			
			float x1 = (x2-pt.x)/2.0f+pt.x;
			float y1 = (y2-pt.y)/2.0f+pt.y;

			if(x1<0 || x1>buf->width-1) continue;
			if(y1<0 || y1>buf->height-1) continue;

			cvSet2D(buf, y2, x2, cvGet2D(img, y1, x1));
		}


}

void myMouse(int event, int x, int y, int flags, void * param)
{
	if(event == CV_EVENT_MOUSEMOVE)
	{
		g_pt = cvPoint(x,y);
		drawMagnifier(g_img, g_buf, g_pt);
		cvShowImage("image", g_buf);
	}
}

int main()
{
	printf("Example for the final exam: \n");
	printf("A Magnifier: \n");

	g_img = cvLoadImage("lena.png");
	g_buf = cvCreateImage(cvGetSize(g_img), 8, 3);

	cvCopy(g_img, g_buf);
	g_pt = cvPoint(g_img->width/2, g_img->height/2);
	
	cvShowImage("image", g_img);
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	cvReleaseImage(&g_img);
	return 0;
}