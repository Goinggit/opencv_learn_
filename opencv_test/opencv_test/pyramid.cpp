#include <cv.h>
#include <highgui.h>
#include <iostream>
#pragma comment( lib, "opencv_highgui2410d.lib")
#pragma comment( lib, "opencv_core2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib") 
using namespace cv;
using namespace std;


int pyramid_main()
{
	Mat src,dst;
	src = imread("tiger.jpg");
	if (!src.data){
		return -1;
	}
	Mat temp(src);
	dst = temp;
	namedWindow("pyramid");
	while (true){
		int c;
		c = waitKey(10);
		if (c == 'd'){
			pyrDown(temp, dst, Size(temp.cols / 2, temp.rows / 2));
		}
		else if (c == 'u'){
			pyrUp(temp, dst, Size(temp.cols * 2, temp.rows * 2));
		}
		else if (c == 27){
			break;
		}
		imshow("pyramid", temp);
		imshow("pyramid2", src);
		imshow("pyramid1", dst);
		temp = dst;
	}

	return 0;
}
/* resize
int main()
{
	Mat src, temp, dst;
	src = imread("tiger.jpg");
	if (!src.data){
		return -1;
	}
	namedWindow("pyramid");
	imshow("pyramid", src);
	waitKey(0);
	resize(src,src,Size(1500,1500));
	imshow("pyramid", src);
	waitKey(0);

}
*/