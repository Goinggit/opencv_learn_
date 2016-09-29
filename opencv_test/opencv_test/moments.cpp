#include <iostream> // for standard I/O
#include <string>   // for strings
#include <stdio.h>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;

Mat comments_src; Mat comments_src_gray;
int comments_thresh = 100;
int comments_max_thresh = 255;
RNG rng5(12312);

/// 函数声明
void comments_thresh_callback(int, void*);

/** @主函数 */
int coments_main(int argc, char** argv)
{
	/// 读入原图像, 返回3通道图像数据
	comments_src = imread("hot.jpg", 1);

	/// 把原图像转化成灰度图像并进行平滑
	cvtColor(comments_src, comments_src_gray, CV_BGR2GRAY);
	blur(comments_src_gray, comments_src_gray, Size(3, 3));

	/// 创建新窗口
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, comments_src);

	createTrackbar(" Canny thresh:", "Source", &comments_thresh, comments_max_thresh, comments_thresh_callback);
	comments_thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @thresh_callback 函数 */
void comments_thresh_callback(int, void*)
{
	Mat canny_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 使用Canndy检测边缘
	Canny(comments_src_gray, canny_output, comments_thresh, comments_thresh * 3, 3);
	/// 找到轮廓
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// 计算矩
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	///  计算中心矩:
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	/// 绘制轮廓
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng5.uniform(0, 255), rng5.uniform(0, 255), rng5.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	/// 显示到窗口中
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	/// 通过m00计算轮廓面积并且和OpenCV函数比较
	printf("\t Info: Area and Contour Length \n");
	for (int i = 0; i< contours.size(); i++)
	{
		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
		//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		//circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}
