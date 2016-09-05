#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;
using namespace std;

int calcHist_main(int argc, char** argv)
{
	Mat src, dst;

	/// 装载图像
	src = imread("1.jpg");

	if (!src.data)
	{
		return-1;
	}

	/// 分割成3个单通道图像 ( R, G 和 B )
	vector<Mat> rgb_planes;
	split(src, rgb_planes);

	/// 设定bin数目
	int histSize = 255;

	/// 设定取值范围 ( R,G,B) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// 计算直方图:
	calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	/*
		&rgb_planes[0]: 输入数组(或数组集)
		1: 输入数组的个数 (这里我们使用了一个单通道图像，我们也可以输入数组集 )
		0: 需要统计的通道 (dim)索引 ，这里我们只是统计了灰度 (且每个数组都是单通道)所以只要写 0 就行了。
		Mat(): 掩码( 0 表示忽略该像素)， 如果未定义，则不使用掩码
		r_hist: 储存直方图的矩阵
		1: 直方图维数
		histSize: 每个维度的bin数目
		histRange: 每个维度的取值范围
		uniform 和 accumulate: bin大小相同，清楚直方图痕迹
	*/
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	// 创建直方图画布
	int hist_w =800; int hist_h =800;
	int bin_w = cvRound((double)hist_w / histSize); //四舍五入去整数

	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// 将直方图归一化到范围 [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/*
	r_hist: 输入数组
	r_hist: 归一化后的输出数组(支持原地计算)
	0 及 histImage.rows: 这里，它们是归一化 r_hist 之后的取值极限
	NORM_MINMAX: 归一化方法 (例中指定的方法将数值缩放到以上指定范围)
	-1: 指示归一化后的输出数组与输入数组同类型
	Mat(): 可选的掩码
	*/

	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// 在直方图画布上画出直方图
	for( int i =1; i < histSize; i++ )
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	/// 显示直方图
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
	imshow("Demo", src);

	waitKey(0);

	return	0;

}