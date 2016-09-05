#include <iostream> // for standard I/O
#include <string>   // for strings


#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;
int video_main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}
	Mat frame;
	Mat edges;

	bool stop = false;

	
	
	while (!stop)
	{
		cap >> frame;
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("µ±Ç°ÊÓÆµ", edges);
		if (waitKey(30) >= 0)
			stop = true;

	}
	return 0;
}