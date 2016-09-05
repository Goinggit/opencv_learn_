#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;

int equalizehist_main(int argc, char** argv)
{
	Mat src, dst;

	char* source_window = "Source image";
	char* equalized_window = "Equalized Image";

	/// ����Դͼ��
	src = imread("1.jpg");

	if (!src.data)
	{
		cout << "Usage: ./Histogram_Demo <path_to_image>" << endl;
		return -1;
	}

	/// תΪ�Ҷ�ͼ
	cvtColor(src, src, CV_BGR2GRAY);



	/// Ӧ��ֱ��ͼ���⻯
	equalizeHist(src, dst);

	/// ��ʾ���
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	namedWindow(equalized_window, CV_WINDOW_AUTOSIZE);

	imshow(source_window, src);
	imshow(equalized_window, dst);

	/// �ȴ��û������˳�����
	waitKey(0);

	return 0;
}