#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;
using namespace std;

Mat convex_src; Mat convex_src_gray;
int convex_thresh = 100;
int convex_max_thresh = 255;
RNG rng2(12345);

/// Function header
void convex_thresh_callback(int, void*);

/** @function main */
int convex_main(int argc, char** argv)
{
	/// ����Դͼ��
	convex_src = imread("hand.jpg",1);

	/// ת�ɻҶ�ͼ������ģ������
	cvtColor(convex_src, convex_src_gray, CV_BGR2GRAY);
	blur(convex_src_gray, convex_src_gray, Size(3, 3));

	/// ��������
	char* source_window ="Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, convex_src);

	createTrackbar(" Threshold:", "Source", &convex_thresh, convex_max_thresh, convex_thresh_callback);
	convex_thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @function thresh_callback */
void convex_thresh_callback(int, void*)
{
	//Mat src_copy = convex_src.clone();
	Mat threshold_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// ��ͼ����ж�ֵ��
	threshold(convex_src_gray, threshold_output, convex_thresh, 255, THRESH_BINARY);

	/// Ѱ������
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// ��ÿ������������͹��
	vector< vector<Point> >hull(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
		//convexHull(contours[i], hull[i], false);
		/*
		͹��(Convex Hull)��һ��Ӌ��׺��еĸ�����ε��f���ڽo�����Sƽ���ϵ��c���ϣ�͹�����ǌ�����ӵ��c�B�������͹��߅�ͣ����ܰ����c�����е������c����Ӱ��̎���У�ͨ�����ҵ�ĳ������ᣬ�Á����a��϶���������Mһ�����M��������R��

		OpenCV͹��

		void convexHull(InputArray points, OutputArray hull, bool clockwise=false, bool returnPoints=true)

		points��ݔ���YӍ�����Ԟ�����c������(vector)����Mat��
		hull��ݔ���YӍ�������c������(vector)��
		lockwise��������ˣ����true��형rᘣ�false����rᘡ�
		*/
	}

	/// �����������͹��
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng2.uniform(0, 255), rng2.uniform(0, 255), rng2.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	/// �ѽ����ʾ�ڴ���
	namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);
	imshow("Hull demo", drawing);
}
