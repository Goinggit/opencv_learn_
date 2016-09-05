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
	src: 输入源图像
	warp_dst : 输出图像
	warp_mat : 仿射变换矩阵
	warp_dst.size() : 输出图像的尺寸
	*/


	// 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 1;

	/// 通过上面的旋转细节信息求得旋转矩阵
	rot_mat = getRotationMatrix2D(center, angle, scale);


	/// 旋转已扭曲图像
	warpAffine(src, warp_rotate_dst, rot_mat, warp_dst.size());
	/*
			src: 输入源图像
			warp_dst : 输出图像
		    warp_mat : 仿射变换矩阵
		    warp_dst.size() : 输出图像的尺寸
	*/

	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	namedWindow(warp_window, CV_WINDOW_AUTOSIZE);
	imshow(warp_window, warp_dst);

	namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);
	imshow(warp_rotate_window, warp_rotate_dst);

	/// 等待用户按任意按键退出程序
	waitKey(0);
	return 0;
}