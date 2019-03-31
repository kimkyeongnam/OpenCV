#include <opencv2/opencv.hpp>

IplImage * g_src;
IplImage * g_copy;

int g_size = 50;
CvPoint g_stPt;
CvPoint g_edPt;


void DoMorphing()
{
	float x1, y1, x2, y2;

	float dx = g_edPt.x - g_stPt.x;
	float dy = g_edPt.y - g_stPt.y;

	cvCopy(g_src, g_copy);

	
	for(x1 = g_stPt.x-g_size; x1 <= g_stPt.x+g_size; x1 += 0.1)
		for(y1 = g_stPt.y-g_size; y1 <= g_stPt.y+g_size; y1+= 0.1)
		{
			float dist = sqrt((x1-g_stPt.x)*(x1-g_stPt.x) + (y1-g_stPt.y)*(y1-g_stPt.y));


			float alpha = dist/float(g_size);
			if(alpha>1) continue;
			
			CvScalar f = cvScalar(0,0,0);
			if(x1>=0 && x1<= g_src->width-1 && y1>=0 && y1<=g_src->height-1)
				f = cvGet2D(g_copy, y1, x1);

			float dx2, dy2;

			dx2 = (1-alpha)*dx;
			dy2 = (1-alpha)*dy;

			x2 = x1+dx2;
			y2 = y1+dy2;

			if(x2<0 || x2> g_src->width-1) continue;
			if(y2<0 || y2> g_src->height-1) continue;

			cvSet2D(g_src, y2, x2, f);

		}

}


void myMouse(int events, int x, int y, int flags, void * param)
{
	if(events == CV_EVENT_LBUTTONDOWN)
	{
		g_stPt = cvPoint(x, y);
		cvCopy(g_src, g_copy);

		cvCircle(g_src, g_stPt, g_size, cvScalar(255,0,0), 2);
		cvShowImage("source", g_src);
	}
	else if(events == CV_EVENT_MOUSEMOVE && flags & CV_EVENT_FLAG_LBUTTON)
	{
		g_edPt = cvPoint(x,y);
		cvCopy(g_copy, g_src);
		cvCircle(g_src, g_edPt, g_size, cvScalar(255,0,0), 2);
		cvShowImage("source", g_src);
	}
	else if(events == CV_EVENT_LBUTTONUP)
	{
		g_edPt = cvPoint(x,y);
		cvCopy(g_copy, g_src);

		DoMorphing();
		cvShowImage("source", g_src);
	}




}

int main()
{
	g_src = cvLoadImage("lena.png");
	CvSize size = cvGetSize(g_src);
	g_copy = cvCreateImage(size, 8, 3);

	printf("Example for the final exam:\n");
	printf("Smearing:\n");

	cvCopy(g_src, g_copy);

	cvShowImage("source", g_src);

	cvSetMouseCallback("source", myMouse);

	cvWaitKey();
	cvReleaseImage(&g_src);
	cvReleaseImage(&g_copy);

	return 0;
}

