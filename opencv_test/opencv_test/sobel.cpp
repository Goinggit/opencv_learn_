#include <cv.h>
#include <highgui.h>
#include <iostream>
#pragma comment( lib, "opencv_highgui2410d.lib")
#pragma comment( lib, "opencv_core2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib") 
using namespace cv;

int main()
{
	Mat src, src_gray;
	Mat grad;
	char* window_name = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	/// װ��ͼ��
	src = imread("tiger.jpg");

	if (!src.data)
	{
		return-1;
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);//ddepth: ���ͼ�����ȣ��趨Ϊ CV_16S �������硣

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	Sobel(src,grad_x,ddepth,1,0,3);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(src, grad_y, ddepth, 0, 1, 3);
	/*
	src_gray: �ڱ�����Ϊ����ͼ��Ԫ������ CV_8U
	grad_x/grad_y: ���ͼ��.
	ddepth: ���ͼ�����ȣ��趨Ϊ CV_16S �������硣
	x_order: x �����󵼵Ľ�����
	y_order: y �����󵼵Ľ�����
	scale, delta �� BORDER_DEFAULT: ʹ��Ĭ��ֵ
	*/
	
	convertScaleAbs(grad_y, abs_grad_y);//���м���ת���� CV_8U:


	
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow(window_name, grad);

	waitKey(0);

	return 0;

}