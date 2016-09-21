#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat Threshold_src, src_gray, Threshold_dst;
char* Threshold_window_name = "Threshold Demo";

char* trackbar_type = "Type";
char* trackbar_value = "Value";


void Threshold_Demo(int, void*)
{
	/* threshold_type:  0: ��������ֵ     1: ����������ֵ     2: �ض���ֵ     3: 0��ֵ     4: ��0��ֵ   */

	threshold(src_gray, Threshold_dst, threshold_value, max_BINARY_value, threshold_type | CV_THRESH_OTSU);
	//threshold(src_gray, Threshold_dst, threshold_value, max_BINARY_value, threshold_type);
	/*
	src_gray: ����ĻҶ�ͼ��ĵ�ַ��
	dst: ���ͼ��ĵ�ַ��
	threshold_value: ������ֵ����ʱ��ֵ�Ĵ�С��
	max_BINARY_value: �趨�����Ҷ�ֵ���ò��������ڶ������뷴��������ֵ�����У���
	threshold_type: ��ֵ�����͡��������ᵽ��5����ѡ����Ľ����
	*/
	imshow(Threshold_window_name, Threshold_dst);
}
int Threshold_main()
{
	Threshold_src = imread("tiger.jpg");

	/// ��ͼƬת���ɻҶ�ͼƬ
	cvtColor(Threshold_src, src_gray, CV_RGB2GRAY);

	/// ����һ��������ʾͼƬ
	namedWindow(Threshold_window_name, CV_WINDOW_AUTOSIZE);

	/// ������������������ֵ
	createTrackbar(trackbar_type,
		Threshold_window_name, &threshold_type,
		max_type, Threshold_Demo);

	createTrackbar(trackbar_value,
		Threshold_window_name, &threshold_value,
		max_value, Threshold_Demo);

	/// ��ʼ���Զ������ֵ����
	Threshold_Demo(0, 0);

	/// �ȴ��û������������ESC�����˳��ȴ����̡�
	waitKey(0);
	return 0;
}