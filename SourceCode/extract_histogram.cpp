#include<opencv2\opencv.hpp>
#include<math.h>

void computeHistorgam(IplImage *src, int h[][256])
{
	CvSize size = cvGetSize(src);

	for (int k = 0; k < 3; k++)
		for (int i = 0; i < 256; i++)
			h[k][i] = 0;

	for (int k = 0; k < 3; k++)
		for (int x = 0; x < size.width; x++)
			for (int y = 0; y < size.height; y++)
			{
				CvScalar g = cvGet2D(src, y, x);
				h[0][int(g.val[0])]++;
				h[1][int(g.val[1])]++;
				h[2][int(g.val[2])]++;
			}
}

void drawHistorgam(int h[][256])
{
	IplImage *g = cvCreateImage(cvSize(256, 300), 8, 3);
	cvSet(g, cvScalar(0, 0, 0));
	int max = 0;
	for (int k = 0; k < 3; k++)
		for (int i = 0; i < 256; i++)
			if (h[k][i] > max) max = h[k][i];

	for (int x = 0; x < 256; x++)
	{
		for (int k = 0; k < 3; k++)
		{
			CvScalar c = cvScalar(0, 0, 0);
			c.val[k] = 255;
			int v = h[k][x] / float(max) * 300;
			for (int y = 0; y < v; y++)
				cvSet2D(g, 299 - y, x, c);
		}
	}
	cvShowImage("histo", g);
	cvWaitKey();
}

void histogramEq(IplImage *src, IplImage *dst)
{
	//1. Compute Historgam
	int histo[3][256];
	computeHistorgam(src, histo);
	drawHistorgam(histo);

	//2. Compute Cumulative Historgam

	//3. Apply Transform function with cumulative histogram
}

int main()
{
	IplImage *src = cvLoadImage("c:\\toodark1.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);

	histogramEq(src, dst);


	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	return 0;
}