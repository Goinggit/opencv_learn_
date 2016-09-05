#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
/*
  模板匹配
*/
Mat matht_img; 
Mat matht_templ; 
Mat matht_result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// 函数声明
void MatchingMethod( int, void* );

/** @主函数 */
int mathT_main(int argc, char** argv)
{
	/// 载入原图像和模板块
	matht_img = imread("1.jpg");
	matht_templ = imread("1.png");
	cvNamedWindow("templ", CV_WINDOW_AUTOSIZE);
	if (!matht_img.data){
		return -1;
	}
	if (!matht_templ.data){
		return -1;
	}
	/// 创建窗口
	namedWindow(image_window, CV_WINDOW_AUTOSIZE);
	namedWindow(result_window, CV_WINDOW_AUTOSIZE);

	/// 创建滑动条
	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);

	MatchingMethod(0, 0);

	waitKey(0);
	return 0;
}
void MatchingMethod(int, void*)
{
	/// 将被显示的原图像
	Mat img_display;
	matht_img.copyTo(img_display);

	/// 创建输出结果的矩阵
	int result_cols = matht_img.cols - matht_templ.cols + 1;
	int result_rows = matht_img.rows - matht_templ.rows + 1;

	matht_result.create(result_cols, result_rows, CV_32FC1);

	matchTemplate(matht_img, matht_templ, matht_result, match_method);
	/*
	很自然地,参数是输入图像 I, 模板图像 T, 结果图像 R 还有匹配方法 (通过滑动条给出)
	*/
	normalize(matht_result, matht_result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;
	minMaxLoc(matht_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	/*
	result: 匹配结果矩阵
	&minVal 和 &maxVal: 在矩阵 result 中存储的最小值和最大值
	&minLoc 和 &maxLoc: 在结果矩阵中最小值和最大值的坐标.
	Mat(): 可选的掩模
	*/
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	
	/// 让我看看您的最终结果
	rectangle(img_display, matchLoc, Point(matchLoc.x + matht_templ.cols, matchLoc.y + matht_templ.rows), Scalar(0,0,255), 2, 8, 0);
	rectangle(matht_result, matchLoc, Point(matchLoc.x + matht_templ.cols, matchLoc.y + matht_templ.rows), Scalar::all(0), 2, 8, 0);

	imshow(image_window, img_display);
	imshow(result_window, matht_result);
	
	imshow("templ", matht_templ);
	
}
