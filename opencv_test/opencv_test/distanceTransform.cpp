#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>
using namespace cv;


int distanceTran_main()
{
	Mat src = imread("hand.jpg", 1);
	Mat dst;
	dst.create(src.size(), src.type());
	Mat canny;
	canny.create(src.size(), src.type());

	cvtColor(src, canny, CV_RGB2GRAY);
	Canny(canny, canny, 100, 200, 3);
	imshow("canny", canny);
	distanceTransform(canny, dst, CV_DIST_WELSCH, 3);

	namedWindow("src", 1);
	imshow("src", src);
	namedWindow("dist", 1);
	imshow("dist", dst);

	waitKey(0);

	

	return 0;
}