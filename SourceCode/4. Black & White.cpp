#include<opencv2\opencv.hpp>

int main()
{
	IplImage *src = NULL;
	char ar[100] = "";
	while (src == NULL)
	{
		printf("Input Filename:");
		scanf("%s", ar);
		src = cvLoadImage(ar);
		if (src == NULL) printf("File not found!\n");
	}
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);

	int div = 10;
	int h_div = size.height / div;
	int w_div = size.width / div;
	double threshold = 0;

	int **color = (int**)malloc(h_div * sizeof(int*));
	for (int y = 0; y*div<size.height; y++)
		color[y] = (int*)malloc(sizeof(int)*w_div);
	for (int y = 0; y<h_div; y++)
		for (int x = 0; x<w_div; x++)
			color[y][x] = 0;

	int i = 0, j = 0;
	for (int y = 0; y<size.height; y++)
	{
		for (int x = 0; x<size.width; x++)
		{
			CvScalar a = cvGet2D(src, y, x);
			threshold += (a.val[0] + a.val[1] + a.val[2]) / 3;
			if ((x + 1) % w_div == 0)
			{
				color[i][j] += threshold;
				j++;
				threshold = 0;
			}
		}
		if ((y + 1) % h_div == 0) i++;
		j = 0;
	}

	for (int y = 0; y<div; y++)
		for (int x = 0; x < div; x++)
			color[y][x] /= w_div * h_div;

	i = 0, j = 0;
	for (int y = 0; y<size.height; y++)
	{
		for (int x = 0; x<size.width; x++)
		{
			double result;
			result = color[i][j] - 20;
			CvScalar a = cvGet2D(src, y, x);
			CvScalar b;
			int sum = 0;
			sum = (a.val[0] + a.val[1] + a.val[2]) / 3;
			if (result>sum) b = cvScalar(0, 0, 0);
			else b = cvScalar(255, 255, 255);
			cvSet2D(dst, y, x, b);
			if ((x + 1) % w_div == 0) j++;
		}
		if ((y + 1) % h_div == 0) i++;
		j = 0;
	}
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();

	for (int y = 0; y*div<size.height; y++)
		free(color[y]);
	free(color);
	return 0;
}