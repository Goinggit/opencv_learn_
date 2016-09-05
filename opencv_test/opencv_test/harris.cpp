#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  

#include <iostream>  

using namespace cv;
using namespace std;

/// Global variables
Mat harris_src, harris_src_gray;
int harris_thresh = 225;
int harris_max_thresh = 255;

char* harris_source_window = "Source image";
char* harris_corners_window = "Corners detected";

/// Function header
void harris_cornerHarris_demo(int, void*);

/** @function main */
int harris_main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	harris_src = imread("tiger.jpg");
	if (!harris_src.data){
		return -1;
	}
	cvtColor(harris_src, harris_src_gray, CV_BGR2GRAY);

	/// Create a window and a trackbar
	namedWindow(harris_source_window, CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold: ", harris_source_window, &harris_thresh, harris_max_thresh, harris_cornerHarris_demo);
	imshow(harris_source_window, harris_src);

	harris_cornerHarris_demo(0, 0);

	waitKey(0);
	return(0);
}

/** @function cornerHarris_demo */
void harris_cornerHarris_demo(int, void*)
{

	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros(harris_src.size(), CV_32FC1);

	/// Detector parameters
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.06;
	/*
		kΪ����������ȡֵ��ΧΪ0.04~0.06
		�ɴˣ����Եó������Ľ��ۣ�����k��ֵ������С�ǵ���ӦֵR�����ͽǵ�������ԣ����ٱ����ǵ��������
		��Сkֵ��������ǵ���ӦֵR�����ӽǵ���������ԣ����ӱ����ǵ��������
	*/


	/// Detecting corners
	cornerHarris(harris_src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
	/*
		��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λ���߸�����ͼ��
		�ڶ���������OutputArray���͵�dst���������ú���������������������������ڴ��Harris�ǵ��������������ԴͼƬ��һ���ĳߴ�����͡�
		������������int���͵�blockSize����ʾ����Ĵ�С���������ϸ��Ϣ��cornerEigenValsAndVecs�������н�����
		���ĸ�������int���͵�ksize����ʾSobel()���ӵĿ׾���С��
		�����������double���͵�k��Harris������
		������������int���͵�borderType��ͼ�����صı߽�ģʽ��ע������Ĭ��ֵBORDER_DEFAULT������ϸ�Ľ��ͣ��ο�borderInterpolate( )������
	*/
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	threshold(dst_norm, dst_norm_scaled, harris_thresh, 255, THRESH_BINARY);

	/// Normalizing
	//normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	//convertScaleAbs(dst_norm, dst_norm_scaled);

	/// Drawing a circle around corners
	/*
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > harris_thresh)
			{
				//circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
			}
		}
	}
	/// Showing the result
	*/
	namedWindow(harris_corners_window, CV_WINDOW_AUTOSIZE);
	imshow(harris_corners_window, dst_norm_scaled);
}