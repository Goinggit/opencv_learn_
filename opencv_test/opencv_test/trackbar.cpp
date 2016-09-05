#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;

Mat tra_src, erosion_dst, dilation_dst;
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

//fuction Erosion 
void Erosion(int, void *)
{
	int erosion_type;
	if (erosion_elem == 0){
		erosion_type = MORPH_RECT;
	}
	else if(erosion_elem == 1){
		erosion_type = MORPH_CROSS;
	}
	else if (erosion_elem == 2){
		erosion_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1),Point(-1,-1));
	erode(tra_src, erosion_dst, element);
	/*
	���� ��ʴ �����ĺ����� erode �� ����������������:
	src: ԭͼ��
	erosion_dst: ���ͼ��
	element: ��ʴ�������ںˡ� �����ָ����Ĭ��Ϊһ���򵥵�  ���󡣷������Ǿ�Ҫ��ȷָ��������״������ʹ�ú��� getStructuringElement:
	Mat element = getStructuringElement( erosion_type,
										 Size( 2*erosion_size +1, 2*erosion_size+1 ),
										 Point( erosion_size, erosion_size ) );
	���ǿ���Ϊ���ǵ��ں�ѡ��������״֮һ:
	����: MORPH_RECT
	������: MORPH_CROSS
	��Բ��: MORPH_ELLIPSE
	Ȼ�����ǻ���Ҫָ���ں˴�С���Լ� ê�� λ�á���ָ��ê��λ�ã���Ĭ��ê�����ں�����λ�á�
	����Щ�ˣ��������ڿ��Զ�ͼ����и�ʴ�����ˡ�
	*/

	imshow("Erosion Demo", erosion_dst);
}

void Dilation(int, void *)
{
	int dilation_type;
	if (dilation_elem == 0){
		dilation_type = MORPH_RECT;
	}
	else if (dilation_elem == 1){
		dilation_type = MORPH_CROSS;
	}
	else if (dilation_elem == 2){
		dilation_type = MORPH_ELLIPSE;
	}
	/*
	
	*/
	Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(-1, -1));
	dilate(tra_src, dilation_dst, element);
	
	imshow("Dilation Demo", dilation_dst);
}

int erosin_main()
{
	tra_src = imread("going.png");
	if (!tra_src.data)
	{
		return-1;
	}
	namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);
	/// ������ʴ Trackbar
	/*
	��һ��������const string&���͵�trackbarname����ʾ�켣�������֣������������Ǵ����Ĺ켣����
	�ڶ���������const string&���͵�winname����ڵ����֣���ʾ����켣�����������ĸ������ϣ�����ӦnamedWindow������������ʱ���ĳһ����������
	������������int* ���͵�value��һ��ָ�����͵�ָ�룬��ʾ�����λ�á������ڴ���ʱ������ĳ�ʼλ�þ��Ǹñ�����ǰ��ֵ��
	���ĸ�������int���͵�count����ʾ������Դﵽ�����λ�õ�ֵ��PS:������С��λ�õ�ֵʼ��Ϊ0��
	�����������TrackbarCallback���͵�onChange������ע������Ĭ��ֵ0������һ��ָ��ص�������ָ�룬ÿ�λ���λ�øı�ʱ���������������лص����������������ԭ�ͱ���Ϊvoid XXXX(int,void*);���е�һ�������ǹ켣����λ�ã��ڶ����������û����ݣ�������ĵ�����������������ص���NULLָ�룬��ʾû�лص������ĵ��ã�������������value�б仯��
	������������void*���͵�userdata����Ҳ��Ĭ��ֵ0������������û������ص����������ݣ���������켣���¼������ʹ�õĵ���������valueʵ����ȫ�ֱ����Ļ�����ȫ���Բ�ȥ�����userdata������

	���createTrackbar������Ϊ���Ǵ���һ�������ض����ƺͷ�Χ�Ĺ켣����Trackbar������˵�ǻ��鷶Χ���ƹ��ߣ���ָ��һ���͹켣��λ��ͬ���ı���������Ҫָ���ص�����onChange����������������ڹ켣��λ�øı��ʱ������������ص���������������֪���������Ĺ켣����ʾ��ָ����winname���ڶ���������������Ĵ����ϡ�
	*/
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
		&erosion_elem, max_elem,
		Erosion);

	createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
		&erosion_size, max_kernel_size,
		Erosion);

	/// �������� Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
		&dilation_elem, max_elem,
		Dilation);

	createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
		&dilation_size, max_kernel_size,
		Dilation);

	/// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	waitKey(0);
	return 0;
}

