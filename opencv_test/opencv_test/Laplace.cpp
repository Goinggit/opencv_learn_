#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;

using namespace cv;

int lapalce_main()
{
	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Demo";

	int c;

	/// 装载图像
	src = imread("1.jpg");
	if (!src.data){
		return 0;
	}
	GaussianBlur(src, src,Size(3,3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	/*
		函数接受了以下参数:
		src_gray: 输入图像。
		dst: 输出图像
		ddepth: 输出图像的深度。 因为输入图像的深度是 CV_8U ，这里我们必须定义 ddepth = CV_16S 以避免外溢。
		kernel_size: 内部调用的 Sobel算子的内核大小，此例中设置为3。
		scale, delta 和 BORDER_DEFAULT: 使用默认值。
	*/
	Mat abs_dst; 

	convertScaleAbs(dst, abs_dst);

	/// 显示结果
	imshow(window_name, abs_dst);

	waitKey(0);

	return 0;

}