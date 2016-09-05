#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace std;

using namespace cv;

Mat findcon_src; Mat findcon_src_gray;
int findcon_thresh = 100;
int findcon_max_thresh = 255;
extern RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

/** @function main */
int findcontours_main(int argc, char** argv)
{
	/// 加载源图像
	findcon_src = imread("1.jpg");

	/// 转成灰度并模糊化降噪
	cvtColor(findcon_src, findcon_src_gray, CV_BGR2GRAY);
	blur(findcon_src_gray, findcon_src_gray, Size(3, 3));

	/// 创建窗体
	char* source_window ="Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, findcon_src);

	createTrackbar(" Canny thresh:", "Source", &findcon_thresh, findcon_max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	/// 用Canny算子检测边缘
	Canny(findcon_src_gray, canny_output, findcon_thresh, findcon_thresh * 3, 3);
	/// 寻找轮廓
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	/*
	void findContours(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Pointoffset=Point())

	void findContours(InputOutputArray image, OutputArrayOfArrays contours, int mode, int method, Point offset=Point())

	image：輸入圖，使用八位元單通道圖，所有非零的像素都會列入考慮，通常為二極化後的圖。
	contours：包含所有輪廓的容器(vector)，每個輪廓都是儲存點的容器(vector)，所以contours的資料結構為vector< vector>。
	hierarchy：可有可無的輸出向量，以階層的方式記錄所有輪廓。
	mode：取得輪廓的模式。
	method：儲存輪廓點的方法。
	mode：取得輪廓的模式，有以下幾種可選擇：

	CV_RETR_EXTERNAL：只取最外層的輪廓。
	CV_RETR_LIST：取得所有輪廓，不建立階層(hierarchy)。
	CV_RETR_CCOMP：取得所有輪廓，儲存成兩層的階層，首階層為物件外圍，第二階層為內部空心部分的輪廓，如果更內部有其餘物件，包含於首階層。
	CV_RETR_TREE：取得所有輪廓，以全階層的方式儲存。
	method：儲存輪廓點的方法，有以下幾種可選擇：

	CV_CHAIN_APPROX_NONE：儲存所有輪廓點。
	CV_CHAIN_APPROX_SIMPLE：對水平、垂直、對角線留下頭尾點，所以假如輪廓為一矩形，只儲存對角的四個頂點。
	*/

	/// 绘出轮廓
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		/*
		void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

		image：輸入輸出圖，會將輪廓畫在此影像上。
		contours：包含所有輪廓的容器(vector)，也就是findContours()所找到的contours。
		contourIdx：指定畫某個輪廓。
		color：繪製的顏色。
		lineType：繪製的線條型態。
		hierarchy：輪廓階層，也就是findContours()所找到的hierarchy。
		maxLevel：最大階層的輪廓，可以指定想要畫的輪廓，有輸入hierarchy時才會考慮，輸入的值代表繪製的層數。
		maxLevel：

		0：繪製指定階層的輪廓。
		1：繪製指定階層的輪廓，和他的一階子階層。
		2：繪製指定階層的輪廓，和他的一階、二階子階層。
		剩下數字依此類推。

		*/
	}

	/// 在窗体中显示结果
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}