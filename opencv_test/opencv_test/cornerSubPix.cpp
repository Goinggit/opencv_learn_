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

extern RNG rng;
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
		circle(copy, corners[i], r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
			rng.uniform(0, 255)), -1, 8, 0);
	}

	/// Show what you got
	namedWindow(cornersub_source_window, CV_WINDOW_AUTOSIZE);
	imshow(cornersub_source_window, copy);

	/// Set the neeed parameters to find the refined corners
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001);
	/*
		TermCriteria模板类，取代了之前的CvTermCriteria，这个类是作为迭代算法的终止条件的，这个类在参考手册里介绍的很简单，我查了些资料，这里介绍一下。
		该类变量需要3个参数，一个是类型，第二个参数为迭代的最大次数，最后一个是特定的阈值。
		类型有CV_TERMCRIT_ITER、CV_TERMCRIT_EPS、CV_TERMCRIT_ITER+CV_TERMCRIT_EPS，分别代表着迭代终止条件为达到最大迭代次数终止，
		迭代到阈值终止，或者两者都作为迭代终止条件。
		以上的宏对应的c++的版本分别为TermCriteria::COUNT、TermCriteria::EPS，这里的COUNT也可以写成MAX_ITER。
	*/

	/// Calculate the refined corner locations
	cornerSubPix(cornersub_src_gray, corners, winSize, zeroZone, criteria);

	/*
		cornerSubPix()函数
		（1）函数原型
		cornerSubPix()函数在角点检测中精确化角点位置，其函数原型如下：
		[cpp] view plain copy
		  1. C++: void cornerSubPix(InputArray image, InputOutputArray corners, Size winSize, Size zeroZone, TermCriteria criteria);  
		  2. C: void cvFindCornerSubPix(const CvArr* image, CvPoint2D32f* corners, int count, CvSize win, CvSize zero_zone, CvTermCriteria criteria);  

		（2）函数参数
		函数参数说明如下：
		image：输入图像
		corners：输入角点的初始坐标以及精准化后的坐标用于输出。
		winSize：搜索窗口边长的一半，例如如果winSize=Size(5,5)，则一个大小为（5*2+1，5*2+1）的搜索窗口将被使用。
		zeroZone：搜索区域中间的dead region边长的一半，有时用于避免自相关矩阵的奇异性。如果值设为(-1,-1)则表示没有这个区域。
		criteria：角点精准化迭代过程的终止条件。也就是当迭代次数超过criteria.maxCount，或者角点位置变化小于criteria.epsilon时，停止迭代过程。
	*/

	/// Write them down
	for (int i = 0; i < corners.size(); i++)
	{
		cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
}