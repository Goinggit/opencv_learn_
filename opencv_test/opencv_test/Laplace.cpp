#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

using namespace cv;

int lapalce_main()
{
	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Demo";

	int c;

	/// װ��ͼ��
	src = imread("1.jpg");
	if (!src.data){
		return 0;
	}
	GaussianBlur(src, src,Size(3,3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	/*
		�������������²���:
		src_gray: ����ͼ��
		dst: ���ͼ��
		ddepth: ���ͼ�����ȡ� ��Ϊ����ͼ�������� CV_8U ���������Ǳ��붨�� ddepth = CV_16S �Ա������硣
		kernel_size: �ڲ����õ� Sobel���ӵ��ں˴�С������������Ϊ3��
		scale, delta �� BORDER_DEFAULT: ʹ��Ĭ��ֵ��
	*/
	Mat abs_dst; 

	convertScaleAbs(dst, abs_dst);

	/// ��ʾ���
	imshow(window_name, abs_dst);

	waitKey(0);

	return 0;

}