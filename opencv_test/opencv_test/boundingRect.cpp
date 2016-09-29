#include <iostream> // for standard I/O
#include <string>   // for strings
#include <vector>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
#include <stdlib.h>
using namespace std;
using namespace cv;

Mat boundrect_src; Mat boundrect_src_gray;
int boundrect_thresh = 100;
int boundrect_max_thresh = 255;
 RNG rng1(12345);

/// 函数声明
void boundrect_thresh_callback(int, void*);

/** @主函数 */
int bounding_main(int argc, char** argv)
{
	/// 载入原图像, 返回3通道图像
	boundrect_src = imread("hot.jpg", 1);
	if (!boundrect_src.data){
		return -1;
	}

	/// 转化成灰度图像并进行平滑
	cvtColor(boundrect_src, boundrect_src_gray, CV_BGR2GRAY);
	blur(boundrect_src_gray, boundrect_src_gray, Size(3, 3));

	/// 创建窗口
	char* source_window ="Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, boundrect_src);

	createTrackbar(" Threshold:", "Source", &boundrect_thresh, boundrect_max_thresh, boundrect_thresh_callback);
	boundrect_thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @thresh_callback 函数 */
void boundrect_thresh_callback(int, void*)
{
	Mat threshold_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 使用Threshold检测边缘
	threshold(boundrect_src_gray, threshold_output, boundrect_thresh, 255, THRESH_BINARY);
	/// 找到轮廓
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// 多边形逼近轮廓 + 获取矩形和圆形边界框
	vector< vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 120, true);
		/*
			void approxPolyDP(InputArray curve, OutputArray approxCurve, double epsilon, bool closed)

			curve – 轮廓点集表示的曲线。通常用vector表示。

			approxCurve – 输出的近似多边形曲线。

			epsilon – 近似精度，表示原始曲线和近似曲线之间的最大距离，比如代码中3。
			closed – 曲线是否是闭合曲线。
		*/
		boundRect[i] = boundingRect(Mat(contours_poly[i]));

		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}


	/// 画多边形轮廓 + 包围的矩形框 + 圆形框
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng1.uniform(0, 255), rng1.uniform(0, 255), rng1.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	/// 显示在一个窗口
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
