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

/// ��������
void boundrect_thresh_callback(int, void*);

/** @������ */
int bounding_main(int argc, char** argv)
{
	/// ����ԭͼ��, ����3ͨ��ͼ��
	boundrect_src = imread("hot.jpg", 1);
	if (!boundrect_src.data){
		return -1;
	}

	/// ת���ɻҶ�ͼ�񲢽���ƽ��
	cvtColor(boundrect_src, boundrect_src_gray, CV_BGR2GRAY);
	blur(boundrect_src_gray, boundrect_src_gray, Size(3, 3));

	/// ��������
	char* source_window ="Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, boundrect_src);

	createTrackbar(" Threshold:", "Source", &boundrect_thresh, boundrect_max_thresh, boundrect_thresh_callback);
	boundrect_thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @thresh_callback ���� */
void boundrect_thresh_callback(int, void*)
{
	Mat threshold_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// ʹ��Threshold����Ե
	threshold(boundrect_src_gray, threshold_output, boundrect_thresh, 255, THRESH_BINARY);
	/// �ҵ�����
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// ����αƽ����� + ��ȡ���κ�Բ�α߽��
	vector< vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 120, true);
		/*
			void approxPolyDP(InputArray curve, OutputArray approxCurve, double epsilon, bool closed)

			curve �C �����㼯��ʾ�����ߡ�ͨ����vector��ʾ��

			approxCurve �C ����Ľ��ƶ�������ߡ�

			epsilon �C ���ƾ��ȣ���ʾԭʼ���ߺͽ�������֮��������룬���������3��
			closed �C �����Ƿ��Ǳպ����ߡ�
		*/
		boundRect[i] = boundingRect(Mat(contours_poly[i]));

		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}


	/// ����������� + ��Χ�ľ��ο� + Բ�ο�
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng1.uniform(0, 255), rng1.uniform(0, 255), rng1.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	/// ��ʾ��һ������
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
