#include <opencv2\opencv.hpp>

IplImage * g_img;
IplImage * g_buf;

CvPoint g_pt[100];
int g_num = 0;

void myMouse(int event, int x, int y, int flags, void * param)
{
	if(event == CV_EVENT_LBUTTONDOWN)
	{
		g_pt[g_num] = cvPoint(x,y);
		g_num ++;

		cvCopy(g_img, g_buf);
		for(int i=0; i<g_num; i++)
		{
			cvCircle(g_buf, g_pt[i], 4, cvScalar(0,255,0), -1);
			if(i<g_num-1) cvLine(g_buf, g_pt[i], g_pt[i+1], cvScalar(0,255,0), 1);
		}
		cvShowImage("image", g_buf);
	}
}

int main()
{
	
	printf("Example for the final exam: \n");
	printf("A Simple Keyframing Animator: \n");
	
	g_img = cvLoadImage("lena.png");
	g_buf = cvCreateImage(cvGetSize(g_img), 8, 3);
	
	cvShowImage("image", g_img);
	cvSetMouseCallback("image", myMouse);	// set the mouse callback
	
	cvWaitKey();
	
	cvSetMouseCallback("image", 0);			// unset the mouse callback		

	for(float time = 0; time<g_num-1; time += 0.01)
	{
		cvCopy(g_img, g_buf);
		
		int ind1 = (int) time;
		int ind2 = ind1 + 1;
		if(ind2>g_num-1) ind2 = g_num-1;
		
		float alpha = time - ind1;

		CvPoint pt;
		pt.x = (1-alpha)*g_pt[ind1].x + alpha*g_pt[ind2].x;
		pt.y = (1-alpha)*g_pt[ind1].y + alpha*g_pt[ind2].y;

		cvCircle(g_buf, pt, 10, cvScalar(0,255,0), -1);

		cvShowImage("image", g_buf);
		cvWaitKey(10);
	}
	
	cvWaitKey();

	cvReleaseImage(&g_img);
	cvReleaseImage(&g_buf);

}
