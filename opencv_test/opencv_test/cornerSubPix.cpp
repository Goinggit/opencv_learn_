#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat cornersub_src, cornersub_src_gray;

int cornersub_maxCorners = 10;
int cornersub_maxTrackbar = 25;

RNG rng4(12324);
char* cornersub_source_window = "Image";

/// Function header
void cornersub_goodFeaturesToTrack_Demo(int, void*);

/** @function main */
int cornersub_main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	cornersub_src = imread("house.jpg");
	cvtColor(cornersub_src, cornersub_src_gray, CV_BGR2GRAY);

	/// Create Window
	namedWindow(cornersub_source_window, CV_WINDOW_AUTOSIZE);

	/// Create Trackbar to set the number of corners
	createTrackbar("Max  corners:", cornersub_source_window, &cornersub_maxCorners, cornersub_maxTrackbar, cornersub_goodFeaturesToTrack_Demo);

	imshow(cornersub_source_window, cornersub_src);

	cornersub_goodFeaturesToTrack_Demo(0, 0);

	waitKey(0);
	return(0);
}

/**
* @function goodFeaturesToTrack_Demo.cpp
* @brief Apply Shi-Tomasi corner detector
*/
void cornersub_goodFeaturesToTrack_Demo(int, void*)
{
	if (cornersub_maxCorners < 1) { cornersub_maxCorners = 1; }

	/// Parameters for Shi-Tomasi algorithm
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	/// Copy the source image
	Mat copy;
	copy = cornersub_src.clone();

	/// Apply corner detection
	goodFeaturesToTrack(cornersub_src_gray,
		corners,
		cornersub_maxCorners,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		useHarrisDetector,
		k);


	/// Draw corners detected
	cout << "** Number of corners detected: " << corners.size() << endl;
	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], r, Scalar(rng4.uniform(0, 255), rng4.uniform(0, 255),
			rng4.uniform(0, 255)), -1, 8, 0);
	}

	/// Show what you got
	namedWindow(cornersub_source_window, CV_WINDOW_AUTOSIZE);
	imshow(cornersub_source_window, copy);

	/// Set the neeed parameters to find the refined corners
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001);
	/*
		TermCriteriaģ���࣬ȡ����֮ǰ��CvTermCriteria�����������Ϊ�����㷨����ֹ�����ģ�������ڲο��ֲ�����ܵĺܼ򵥣��Ҳ���Щ���ϣ��������һ�¡�
		���������Ҫ3��������һ�������ͣ��ڶ�������Ϊ�����������������һ�����ض�����ֵ��
		������CV_TERMCRIT_ITER��CV_TERMCRIT_EPS��CV_TERMCRIT_ITER+CV_TERMCRIT_EPS���ֱ�����ŵ�����ֹ����Ϊ�ﵽ������������ֹ��
		��������ֵ��ֹ���������߶���Ϊ������ֹ������
		���ϵĺ��Ӧ��c++�İ汾�ֱ�ΪTermCriteria::COUNT��TermCriteria::EPS�������COUNTҲ����д��MAX_ITER��
	*/

	/// Calculate the refined corner locations
	cornerSubPix(cornersub_src_gray, corners, winSize, zeroZone, criteria);

	/*
		cornerSubPix()����
		��1������ԭ��
		cornerSubPix()�����ڽǵ����о�ȷ���ǵ�λ�ã��亯��ԭ�����£�
		[cpp] view plain copy
		  1. C++: void cornerSubPix(InputArray image, InputOutputArray corners, Size winSize, Size zeroZone, TermCriteria criteria);  
		  2. C: void cvFindCornerSubPix(const CvArr* image, CvPoint2D32f* corners, int count, CvSize win, CvSize zero_zone, CvTermCriteria criteria);  

		��2����������
		��������˵�����£�
		image������ͼ��
		corners������ǵ�ĳ�ʼ�����Լ���׼������������������
		winSize���������ڱ߳���һ�룬�������winSize=Size(5,5)����һ����СΪ��5*2+1��5*2+1�����������ڽ���ʹ�á�
		zeroZone�����������м��dead region�߳���һ�룬��ʱ���ڱ�������ؾ���������ԡ����ֵ��Ϊ(-1,-1)���ʾû���������
		criteria���ǵ㾫׼���������̵���ֹ������Ҳ���ǵ�������������criteria.maxCount�����߽ǵ�λ�ñ仯С��criteria.epsilonʱ��ֹͣ�������̡�
	*/

	/// Write them down
	for (int i = 0; i < corners.size(); i++)
	{
		cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
}
