#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  



using namespace cv;
using namespace std;

int houthline_threshold = 2;
int const houthline_threshold_max = 100;
Mat houthline_srt,houthline_show;
Mat houthline_dst, houthline_canny_dst;

static void houthline_threshold_fun(int, void *)
{
#if 0  
	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 100, 0, 0);
	for (size_t i = 0; i < lines.size(); i++)  {
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
#else  
	vector<Vec4i> lines;
	HoughLinesP(houthline_canny_dst, lines, 1, CV_PI / 180, houthline_threshold, 10, 10);
	/*
	dst: ��Ե�������ͼ��. ��Ӧ���Ǹ��Ҷ�ͼ (����ʵ���Ǹ���ֵ��ͼ) * 
	lines: �����ż�⵽��ֱ�ߵĲ�����  ������
	rho : ��������  ������ֵΪ��λ�ķֱ���. ����ʹ�� 1 ����.
	theta: ��������  �Ի���Ϊ��λ�ķֱ���. ����ʹ�� 1�� (��CV_PI/180)
	threshold: Ҫ����⡱ һ��ֱ���������ٵĵ����߽��� *
	 minLinLength: �����һ��ֱ�ߵ����ٵ������. �����������ֱ�߽�������.
	maxLineGap: �ܱ���Ϊ��һ��ֱ���ϵ������������.
	*/
	Mat tmp;
	houthline_show.copyTo(tmp);

	for (size_t i = 0; i < lines.size(); i++)  {
		Vec4i l = lines[i];
		line(tmp, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 0);
	}
	
	
#endif
	imshow("source", houthline_srt);
	imshow("houthline", tmp);

	waitKey(0);


}

int hough_line_main()
{
	namedWindow("houthline", CV_WINDOW_AUTOSIZE);
	houthline_srt = imread("1.jpg");
	if (!houthline_srt.data){
		return 0;
	}
	houthline_srt.copyTo(houthline_show);
	cvtColor(houthline_srt, houthline_srt, CV_RGB2GRAY);
	GaussianBlur(houthline_srt, houthline_srt, Size(3, 3), 0, 0);
	Canny(houthline_srt, houthline_canny_dst, 50, 50 * 3);
	


	

	createTrackbar("houth_threshold", "houthline", &houthline_threshold, houthline_threshold_max, houthline_threshold_fun);
	houthline_threshold_fun(0, 0);
	waitKey(0);
}