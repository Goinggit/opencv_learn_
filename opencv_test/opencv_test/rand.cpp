#include <cv.h>
#include <highgui.h>
#include <iostream>
#pragma comment( lib, "opencv_highgui2410d.lib")
#pragma comment( lib, "opencv_core2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib") 
using namespace cv;

int Drawing_Random_Lines(Mat image, char* window_name, RNG rng);
int Drawing_Random_ellipse(Mat image, char* window_name, RNG rng);
int Drawing_Random_text(Mat image, char* window_name, RNG rng);

int rand_main(int argc, char **argv)
{
	RNG rng(0xFFFFFFF0);
	char atom_window[] = "Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";

	
	Mat atom_image = Mat::zeros(500, 1000, CV_8UC3);
	Mat rook_image = atom_image;
	//Drawing_Random_ellipse(atom_image, atom_window, rng);
	//Drawing_Random_Lines(atom_image, atom_window, rng);
	Drawing_Random_text(atom_image, atom_window, rng);
	waitKey(0);
	imshow(rook_window, rook_image);
	waitKey(0);
	return 0;
}
static Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}
int Drawing_Random_Lines(Mat image, char* window_name, RNG rng)
{
	int lineType = 8;
	Point pt1, pt2;

	for (int i = 0; i < 200; i++)
	{
		pt1.x = rng.uniform(0, image.cols);
		pt1.y = rng.uniform(0, image.rows);
		pt2.x = rng.uniform(0, image.cols);
		pt2.y = rng.uniform(0, image.rows);

		line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
		imshow(window_name, image);
		if (waitKey(20) >= 0)
		{
			return -1;
		}
	}
	
	return 0;
}
int Drawing_Random_ellipse(Mat image, char* window_name, RNG rng)
{
	int lineType = 8;
	Point pt1, pt2;

	for (int i = 0; i < 200; i++)
	{
		pt1.x = rng.uniform(0, image.cols);
		pt1.y = rng.uniform(0, image.rows);
		pt2.x = rng.uniform(50, image.cols);
		pt2.y = rng.uniform(50, image.rows);

		ellipse(image, pt1, pt2, 0, 0, 0, randomColor(rng), pt2.x % 5);
		imshow(window_name, image);
		if (waitKey(20) >= 0)
		{
			return -1;
		}
	}

	return 0;
}
int Drawing_Random_text(Mat image, char* window_name, RNG rng)
{
	int lineType = 8;
	Point pt1, pt2;

	for (int i = 0; i < 10; i++)
	{
		pt1.x = rng.uniform(0, image.cols);
		pt1.y = rng.uniform(0, image.rows);
		pt2.x = rng.uniform(50, image.cols);
		pt2.y = rng.uniform(50, image.rows);

		putText(image, "I am going !!!", pt1,rng.uniform(0, 5), rng.uniform(0, 100)*0.05 + 0.1, randomColor(rng), rng.uniform(1, 10), lineType);
		imshow(window_name, image);
		if (waitKey(20) >= 0)
		{
			return -1;
		}
	}

	return 0;
}
