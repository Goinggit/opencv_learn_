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

/// ��������
void comments_thresh_callback(int, void*);

/** @������ */
int coments_main(int argc, char** argv)
{
	/// ����ԭͼ��, ����3ͨ��ͼ������
	comments_src = imread("hot.jpg", 1);

	/// ��ԭͼ��ת���ɻҶ�ͼ�񲢽���ƽ��
	cvtColor(comments_src, comments_src_gray, CV_BGR2GRAY);
	blur(comments_src_gray, comments_src_gray, Size(3, 3));

	/// �����´���
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, comments_src);

	createTrackbar(" Canny thresh:", "Source", &comments_thresh, comments_max_thresh, comments_thresh_callback);
	comments_thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @thresh_callback ���� */
void comments_thresh_callback(int, void*)
{
	Mat canny_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// ʹ��Canndy����Ե
	Canny(comments_src_gray, canny_output, comments_thresh, comments_thresh * 3, 3);
	/// �ҵ�����
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// �����
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	///  �������ľ�:
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	/// ��������
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng5.uniform(0, 255), rng5.uniform(0, 255), rng5.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	/// ��ʾ��������
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	/// ͨ��m00��������������Һ�OpenCV�����Ƚ�
	printf("\t Info: Area and Contour Length \n");
	for (int i = 0; i< contours.size(); i++)
	{
		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
		//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		//circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}
