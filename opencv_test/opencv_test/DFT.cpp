
#include <iostream>
#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  
using namespace cv;
using namespace std;

static void help(char* progName)
{
	cout << endl
		<< "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
		<< "The dft of an image is taken and it's power spectrum is displayed." << endl
		<< "Usage:" << endl
		<< progName << " [image_name -- default lena.jpg] " << endl << endl;
}

void dft_magnitude(Mat & I);
int DFT_main()
{

	const char* filename =  "C:\\Users\\going\\Desktop\\16260129101.jpg";

	Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("777", I);
	if (I.empty())
		return -1;
	
	dft_magnitude(I);

	return 0;
}
void dft_magnitude(Mat & I)
{
	Mat padded;                            //expand input image to optimal size
	int m = getOptimalDFTSize(I.rows);
	int n = getOptimalDFTSize(I.cols); // on the border add zero values
	copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	dft(complexI, complexI);            // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	Mat magI = planes[0];

	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	/*
	int n1 = 15;
	std::cout << (n1 & -2) << std::endl;
	std::cout << n1  << std::endl;
	*/
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
	uchar * ptr = magI.data;
	int sum = 0;
	int count = 1;
	for (int i = magI.cols / 2 - 10; i <=  magI.cols / 2 + 10; i++){
		for (int j = magI.rows / 2 - 10; j <= magI.rows / 2 + 10; j++){
		//	printf("%d\n", magI.at<uchar>(i, j));
			sum += magI.at<uchar>(i, j);
			count++;
		}
		
	}
	printf("%d\n", sum / count);
	//printf("%d\n", magI.at<uchar>(magI.cols / 2-1, magI.rows / 2 -1));
	//printf("%d\n", magI.at<Vec3b>(magI.cols / 2, magI.rows / 2)[1]);
	//printf("%d\n", magI.at<Vec3b>(magI.cols / 2, magI.rows / 2)[2]);
	//printf("%d\n", (magI.at<Vec3b>(magI.cols / 2, magI.rows / 2)[2] + magI.at<Vec3b>(magI.cols / 2, magI.rows / 2)[0] + magI.at<Vec3b>(magI.cols / 2, magI.rows / 2)[2])/3);
	imshow("Input Image", I);    // Show the result
	imshow("spectrum magnitude", magI);
	waitKey();
}