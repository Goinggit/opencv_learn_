#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;



double alpha; /**< ���ƶԱȶ� */
int beta;  /**< �������� */

int light_main(int argc, char** argv)
{
	/// �����û��ṩ��ͼ��
	Mat image = imread(argv[1]);
	Mat new_image = Mat::zeros(image.size(), image.type());

	/// ��ʼ��
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: ";
	cin >> alpha;
	cout << "* Enter the beta value [0-100]: ";
	cin >> beta;

	/// ִ������ new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
			   
		}
	}

	/// ��������
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// ��ʾͼ��
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// �ȴ��û�����
	waitKey();
	return 0;
}