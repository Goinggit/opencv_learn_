#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

using namespace cv;
using namespace std;

int hough_circle_main()
{
	Mat src,src_gray;
	src = imread("circle.jpg");
	if (!src.data){
		return 1;
	}
	cvtColor(src, src_gray, CV_BGR2GRAY);

	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 100, 100, 0, 0);
	/*
	src_gray: 输入图像 (灰度图)
	circles: 存储下面三个参数:  集合的容器来表示每个检测到的圆.
	CV_HOUGH_GRADIENT: 指定检测方法. 现在OpenCV中只有霍夫梯度法
	dp = 1: 累加器图像的反比分辨率
	min_dist = src_gray.rows/8: 检测到圆心之间的最小距离
	param_1 = 200: Canny边缘函数的高阈值
	param_2 = 100: 圆心检测阈值.
	min_radius = 0: 能检测到的最小圆半径, 默认为0.
	max_radius = 0: 能检测到的最大圆半径, 默认为0
	*/
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	waitKey(0);
	return 0;

}