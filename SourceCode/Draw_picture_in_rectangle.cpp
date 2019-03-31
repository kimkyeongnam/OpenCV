#include <opencv2\opencv.hpp>

IplImage * g_src = NULL;
IplImage * g_copy = NULL;
IplImage * g_dst = NULL;

void drawRectangle(IplImage * src, IplImage * dst, CvPoint p1, CvPoint p2)
{
	if(p1.x>p2.x) std::swap(p1.x, p2.x);
	if(p1.y>p2.y) std::swap(p1.y, p2.y);

	int w = p2.x-p1.x;
	int h = p2.y-p1.y;

	for(int x=0; x<w; x++)
		for(int y=0; y<h; y++)
		{
			int x1 = float(x)/w*src->width;
			int y1 = float(y)/h*src->height;
			int x2 = x + p1.x;
			int y2 = y + p1.y;
			if(x1<0 || x1>src->width-1) continue;
			if(y1<0 || y1>src->height-1) continue;
			if(x2<0 || x2>dst->width-1) continue;
			if(y2<0 || y2>dst->height-1) continue;

			CvScalar f = cvGet2D(src, y1, x1);
			cvSet2D(dst, y2, x2, f);
		}

}


void myMouse(int event, int x, int y, int flags, void *)
{
	static CvPoint pt1 = cvPoint(-1, -1);
	if(event == CV_EVENT_LBUTTONDOWN)
	{
		pt1 = cvPoint(x, y);
		cvCopy(g_dst, g_copy);
	}
	else if(event == CV_EVENT_MOUSEMOVE && (flags&CV_EVENT_FLAG_LBUTTON!=0))
	{
		CvPoint pt2 = cvPoint(x,y);
		if(pt1.x<0) return;
		if(pt1.y<0) return;
		if(pt2.x<0) return;
		if(pt2.y<0) return;
		if(pt1.x>g_dst->width-1) return;
		if(pt2.x>g_dst->width-1) return;
		if(pt1.y>g_dst->height-1) return;
		if(pt2.y>g_dst->height-1) return;
				
		cvCopy(g_copy, g_dst);
		drawRectangle(g_src, g_dst, pt1, pt2);
		cvShowImage("dst", g_dst);
	}

}

int main()
{
	g_src = cvLoadImage("lena.png");
	if(g_src == NULL){ printf("Couldn't find the image file"); exit(0);}
	CvSize size = cvGetSize(g_src);

	printf("Example for the final exam:\n");
	printf("Drawing many rectangles with the image:\n");

	g_copy = cvCreateImage(size, 8, 3);
	g_dst = cvCreateImage(size, 8, 3);

	cvSet(g_dst, cvScalar(255,255,255));
	
	cvShowImage("dst", g_dst);
	cvSetMouseCallback("dst", myMouse);
	cvWaitKey();

	return 0;
}