
#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"   
using namespace cv;


Mat canny_src, canny_src_gray;
Mat canny_dst, canny_detected_edges;

int edgeThresh = 1;
int lowThreshold = 0;
int const max_lowThreshold = 100;
int ratio = 3;
int canny_kernel_size = 3;
char* canny_window_name = "Edge Map";

void Canny_trackbar(int, void*)
{
	GaussianBlur(canny_src_gray, canny_detected_edges, Size(3, 3),0 ,0);
	Canny(canny_detected_edges, canny_detected_edges, lowThreshold, lowThreshold*ratio,canny_kernel_size);
	/*
		
		输入参数:
		detected_edges: 原灰度图像
		detected_edges: 输出图像 (支持原地计算，可为输入图像)
		lowThreshold: 用户通过 trackbar设定的值。
		highThreshold: 设定为低阈值的3倍 (根据Canny算法的推荐)
		kernel_size: 设定为 3 (Sobel内核大小，内部使用)
	
	*/
	canny_dst = Scalar::all(0); //把canny_dst的值全赋值为0
	canny_src.copyTo(canny_dst, canny_detected_edges);
	imshow(canny_window_name, canny_detected_edges);
	
}

int canny_main()
{
	canny_src = imread("tiger.jpg");
	if (!canny_src.data){
		return 1;
	}
	cvtColor(canny_src, canny_src_gray, CV_RGB2GRAY);
	
	namedWindow(canny_window_name, CV_WINDOW_AUTOSIZE);
	canny_dst.create(canny_src.size(), canny_src.type());
	createTrackbar("canny", canny_window_name, &lowThreshold, max_lowThreshold, Canny_trackbar);
	Canny_trackbar(0, 0);
	waitKey(0);
}