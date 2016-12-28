#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** 函数声明 */
void detectAndDisplay(Mat frame);

/** 全局变量 */ 
string face_cascade1_name_3_4 = "trainout3-4.xml";
string face_cascade1_name_3_3 = "us.xml";
string face_cascade1_name_3_0 = "au.xml";
//char *pic_name = "C:\\Users\\going\\Desktop\\图片\\16260632501.jpg";
char *pic_name = "C:\\Users\\going\\Desktop\\图片\\16270977001.jpg";
CascadeClassifier Cplate3_0;
CascadeClassifier Cplate3_3;
CascadeClassifier Cplate3_4;



/** @主函数 */
int car_plate_main(int argc, const char** argv)
{

	//-- 1. 加载级联分类器文件
	if (!Cplate3_0.load(face_cascade1_name_3_0)){ printf("--(!)Error loading\n"); return -1; };
	if (!Cplate3_3.load(face_cascade1_name_3_3)){ printf("--(!)Error loading\n"); return -1; };
	if (!Cplate3_4.load(face_cascade1_name_3_4)){ printf("--(!)Error loading\n"); return -1; };

	std::vector<Rect> plate_rect3_0;
	std::vector<Rect> plate_rect3_3;
	std::vector<Rect> plate_rect3_4;
	Mat plate3_0;
	Mat plate3_3;
	Mat plate3_4;
	
	plate3_0 = imread(pic_name);
	plate3_3 = imread(pic_name);
	plate3_4 = imread(pic_name);
	
	//plate = imread("C:\\Users\\going\\Desktop\\图片\\16261054301.jpg");
	//plate = imread("C:\\Users\\going\\Desktop\\图片\\16264834201.jpg");
	//plate = imread("C:\\Users\\going\\Desktop\\图片\\16263281901.jpg");
	//plate = imread("C:\\Users\\going\\Desktop\\图片\\16261239801.jpg");
	//plate = imread("C:\\Users\\going\\Desktop\\图片\\16261202101.jpg");
	//plate = imread("C:\\Users\\going\\Desktop\\图片\\16283425901.jpg");
	//plate = imread("C:\\Users\\going\\Desktop\\新建文件夹 (3)\\u=4015189979,2073445481&fm=21&gp=0.jpg");
	//imshow("666", plate);
	if (!plate3_0.data){
		return 0;
	}
	if (plate3_0.cols > 1200){
		resize(plate3_0, plate3_0, Size(plate3_0.cols / 2, plate3_0.rows / 2));
		resize(plate3_3, plate3_3, Size(plate3_3.cols / 2, plate3_3.rows / 2));
		resize(plate3_4, plate3_4, Size(plate3_4.cols / 2, plate3_4.rows / 2));
	}
	Cplate3_0.detectMultiScale(plate3_0, plate_rect3_0, 1.1, 5, 0, Size(60, 16));
	std::cout << "==============" << std::endl;
	for (int i = 0; i < plate_rect3_0.size(); i++){
		
		rectangle(plate3_0,
			plate_rect3_0[i].tl(),
			plate_rect3_0[i].br(),
			Scalar(0, 255, 255),
			1,
			8);
		std::cout << "has a car_plate!!!!" << std::endl;

	}

	std::cout << "==============" << std::endl;
	Cplate3_3.detectMultiScale(plate3_3, plate_rect3_3, 1.1, 5, 0, Size(60, 16));
	for (int i = 0; i < plate_rect3_3.size(); i++){

		rectangle(plate3_3,
			plate_rect3_3[i].tl(),
			plate_rect3_3[i].br(),
			Scalar(0, 255, 255),
			1,
			8);
		std::cout << "has a car_plate!!!!" << std::endl;

	}

	std::cout << "==============" << std::endl;
	Cplate3_4.detectMultiScale(plate3_4, plate_rect3_4, 1.1, 5, 0, Size(60, 16));
	for (int i = 0; i < plate_rect3_4.size(); i++){

		rectangle(plate3_4,
			plate_rect3_4[i].tl(),
			plate_rect3_4[i].br(),
			Scalar(0, 255, 255),
			1,
			8);
		std::cout << "has a car_plate!!!!" << std::endl;

	}


	imshow("3.0", plate3_0);
	waitKey(0);
	imshow("3.3", plate3_3);
	waitKey(0);
	imshow("3.4", plate3_4);
	waitKey(0);

	return 0;
}

/** @函数 detectAndDisplay */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <ctype.h>
#include <stdio.h>

static void help(void)
{
	printf("\n This sample demonstrates cascade's convertation \n"
		"Usage:\n"
		"./convert_cascade --size=\"<width>x<height>\"<convertation size> \n"
		"                   input_cascade_path \n"
		"                   output_cascade_filename\n"
		"Example: \n"
		"./convert_cascade --size=640x480 ../../opencv/data/haarcascades/haarcascade_eye.xml ../../opencv/data/haarcascades/test_cascade.xml \n"
		);
}

int xxxx_main(int argc, char** argv)
{
	const char* size_opt = "--size=";
	char comment[1024];
	CvHaarClassifierCascade* cascade = 0;
	CvSize size;

	help();

	if (argc != 4 || strncmp(argv[1], size_opt, strlen(size_opt)) != 0)
	{
		help();
		return -1;
	}

	sscanf(argv[1], "--size=%ux%u", &size.width, &size.height);
	cascade = cvLoadHaarClassifierCascade(argv[2], size);

	if (!cascade)
	{
		fprintf(stderr, "Input cascade could not be found/opened\n");
		return -1;
	}

	sprintf(comment, "Automatically converted from %s, window size = %dx%d", argv[2], size.width, size.height);
	cvSave(argv[3], cascade, 0, comment, cvAttrList(0, 0));
	return 0;
}

#ifdef _EiC
main(1, "facedetect.c");
#endif