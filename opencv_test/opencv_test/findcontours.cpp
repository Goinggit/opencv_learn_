#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace std;

using namespace cv;

Mat findcon_src; Mat findcon_src_gray;
int findcon_thresh = 100;
int findcon_max_thresh = 255;
extern RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

/** @function main */
int findcon_main(int argc, char** argv)
{
	/// ����Դͼ��
	findcon_src = imread("1.jpg");

	/// ת�ɻҶȲ�ģ��������
	cvtColor(findcon_src, findcon_src_gray, CV_BGR2GRAY);
	blur(findcon_src_gray, findcon_src_gray, Size(3, 3));

	/// ��������
	char* source_window ="Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, findcon_src);

	createTrackbar(" Canny thresh:", "Source", &findcon_thresh, findcon_max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	/// ��Canny���Ӽ���Ե
	Canny(findcon_src_gray, canny_output, findcon_thresh, findcon_thresh * 3, 3);
	/// Ѱ������
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	std::cout << hierarchy[0] << std::endl;
	std::cout << contours[0] << std::endl;
	/*
	void findContours(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Pointoffset=Point())

	void findContours(InputOutputArray image, OutputArrayOfArrays contours, int mode, int method, Point offset=Point())

	image��ݔ��D��ʹ�ð�λԪ��ͨ���D�����з�������ض������뿼�]��ͨ������O����ĈD��
	contours����������݆��������(vector)��ÿ��݆�����ǃ����c������(vector)������contours���Y�ϽY����vector< vector>��
	hierarchy�����пɟo��ݔ�����������A�ӵķ�ʽӛ�����݆����
	mode��ȡ��݆����ģʽ��
	method������݆���c�ķ�����


	mode��ȡ��݆����ģʽ�������׷N���x��

	CV_RETR_EXTERNAL��ֻȡ����ӵ�݆����
	CV_RETR_LIST��ȡ������݆�����������A��(hierarchy)��
	CV_RETR_CCOMP��ȡ������݆��������ɃɌӵ��A�ӣ����A�Ӟ����������ڶ��A�Ӟ�Ȳ����Ĳ��ֵ�݆����������Ȳ������N�������������A�ӡ�
	CV_RETR_TREE��ȡ������݆������ȫ�A�ӵķ�ʽ���档
	method������݆���c�ķ����������׷N���x��

	CV_CHAIN_APPROX_NONE����������݆���c��
	CV_CHAIN_APPROX_SIMPLE����ˮƽ����ֱ�����Ǿ������^β�c�����Լ���݆����һ���Σ�ֻ���挦�ǵ��Ă���c��
	*/

	/// �������
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		/*
		void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

		image��ݔ��ݔ���D������݆�����ڴ�Ӱ���ϡ�
		contours����������݆��������(vector)��Ҳ����findContours()���ҵ���contours��
		contourIdx��ָ����ĳ��݆����
		color���L�u���ɫ��
		lineType���L�u�ľ��l�͑B��
		hierarchy��݆���A�ӣ�Ҳ����findContours()���ҵ���hierarchy��
		maxLevel������A�ӵ�݆��������ָ����Ҫ����݆������ݔ��hierarchy�r�ŕ����]��ݔ���ֵ�����L�u�ČӔ���
		maxLevel��

		0���L�uָ���A�ӵ�݆����
		1���L�uָ���A�ӵ�݆����������һ�A���A�ӡ�
		2���L�uָ���A�ӵ�݆����������һ�A�����A���A�ӡ�
		ʣ����������ơ�

		*/
	}

	/// �ڴ�������ʾ���
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}