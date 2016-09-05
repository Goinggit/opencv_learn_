#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

void MyEllipse(Mat &img, double angle);
void MyLine(Mat img, Point start, Point end);
void MyFilledCircle(Mat img, int w);
int draw()
{
	/// ��������
	char atom_window[] ="Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";
	int x = 500;
	int y = 1000;
	namedWindow(atom_window);
	namedWindow(rook_window);
	//namedWindow(rook_window);
	//������ȫ�����صĿ�ͼ��
	Mat atom_image = Mat::zeros(x, y, CV_8UC3);
	Mat rook_image = Mat::zeros(x, y, CV_8UC3);
	MyEllipse(atom_image, 0);
	MyEllipse(atom_image, 90);
	MyEllipse(atom_image, 45);
	MyEllipse(atom_image, -45);
	MyLine(atom_image, Point(x / 2, y / 4), Point(x / 6, y / 8));
	MyFilledCircle(atom_image, 100);

	rectangle(rook_image,
		Point(0+20, 7 * 100 / 8.0),
		Point(y-20, x-20),
		Scalar(0, 255, 255),
		1,
		8);
	imshow(atom_window, atom_image);
	imshow(rook_window, rook_image);

	waitKey();
	return 0;
}
void MyEllipse(Mat &img, double angle)
{
	int thickness = 5;
	int lineType = 8;
	int x = img.rows;
	
	int y = img.cols;
	//std::cout << "x = " << Point(x / 2.0, y / 2.0) << std::endl;
	ellipse(img,
		Point(y / 2.0, x / 2.0),
		Size(x / 4.0, y / 16.0),
		angle,
		0,
		360,
		Scalar(255, 0, 0),
		thickness,
		lineType);
	/*
		��Բ��������ͼ�� img ��
		��Բ����Ϊ��(w / 2.0, w / 2.0) ���Ҵ�Сλ�ھ���(w / 4.0, w / 16.0) ��
		��Բ��ת�Ƕ�Ϊ angle
		��Բ��չ�Ļ��ȴ� 0 �ȵ� 360 ��
		ͼ����ɫΪ Scalar(255, 255, 0) ������ɫ
		����Բ���ߴ�Ϊ thickness ���˴���2
	*/
}
void MyLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		start,
		end,
		Scalar(0, 255, 0),
		thickness,
		lineType);
	/*
	��һ���ӵ� start ���� end ��ֱ�߶�
	���߶ν�������ͼ�� img ��
	�ߵ���ɫ�� Scalar( 0, 0, 0) �����壬�ڴ�����ӦRGBֵΪ ��ɫ
	�ߵĴ�ϸ�� thickness �趨(�˴���Ϊ 2)
	����Ϊ8��ͨ (lineType = 8)
	*/
}
void MyFilledCircle(Mat img,int w)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		Point(img.cols/2, img.rows/2),
		w / 32.0,
		Scalar(0, 0, 255),
		thickness,
		lineType);
	/*
	Բ��������ͼ�� ( img )��
	Բ���ɵ� center ����
	Բ�İ뾶Ϊ: w/32.0
	Բ����ɫΪ: Scalar(0, 0, 255) ����BGR�ĸ�ʽΪ ��ɫ
	�ߴֶ���Ϊ thickness = -1, ��˴�Բ�������
	*/
}