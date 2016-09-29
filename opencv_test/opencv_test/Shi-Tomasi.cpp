#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat shit_tomasi_src, shit_tomasi_src_gray;

int shit_tomasi_maxCorners = 23;
int shit_tomasi_maxTrackbar = 1000;

RNG rng6(6666);
char* shit_tomasi_source_window = "Image";

/// Function header
void goodFeaturesToTrack_Demo(int, void*);

/**
* @function main
*/
int shi_tomasi_main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	shit_tomasi_src = imread("house.jpg");

	if (!shit_tomasi_src.data){
		return -1;
	}
	cvtColor(shit_tomasi_src, shit_tomasi_src_gray, CV_BGR2GRAY);

	/// Create Window
	namedWindow(shit_tomasi_source_window, CV_WINDOW_AUTOSIZE);

	/// Create Trackbar to set the number of corners
	createTrackbar("Max  corners:", shit_tomasi_source_window, &shit_tomasi_maxCorners, shit_tomasi_maxTrackbar, goodFeaturesToTrack_Demo);

	imshow(shit_tomasi_source_window, shit_tomasi_src);

	goodFeaturesToTrack_Demo(0, 0);

	waitKey(0);
	return(0);
}

/**
* @function goodFeaturesToTrack_Demo.cpp
* @brief Apply Shi-Tomasi corner detector
*/
void goodFeaturesToTrack_Demo(int, void*)
{
	if (shit_tomasi_maxCorners < 1){ 

		shit_tomasi_maxCorners = 1; 
	}

	/// Parameters for Shi-Tomasi algorithm
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	/// Copy the source image
	Mat copy;
	copy = shit_tomasi_src.clone();

	/// Apply corner detection
	/*
		void goodFeaturesToTrack( InputArray image, OutputArray corners,  
                                     int maxCorners, double qualityLevel, double minDistance,  
                                     InputArray mask=noArray(), int blockSize=3,  
                                     bool useHarrisDetector=false, double k=0.04 );  
	*/
	goodFeaturesToTrack(shit_tomasi_src_gray,
		corners,
		shit_tomasi_maxCorners,
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
		circle(copy, corners[i], r, Scalar(rng6.uniform(0, 255), rng6.uniform(0, 255),
			rng6.uniform(0, 255)), -1, 8, 0);
	}

	/// Show what you got
	namedWindow(shit_tomasi_source_window, CV_WINDOW_AUTOSIZE);
	imshow(shit_tomasi_source_window, copy);

}
