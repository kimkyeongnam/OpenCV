#include<opencv2\opencv.hpp>

bool myCompare(CvScalar a, CvScalar b)
{
	int bri_a = a.val[0] + a.val[1] + a.val[2];
	int bri_b = b.val[0] + b.val[1] + b.val[2];
	if ((bri_a - bri_b) > 0) return true;
	return false;
}

void mySwap(CvScalar *a, CvScalar *b)
{
	CvScalar temp = *a;
	*a = *b;
	*b = temp;
}

//bool myCompInt(int a, int b)
//{
//	if((a-b>0)) return true;
//	else return false;
//}

void myMedianFilter(IplImage *src, IplImage *dst, int k)
{
	CvSize size = cvGetSize(src);
	int num = (2 * k + 1)*(2 * k + 1);
	CvScalar *f = new CvScalar[num];
	for (int y = k; y < size.height - k; y++)
	{
		for (int x = k; x < size.width - k; x++)
		{
			int count = 0;
			for (int v = -k; v <= k; v++)
				for (int u = -k; u <= k; u++)
				{
					f[count] = cvGet2D(src, y + v, x + u);
					count++;
				}
			//sorting --> ºñ±³,swap
			for (int i = 0; i < num - 1; i++)
				for (int j = i + 1; j < num; j++)
					if (myCompare(f[i], f[j]) == true)
						mySwap(&f[i], &f[j]);
			CvScalar g = f[num / 2];
			cvSet2D(dst, y, x, g);
		}
	}
	delete[] f;
}

int main(void)
{
	IplImage *src = cvLoadImage("c:\\saltpepper.jpg");
	CvSize size = cvGetSize(src);
	IplImage *dst = cvCreateImage(size, 8, 3);

	int k = 1;
	myMedianFilter(src, dst, k);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
	return 0;
}
