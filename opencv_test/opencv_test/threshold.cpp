#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat Threshold_src, src_gray, Threshold_dst;
char* Threshold_window_name = "Threshold Demo";

char* trackbar_type = "Type";
char* trackbar_value = "Value";


void Threshold_Demo(int, void*)
{
	/* threshold_type:  0: 二进制阈值     1: 反二进制阈值     2: 截断阈值     3: 0阈值     4: 反0阈值   */

	threshold(src_gray, Threshold_dst, threshold_value, max_BINARY_value, threshold_type);
	/*
	src_gray: 输入的灰度图像的地址。
	dst: 输出图像的地址。
	threshold_value: 进行阈值操作时阈值的大小。
	max_BINARY_value: 设定的最大灰度值（该参数运用在二进制与反二进制阈值操作中）。
	threshold_type: 阈值的类型。从上面提到的5种中选择出的结果。
	*/
	imshow(Threshold_window_name, Threshold_dst);
}
int threhold_main()
{
	Threshold_src = imread("tiger.jpg");

	/// 将图片转换成灰度图片
	cvtColor(Threshold_src, src_gray, CV_RGB2GRAY);

	/// 创建一个窗口显示图片
	namedWindow(Threshold_window_name, CV_WINDOW_AUTOSIZE);

	/// 创建滑动条来控制阈值
	createTrackbar(trackbar_type,
		Threshold_window_name, &threshold_type,
		max_type, Threshold_Demo);

	createTrackbar(trackbar_value,
		Threshold_window_name, &threshold_value,
		max_value, Threshold_Demo);

	/// 初始化自定义的阈值函数
	Threshold_Demo(0, 0);

	/// 等待用户按键。如果是ESC健则退出等待过程。
	waitKey(0);
	return 0;
}