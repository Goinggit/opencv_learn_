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

	/// װ��ͼ��
	src = imread("1.jpg");

	if (!src.data)
	{
		return-1;
	}

	/// �ָ��3����ͨ��ͼ�� ( R, G �� B )
	vector<Mat> rgb_planes;
	split(src, rgb_planes);

	/// �趨bin��Ŀ
	int histSize = 255;

	/// �趨ȡֵ��Χ ( R,G,B) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// ����ֱ��ͼ:
	calcHist(&rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	/*
		&rgb_planes[0]: ��������(�����鼯)
		1: ��������ĸ��� (��������ʹ����һ����ͨ��ͼ������Ҳ�����������鼯 )
		0: ��Ҫͳ�Ƶ�ͨ�� (dim)���� ����������ֻ��ͳ���˻Ҷ� (��ÿ�����鶼�ǵ�ͨ��)����ֻҪд 0 �����ˡ�
		Mat(): ����( 0 ��ʾ���Ը�����)�� ���δ���壬��ʹ������
		r_hist: ����ֱ��ͼ�ľ���
		1: ֱ��ͼά��
		histSize: ÿ��ά�ȵ�bin��Ŀ
		histRange: ÿ��ά�ȵ�ȡֵ��Χ
		uniform �� accumulate: bin��С��ͬ�����ֱ��ͼ�ۼ�
	*/
	calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	// ����ֱ��ͼ����
	int hist_w =800; int hist_h =800;
	int bin_w = cvRound((double)hist_w / histSize); //��������ȥ����

	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));

	/// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/*
	r_hist: ��������
	r_hist: ��һ������������(֧��ԭ�ؼ���)
	0 �� histImage.rows: ��������ǹ�һ�� r_hist ֮���ȡֵ����
	NORM_MINMAX: ��һ������ (����ָ���ķ�������ֵ���ŵ�����ָ����Χ)
	-1: ָʾ��һ����������������������ͬ����
	Mat(): ��ѡ������
	*/

	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// ��ֱ��ͼ�����ϻ���ֱ��ͼ
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

	/// ��ʾֱ��ͼ
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
	imshow("Demo", src);

	waitKey(0);

	return	0;

}