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
		k为经常常数，取值范围为0.04~0.06
		由此，可以得出这样的结论：增大k的值，将减小角点响应值R，降低角点检测的灵性，减少被检测角点的数量；
		减小k值，将增大角点响应值R，增加角点检测的灵敏性，增加被检测角点的数量。
	*/


	/// Detecting corners
	cornerHarris(harris_src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
	/*
		第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。
		第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放Harris角点检测的输出结果，和源图片有一样的尺寸和类型。
		第三个参数，int类型的blockSize，表示邻域的大小，更多的详细信息在cornerEigenValsAndVecs（）中有讲到。
		第四个参数，int类型的ksize，表示Sobel()算子的孔径大小。
		第五个参数，double类型的k，Harris参数。
		第六个参数，int类型的borderType，图像像素的边界模式，注意它有默认值BORDER_DEFAULT。更详细的解释，参考borderInterpolate( )函数。
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