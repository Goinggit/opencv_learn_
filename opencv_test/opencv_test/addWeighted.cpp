#include <iostream> // for standard I/O
#include <string>   // for strings
#include <stdio.h>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;

int addw_main(int argc, char** argv)
{
	double alpha = 0.5; double beta; double input;

	Mat src1, src2, dst;
	/// Ask the user enter alpha
	std::cout << " Simple Linear Blender " << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "* Enter alpha [0-1]: ";
	//std::cin >> input;

	/// We use the alpha provided by the user iff it is between 0 and 1
	if (alpha >= 0 && alpha <= 1)
	{
		//alpha = input;
	}

	/// Read image ( same size, same type )
	src1 = imread("tiger.jpg");
	src2 = imread("2.jpg");

	if (!src1.data) { printf("Error loading src1 \n"); return -1; }
	if (!src2.data) { printf("Error loading src2 \n"); return -1; }

	/// Create Windows
	namedWindow("Linear Blend", 1);
	Mat imageROI;
	imageROI = src1(Rect(400, 200, src2.cols, src2.rows));
	beta = (1.0 - alpha);
	addWeighted(imageROI, alpha, src2, beta, 0.0, dst);
	//if (!dst.data) { printf("Error loading src1 \n"); return -1; }
	imshow("Linear Blend", dst);

	waitKey(0);
	return 0;
}
