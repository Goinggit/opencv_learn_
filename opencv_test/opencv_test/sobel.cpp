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

	/// 装载图像
	src = imread("tiger.jpg");

	if (!src.data)
	{
		return-1;
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);//ddepth: 输出图像的深度，设定为 CV_16S 避免外溢。

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	Sobel(src,grad_x,ddepth,1,0,3);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(src, grad_y, ddepth, 0, 1, 3);
	/*
	src_gray: 在本例中为输入图像，元素类型 CV_8U
	grad_x/grad_y: 输出图像.
	ddepth: 输出图像的深度，设定为 CV_16S 避免外溢。
	x_order: x 方向求导的阶数。
	y_order: y 方向求导的阶数。
	scale, delta 和 BORDER_DEFAULT: 使用默认值
	*/
	
	convertScaleAbs(grad_y, abs_grad_y);//将中间结果转换到 CV_8U:


	
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow(window_name, grad);

	waitKey(0);

	return 0;

}