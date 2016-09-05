#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;

Mat calBack_src;
Mat calBack_hsv;
Mat calBack_hue;
int calBackbins = 25;

void Hist_and_Back(int, void *);

int calBack_main()
{
	calBack_src = imread("hand.jpg");
	if (!calBack_src.data){
		return -1;
	}

	cvtColor(calBack_src, calBack_hsv, CV_BGR2HSV);
	calBack_hue.create(calBack_hsv.size(), calBack_hsv.depth());
	int ch[] = { 0, 0 };
	
	mixChannels( &calBack_hsv, 1, &calBack_hue, 1,ch, 1);

	/*
	&hsv: 一系列输入图像的数组， 被拷贝的通道的来源
	1: 输入数组中图像的数目
	&hue: 一系列目的图像的数组， 储存拷贝的通道
	1: 目的数组中图像的数目
	ch[] = {0,0}: 通道索引对的数组，指示如何将输入图像的某一通道拷贝到目的图像的某一通道。在这里，&hsv图像的Hue(0) 通道被拷贝到&hue图像(单通道)的0 通道。
	1: 通道索引对德数目
	*/

	char * windou_image = "Source image";
	cvNamedWindow(windou_image, CV_WINDOW_AUTOSIZE);
	createTrackbar("Hue bins", windou_image, &calBackbins, 180, Hist_and_Back);

	Hist_and_Back(0, 0);
	imshow(windou_image, calBack_src);

	waitKey(0);
	return 0;

}

void Hist_and_Back(int, void *)
{
	MatND hist;
	int histSize = MAX(calBackbins, 2);
	float hue_range[] = { 0, 180 };

	const float * ranges = { hue_range };
	calcHist(&calBack_hue, 1, 0, Mat(), hist, 1, &histSize, &ranges);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
	MatND backproj;
	calcBackProject(&calBack_hue, 1, 0, hist, backproj, &ranges, 1, true);


	imshow("Backproj", backproj);

	int w = 400; int h = 400;

	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);
	for (int i = 0; i < calBackbins; i++){
		rectangle(histImg, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(0, 0, 255), -1);
	}
	imshow("histogram", histImg);


}