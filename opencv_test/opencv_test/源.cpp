#pragma comment( lib, "opencv_highgui2410d.lib")
#pragma comment( lib, "opencv_core2410d.lib")
#include<opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
int main_1()
{
	Mat A(2,2,CV_8UC3, Scalar(0,0,255));
	//Mat A = imread("tiger.jpg", CV_LOAD_IMAGE_COLOR);
	if (!A.data)
	{
		std::cout << " No image data \n ";
		waitKey(0);
		return -1;
	}
	randu(A, Scalar::all(0), Scalar::all(255));
	std::cout << "M = " << format(A, "python")<< std::endl;
	system("pause");
}
/*
int main()
{
	Mat A;
	A = imread("tiger.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("1", CV_WINDOW_AUTOSIZE);
	
	if (!A.data)
	{
		std::cout << " No image data \n ";
		waitKey(0);
		return -1;
	}
	Mat D(A, Rect(10, 10, 700, 700));
	Mat E = A(Range::all(), Range(1, 700));
	imshow("1",E);
	waitKey(0);
}
*/
/*
int main(){
	IplImage* img = cvLoadImage("1.jpg", CV_LOAD_IMAGE_COLOR);
	cvRectangle(img, cvPoint(5, 10), cvPoint(200, 200), cvScalar(255 ,255, 255, 255));
	cvNamedWindow("Image_show", CV_WINDOW_AUTOSIZE);
	cvShowImage("Image_show", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Image_show");
}
*/
/*
int main()
{
	cvNamedWindow("2", CV_WINDOW_AUTOSIZE);
	CvCapture * capture = cvCreateFileCapture("1.avi");
	IplImage * frame;
	while (1){
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage("2", frame);
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("2");
}
*/
/*int main()
{
	IplImage* img = cvLoadImage("1.jpg", CV_LOAD_IMAGE_COLOR);
	cvNamedWindow("Image_show", CV_WINDOW_AUTOSIZE);
	cvShowImage("Image_show", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Image_show");
	return 0;
}
*/