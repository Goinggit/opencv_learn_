#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;

int display_caption(char* caption);
int display_dst(int delay);
/// ȫ�ֱ���
int DELAY_CAPTION =1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;
char window_name[] = "Filter Demo 1";

/// ��������int display_caption( char* caption );
int display_dst(int delay);

/** *  main ���� */
int smooth_main(int argc, char** argv)
{
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// ����ԭͼ��
	src = imread("tiger.jpg", 1);

	if (display_caption("Original Image") != 0){ 
		return 0; 
	}

	dst = src.clone();
	if (display_dst(DELAY_CAPTION) != 0) {
		return 0; 
	}

	/// ʹ�� ��ֵƽ��
	if( display_caption( "Homogeneous Blur" ) !=0 ){
		return 0; 
	}
	
	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		blur(src, dst, Size(i, i), Point(-1, -1));
		/*
		src: ����ͼ��
		dst: ���ͼ��
		Size( w,h ): �����ں˴�С( w ���ؿ�ȣ� h ���ظ߶�)
		Point(-1, -1): ָ��ê��λ��(��ƽ����)�� ����Ǹ�ֵ��ȡ�˵�����Ϊê�㡣
		*/

		if (display_dst(DELAY_BLUR) != 0){ 
			return 0;
		}
	}

	/// ʹ�ø�˹ƽ��
	if( display_caption( "Gaussian Blur" ) !=0 ){ 
		return 0; 
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		/*
		src: ����ͼ��
		dst: ���ͼ��
		Size(w, h): �����ں˵Ĵ�С(��Ҫ���ǵ�����Χ)��  ��  ������������������ʹ��  ��  �����������ں˴�С��
		0: x �����׼��� �����0ʹ���ں˴�С����õ���
		0: y �����׼��� �����0ʹ���ں˴�С����õ���.
		*/
		if (display_dst(DELAY_BLUR) != 0){
			return 0; 
		}
	}

	/// ʹ����ֵƽ��
	if( display_caption( "Median Blur" ) !=0 ){
		return 0; 
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		medianBlur(src, dst, i);
		/*
		src: ����ͼ��
		dst: ���ͼ��, ������ src ��ͬ����
		i: �ں˴�С (ֻ��һ��ֵ����Ϊ����ʹ�������δ���)������Ϊ������
		*/
		if (display_dst(DELAY_BLUR) != 0){ 
			return 0; 
		}
	}

	/// ʹ��˫��ƽ��
	if( display_caption( "Bilateral Blur" ) !=0 ){
		return 0;
	}

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2){
		bilateralFilter(src, dst, i, i * 2, i / 2);
		/*
		src: ����ͼ��
		dst: ���ͼ��
		d: ���ص�����ֱ��
		i*2: ��ɫ�ռ�ı�׼����
		i/2: ����ռ�ı�׼����(���ص�λ)
		*/
		if (display_dst(DELAY_BLUR) != 0){
			return 0;
		}
	}

	/// �ȴ��û�����
	display_caption("End: Press a key!");

	waitKey(0);
	return 0;
}

int display_caption(char* caption)
{
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption,
		Point(src.cols / 4, src.rows / 2),
		CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

	imshow(window_name, dst);
	int c = waitKey(DELAY_CAPTION);
	if (c >= 0){
		return -1; 
	}
	return 0;
}

int display_dst(int delay)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0){
		return -1; 
	}
	return 0;
}