#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

int wrapAddine_main()
{
	char * source_window = "source image";
	char * warp_window = "Warp";
	char * warp_rotate_window = "wart + rotate";

	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;

	src = imread("1.jpg", CV_LOAD_IMAGE_COLOR);

	warp_dst = Mat::zeros(src.size(), src.type());

	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
	dstTri[1] = Point2f(src.cols*0.85, src.rows*0.25);
	dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);

	warp_mat = getAffineTransform(srcTri, dstTri);

	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	/*
	src: ����Դͼ��
	warp_dst : ���ͼ��
	warp_mat : ����任����
	warp_dst.size() : ���ͼ��ĳߴ�
	*/


	// ������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 1;

	/// ͨ���������תϸ����Ϣ�����ת����
	rot_mat = getRotationMatrix2D(center, angle, scale);


	/// ��ת��Ť��ͼ��
	warpAffine(src, warp_rotate_dst, rot_mat, warp_dst.size());
	/*
			src: ����Դͼ��
			warp_dst : ���ͼ��
		    warp_mat : ����任����
		    warp_dst.size() : ���ͼ��ĳߴ�
	*/

	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	namedWindow(warp_window, CV_WINDOW_AUTOSIZE);
	imshow(warp_window, warp_dst);

	namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);
	imshow(warp_rotate_window, warp_rotate_dst);

	/// �ȴ��û������ⰴ���˳�����
	waitKey(0);
	return 0;
}