/*
#include <cv.h>
#include <highgui.h>
#include <iostream>
#pragma comment( lib, "opencv_highgui2410d.lib")
#pragma comment( lib, "opencv_core2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib") 
using namespace cv;
void MyEllipse(Mat img, double angle, int x, int y);
int main()
{
	/// 窗口名字
	char atom_window[] ="Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";
	//int x = 500;
	//int y = 500;
	namedWindow(atom_window);
	//namedWindow(rook_window);
	//创建空全黑像素的空图像
	Mat atom_image = Mat::zeros(x, y, CV_8UC3);
	Mat rook_image = Mat::zeros(x, y, CV_8UC3);
	MyEllipse(atom_image, 90);
	imshow(atom_window, atom_image);
	waitKey();
}
void MyEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
		Point(w / 2.0, w / 2.0),
		Size(w / 4.0, w / 16.0),
		angle,
		0,
		360,
		Scalar(255, 0, 0),
		thickness,
		lineType);
}
*/