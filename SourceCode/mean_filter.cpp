#include<opencv2\opencv.hpp>

int main()
{
	IplImage *src = cvLoadImage("c:\\keroro.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);

	int k = 3;
	for (int y = k; y < size.height - k; y++)
		for (int x = k; x < size.width - k; x++)
		{
			CvScalar g = cvScalar(0, 0, 0);
			for (int u = -k; u <= k; u++)
				for (int v = -k; v <= k; v++)
				{
					CvScalar f = cvGet2D(src, y + v, x + u);
					g.val[0] += f.val[0];
					g.val[1] += f.val[1];
					g.val[2] += f.val[2];
				}
			g.val[0] /= ((2 * k + 1)*(2 * k + 1));
			g.val[1] /= ((2 * k + 1)*(2 * k + 1));
			g.val[2] /= ((2 * k + 1)*(2 * k + 1));
			cvSet2D(dst, y, x, g);
		}

	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}