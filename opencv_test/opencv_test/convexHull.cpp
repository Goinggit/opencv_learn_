#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;
using namespace std;

Mat convex_src; Mat convex_src_gray;
int convex_thresh = 100;
int convex_max_thresh = 255;
RNG rng2(12345);

/// Function header
void convex_thresh_callback(int, void*);

/** @function main */
int convex_main(int argc, char** argv)
{
	/// 加载源图像
	convex_src = imread("hand.jpg",1);

	/// 转成灰度图并进行模糊降噪
	cvtColor(convex_src, convex_src_gray, CV_BGR2GRAY);
	blur(convex_src_gray, convex_src_gray, Size(3, 3));

	/// 创建窗体
	char* source_window ="Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, convex_src);

	createTrackbar(" Threshold:", "Source", &convex_thresh, convex_max_thresh, convex_thresh_callback);
	convex_thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @function thresh_callback */
void convex_thresh_callback(int, void*)
{
	//Mat src_copy = convex_src.clone();
	Mat threshold_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 对图像进行二值化
	threshold(convex_src_gray, threshold_output, convex_thresh, 255, THRESH_BINARY);

	/// 寻找轮廓
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// 对每个轮廓计算其凸包
	vector< vector<Point> >hull(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
		//convexHull(contours[i], hull[i], false);
		/*
		凸殼(Convex Hull)是一個計算幾何中的概念，簡單的說，在給定二維平面上的點集合，凸殼就是將最外層的點連接起來的凸多邊型，它能包含點集合中的所有點，在影像處理中，通常是找到某個物件後，用來填補空隙，或者是進一步的進行物件辨識。

		OpenCV凸殼

		void convexHull(InputArray points, OutputArray hull, bool clockwise=false, bool returnPoints=true)

		points：輸入資訊，可以為包含點的容器(vector)或是Mat。
		hull：輸出資訊，包含點的容器(vector)。
		lockwise：方向旗標，如果true是順時針，false是逆時針。
		*/
	}

	/// 绘出轮廓及其凸包
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng2.uniform(0, 255), rng2.uniform(0, 255), rng2.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	/// 把结果显示在窗体
	namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);
	imshow("Hull demo", drawing);
}
