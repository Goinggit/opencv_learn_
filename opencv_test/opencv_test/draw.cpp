#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

void MyEllipse(Mat &img, double angle);
void MyLine(Mat img, Point start, Point end);
void MyFilledCircle(Mat img, int w);
int draw()
{
	/// 窗口名字
	char atom_window[] ="Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";
	int x = 500;
	int y = 1000;
	namedWindow(atom_window);
	namedWindow(rook_window);
	//namedWindow(rook_window);
	//创建空全黑像素的空图像
	Mat atom_image = Mat::zeros(x, y, CV_8UC3);
	Mat rook_image = Mat::zeros(x, y, CV_8UC3);
	MyEllipse(atom_image, 0);
	MyEllipse(atom_image, 90);
	MyEllipse(atom_image, 45);
	MyEllipse(atom_image, -45);
	MyLine(atom_image, Point(x / 2, y / 4), Point(x / 6, y / 8));
	MyFilledCircle(atom_image, 100);

	rectangle(rook_image,
		Point(0+20, 7 * 100 / 8.0),
		Point(y-20, x-20),
		Scalar(0, 255, 255),
		1,
		8);
	imshow(atom_window, atom_image);
	imshow(rook_window, rook_image);

	waitKey();
	return 0;
}
void MyEllipse(Mat &img, double angle)
{
	int thickness = 5;
	int lineType = 8;
	int x = img.rows;
	
	int y = img.cols;
	//std::cout << "x = " << Point(x / 2.0, y / 2.0) << std::endl;
	ellipse(img,
		Point(y / 2.0, x / 2.0),
		Size(x / 4.0, y / 16.0),
		angle,
		0,
		360,
		Scalar(255, 0, 0),
		thickness,
		lineType);
	/*
		椭圆将被画到图像 img 上
		椭圆中心为点(w / 2.0, w / 2.0) 并且大小位于矩形(w / 4.0, w / 16.0) 内
		椭圆旋转角度为 angle
		椭圆扩展的弧度从 0 度到 360 度
		图形颜色为 Scalar(255, 255, 0) ，既蓝色
		绘椭圆的线粗为 thickness ，此处是2
	*/
}
void MyLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		start,
		end,
		Scalar(0, 255, 0),
		thickness,
		lineType);
	/*
	画一条从点 start 到点 end 的直线段
	此线段将被画到图像 img 上
	线的颜色由 Scalar( 0, 0, 0) 来定义，在此其相应RGB值为 黑色
	线的粗细由 thickness 设定(此处设为 2)
	此线为8联通 (lineType = 8)
	*/
}
void MyFilledCircle(Mat img,int w)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		Point(img.cols/2, img.rows/2),
		w / 32.0,
		Scalar(0, 0, 255),
		thickness,
		lineType);
	/*
	圆将被画到图像 ( img )上
	圆心由点 center 定义
	圆的半径为: w/32.0
	圆的颜色为: Scalar(0, 0, 255) ，按BGR的格式为 红色
	线粗定义为 thickness = -1, 因此次圆将被填充
	*/
}