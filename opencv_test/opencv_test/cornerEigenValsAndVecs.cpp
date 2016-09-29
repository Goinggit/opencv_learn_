#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat  cornerEigenValsAndVecs_src, cornerEigenValsAndVecs_src_gray;
Mat myHarris_dst; Mat myHarris_copy; Mat Mc;
Mat myShiTomasi_dst; Mat myShiTomasi_copy;

int myShiTomasi_qualityLevel = 50;
int myHarris_qualityLevel = 50;
int max_qualityLevel = 100;

double myHarris_minVal; double myHarris_maxVal;
double myShiTomasi_minVal; double myShiTomasi_maxVal;

RNG rng3(123456);

char* myHarris_window = "My Harris corner detector";
char* myShiTomasi_window = "My Shi Tomasi corner detector";

/// Function headers
void myShiTomasi_function(int, void*);
void myHarris_function(int, void*);

/** @function main */
int cornerEigenValsAndVecs_main(int argc, char** argv)
{
	/// Load source image and convert it to gray

	float nn = pow(1,4);
	cout << "nn =" << nn << endl;
	cornerEigenValsAndVecs_src = imread("tiger.jpg");
	if (!cornerEigenValsAndVecs_src.data){
		return -1;
	}
	cvtColor(cornerEigenValsAndVecs_src, cornerEigenValsAndVecs_src_gray, CV_BGR2GRAY);

	/// Set some parameters
	int blockSize = 3; int apertureSize = 3;

	/// My Harris matrix -- Using cornerEigenValsAndVecs
	myHarris_dst = Mat::zeros(cornerEigenValsAndVecs_src_gray.size(), CV_32FC(6));
	Mc = Mat::zeros(cornerEigenValsAndVecs_src_gray.size(), CV_32FC1);

	cornerEigenValsAndVecs(cornerEigenValsAndVecs_src_gray, myHarris_dst, blockSize, apertureSize, BORDER_DEFAULT);
	/*
		cornerEigenValsAndVecs����
		���ã�����ͼ��������ֵ�������������ڽǵ��⡣
		��ʽ��void cornerEigenValsAndVecs(InputArray src, OutputArray dst, int blockSize, int ksize, int borderType=BORDER_DEFAULT )��
		������
		src�����뵥ͨ��8λ�򸡵�ͼ��
		dst�������洢�����ͼ������src��ͬ�Ĵ�С������ΪCV_32FC(6)��
		blockSize������ߴ磻
		ksize��Sobel()���ӵĿ׾�������
		borderType���������Ʒ�ʽ��
	*/

	/* calculate Mc */
	for (int j = 0; j < cornerEigenValsAndVecs_src_gray.rows; j++)
	{
		for (int i = 0; i < cornerEigenValsAndVecs_src_gray.cols; i++)
		{
			float lambda_1 = myHarris_dst.at<Vec6f>(j, i)[0];
			float lambda_2 = myHarris_dst.at<Vec6f>(j, i)[1];
			Mc.at<float>(j, i) = lambda_1*lambda_2 - 0.04*pow((lambda_1 + lambda_2), 2);
			/*
				pow����
				���ã���������ÿ��Ԫ������һ��ָ���ݡ�
				��ʽ��void pow(folat a, int b)��
				������
				a���������
				b��ָ���ݣ�
				
			*/
		}
	}

	minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal, 0, 0, Mat());

	/* Create Window and Trackbar */
	namedWindow(myHarris_window, CV_WINDOW_AUTOSIZE);
	createTrackbar(" Quality Level:", myHarris_window, &myHarris_qualityLevel, max_qualityLevel,
		myHarris_function);
	myHarris_function(0, 0);

	/// My Shi-Tomasi -- Using cornerMinEigenVal
	myShiTomasi_dst = Mat::zeros(cornerEigenValsAndVecs_src_gray.size(), CV_32FC1);
	cornerMinEigenVal(cornerEigenValsAndVecs_src_gray, myShiTomasi_dst, blockSize, apertureSize, BORDER_DEFAULT);
	/*
		cornerMinEigenVal����
		���ã������ݶȾ������С����ֵ���ڽǵ��⡣
		��ʽ��void cornerMinEigenVal(InputArray src, OutputArray dst, int blockSize, int ksize=3, int borderType=BORDER_DEFAULT )��
		������
		src�����뵥ͨ��8λ�򸡵�ͼ��
		dst�������洢��С����ֵ��ͼ������src��ͬ�Ĵ�С������ΪCV_32FC1��
		blockSize������ߴ磻
		ksize��Sobel()���ӵĿ׾�������
		borderType���������Ʒ�ʽ��
	*/

	minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal, 0, 0, Mat());

	/* Create Window and Trackbar */
	namedWindow(myShiTomasi_window, CV_WINDOW_AUTOSIZE);
	createTrackbar(" Quality Level:", myShiTomasi_window, &myShiTomasi_qualityLevel, max_qualityLevel,
		myShiTomasi_function);
	myShiTomasi_function(0, 0);

	waitKey(0);
	return(0);
}

/** @function myShiTomasi_function  */
void myShiTomasi_function(int, void*)
{
	myShiTomasi_copy = cornerEigenValsAndVecs_src.clone();

	if (myShiTomasi_qualityLevel < 1) { myShiTomasi_qualityLevel = 1; }

	for (int j = 0; j < cornerEigenValsAndVecs_src_gray.rows; j++)
	{
		for (int i = 0; i < cornerEigenValsAndVecs_src_gray.cols; i++)
		{
			if (myShiTomasi_dst.at<float>(j, i) > myShiTomasi_minVal + (myShiTomasi_maxVal -
				myShiTomasi_minVal)*myShiTomasi_qualityLevel / max_qualityLevel)
			{
				circle(myShiTomasi_copy, Point(i, j), 4, Scalar(rng3.uniform(0, 255),
					rng3.uniform(0, 255), rng3.uniform(0, 255)), -1, 8, 0);
			}
		}
	}
	imshow(myShiTomasi_window, myShiTomasi_copy);
}

/** @function myHarris_function */
void myHarris_function(int, void*)
{
	myHarris_copy = cornerEigenValsAndVecs_src.clone();

	if (myHarris_qualityLevel < 1) { myHarris_qualityLevel = 1; }

	for (int j = 0; j < cornerEigenValsAndVecs_src_gray.rows; j++)
	{
		for (int i = 0; i < cornerEigenValsAndVecs_src_gray.cols; i++)
		{
			if (Mc.at<float>(j, i) > myHarris_minVal + (myHarris_maxVal - myHarris_minVal)
				*myHarris_qualityLevel / max_qualityLevel)
			{
				circle(myHarris_copy, Point(i, j), 4, Scalar(rng3.uniform(0, 255), rng3.uniform(0, 255),
					rng3.uniform(0, 255)), -1, 8, 0);
			}
		}
	}
	imshow(myHarris_window, myHarris_copy);
}
