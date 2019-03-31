
#include<opencv2\opencv.hpp>

int main(void)
{
	IplImage *img = cvLoadImage("c:\\keroro.jpg");
	CvSize size = cvGetSize(img);
	IplImage *result = cvCreateImage(size, 8, 3);

	for (int x = 0; x < size.width; x++)
	{
		for (int y = 0; y < size.height; y++)
		{
			CvScalar f = cvGet2D(img, y, x);
			int bri = f.val[0] + f.val[1] + f.val[2];
			CvScalar g = cvScalar(bri / 3, bri / 3, bri / 3);
			cvSet2D(result, y, x, g);
		}
	}

	cvShowImage("image", img);
	cvShowImage("result", result);

	cvWaitKey();
	return 0;
}