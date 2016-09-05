
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
		
		�������:
		detected_edges: ԭ�Ҷ�ͼ��
		detected_edges: ���ͼ�� (֧��ԭ�ؼ��㣬��Ϊ����ͼ��)
		lowThreshold: �û�ͨ�� trackbar�趨��ֵ��
		highThreshold: �趨Ϊ����ֵ��3�� (����Canny�㷨���Ƽ�)
		kernel_size: �趨Ϊ 3 (Sobel�ں˴�С���ڲ�ʹ��)
	
	*/
	canny_dst = Scalar::all(0); //��canny_dst��ֵȫ��ֵΪ0
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