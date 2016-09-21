

#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;

int calcHist_main()
{
	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;
	Mat src_test2, hsv_test2;
	Mat hsv_half_down;

	src_base = imread("E:\\JP.VideoAnalysis\\output\\objects\\1152_2_10_(1734,508,1794,612).jpg");
	src_test1 = imread("E:\\JP.VideoAnalysis\\output\\objects\\1167_1_10_(1788,556,1854,604).jpg");
	src_test2 = imread("E:\\JP.VideoAnalysis\\output\\objects\\1136_1_10_(1674,608,1734,668).jpg");
	if (!src_base.data){
		return -1;
	}
	if (!src_test1.data){
		return -1;
	}
	if (!src_test2.data){
		return -1;
	}



	cvtColor(src_base, hsv_base, CV_BGR2HSV);
	cvtColor(src_test1, hsv_test1, CV_BGR2HSV);
	cvtColor(src_test2, hsv_test2, CV_BGR2HSV);

	//取基准下半身像  Range(start, end)
	hsv_half_down = hsv_base(Range(hsv_base.rows / 2, hsv_base.rows), Range(0, hsv_base.cols - 1));

	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 };

	MatND hist_base;
	MatND hist_half_down;
	MatND hist_test1;
	MatND hist_test2;

	calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges);
	/*
	&hsv_base: 输入数组(或数组集)
	1: 输入数组的个数 (这里我们使用了一个单通道图像，我们也可以输入数组集 )
	channels: 需要统计的通道 (dim)索引 ，这里我们只是统计了灰度 (且每个数组都是单通道)所以只要写 0 就行了。
	Mat(): 掩码( 0 表示忽略该像素)， 如果未定义，则不使用掩码
	hist_base: 储存直方图的矩阵
	2: 直方图维数
	histSize: 每个维度的bin数目
	ranges: 每个维度的取值范围
	uniform 和 accumulate: bin大小相同，清楚直方图痕迹
	*/

	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges);
	normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges);
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges);
	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());

	for (int i = 0; i <4; i++)
	{
		int compare_method = i;
		double base_base = compareHist(hist_base, hist_base, compare_method);
		double base_half = compareHist(hist_base, hist_half_down, compare_method);
		double base_test1 = compareHist(hist_base, hist_test1, compare_method);
		double base_test2 = compareHist(hist_base, hist_test2, compare_method);

		printf(" Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half, base_test1, base_test2);
	}

	printf("Done \n");
	system("pause");
	return 0;
}

	





