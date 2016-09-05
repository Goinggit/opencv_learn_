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
	src_gray: ����ͼ�� (�Ҷ�ͼ)
	circles: �洢������������:  ���ϵ���������ʾÿ����⵽��Բ.
	CV_HOUGH_GRADIENT: ָ����ⷽ��. ����OpenCV��ֻ�л����ݶȷ�
	dp = 1: �ۼ���ͼ��ķ��ȷֱ���
	min_dist = src_gray.rows/8: ��⵽Բ��֮�����С����
	param_1 = 200: Canny��Ե�����ĸ���ֵ
	param_2 = 100: Բ�ļ����ֵ.
	min_radius = 0: �ܼ�⵽����СԲ�뾶, Ĭ��Ϊ0.
	max_radius = 0: �ܼ�⵽�����Բ�뾶, Ĭ��Ϊ0
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