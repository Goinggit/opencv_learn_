#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;

int display_caption(char* caption);
int display_dst(int delay);
/// 全局变量
int DELAY_CAPTION =1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;
char window_name[] = "Filter Demo 1";

/// 函数申明int display_caption( char* caption );
int display_dst(int delay);

/** *  main 函数 */
int smooth_main(int argc, char** argv)
{
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// 载入原图像
	src = imread("tiger.jpg", 1);

	if (display_caption("Original Image") != 0){ 
		return 0; 
	}

	dst = src.clone();
	if (display_dst(DELAY_CAPTION) != 0) {
		return 0; 
	}

	/// 使用 均值平滑
	if( display_caption( "Homogeneous Blur" ) !=0 ){
		return 0; 
	}
	
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		blur(src, dst, Size(i, i), Point(-1, -1));
		/*
		src: 输入图像
		dst: 输出图像
		Size( w,h ): 定义内核大小( w 像素宽度， h 像素高度)
		Point(-1, -1): 指定锚点位置(被平滑点)， 如果是负值，取核的中心为锚点。
		*/

		if (display_dst(DELAY_BLUR) != 0){ 
			return 0;
		}
	}

	/// 使用高斯平滑
	if( display_caption( "Gaussian Blur" ) !=0 ){ 
		return 0; 
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		/*
		src: 输入图像
		dst: 输出图像
		Size(w, h): 定义内核的大小(需要考虑的邻域范围)。  和  必须是正奇数，否则将使用  和  参数来计算内核大小。
		0: x 方向标准方差， 如果是0使用内核大小计算得到。
		0: y 方向标准方差， 如果是0使用内核大小计算得到。.
		*/
		if (display_dst(DELAY_BLUR) != 0){
			return 0; 
		}
	}

	/// 使用中值平滑
	if( display_caption( "Median Blur" ) !=0 ){
		return 0; 
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		medianBlur(src, dst, i);
		/*
		src: 输入图像
		dst: 输出图像, 必须与 src 相同类型
		i: 内核大小 (只需一个值，因为我们使用正方形窗口)，必须为奇数。
		*/
		if (display_dst(DELAY_BLUR) != 0){ 
			return 0; 
		}
	}

	/// 使用双边平滑
	if( display_caption( "Bilateral Blur" ) !=0 ){
		return 0;
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		bilateralFilter(src, dst, i, i * 2, i / 2);
		/*
		src: 输入图像
		dst: 输出图像
		d: 像素的邻域直径
		i*2: 颜色空间的标准方差
		i/2: 坐标空间的标准方差(像素单位)
		*/
		if (display_dst(DELAY_BLUR) != 0){
			return 0;
		}
	}

	/// 等待用户输入
	display_caption("End: Press a key!");

	waitKey(0);
	return 0;
}

int display_caption(char* caption)
{
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption,
		Point(src.cols / 4, src.rows / 2),
		CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

	imshow(window_name, dst);
	int c = waitKey(DELAY_CAPTION);
	if (c >= 0){
		return -1; 
	}
	return 0;
}

int display_dst(int delay)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0){
		return -1; 
	}
	return 0;
}