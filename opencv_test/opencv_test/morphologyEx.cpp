#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;
using namespace std;

int kernel_share = 0;
int operation = 0;
int morph_operator = 0;
Mat morph_src, morph_dst;
int morph_kernel_size = 0;
void Morphology(int, void *)
{
	/*
	share meaning;

	MORPH_RECT : 0

	MORPH_CROSS : 1

	MORPH_ELLIPSE : 2
	*/
	
	int share = kernel_share;
	
	/*
	operate meaning;

	Opening: MORPH_OPEN : 2 
	�����㣺
			��������ͨ���ȶ�ͼ��ʴ������ʵ�ֵġ�
			�ܹ��ų�С�ſ�����(��������ϱ���������

	Closing : MORPH_CLOSE : 3  
	�����㣺
			��������ͨ���ȶ�ͼ�������ٸ�ʴʵ�ֵġ�
			�ܹ��ų�С�ͺڶ�(��ɫ����)��

	Gradient : MORPH_GRADIENT : 4  
	��̬�ݶ�(Morphological Gradient)��
	����ͼ�븯ʴͼ֮��
	�ܹ���������ı�Ե������������ʾ:

	Top Hat : MORPH_TOPHAT : 5
	��ñ(Top Hat)��
	ԭͼ���뿪������ͼ֮��

	Black Hat : MORPH_BLACKHAT : 6

	��ñ(Black Hat)
	��������ͼ��ԭͼ��֮��
	*/

	int operate = morph_operator + 2;

	
	//��ȡһ���ˣ�Point(-1, -1)����ʾê��������
	Mat element = getStructuringElement(share, Size(2 * morph_kernel_size + 1, 2 * morph_kernel_size + 1), Point(-1, -1));
	//��̬����
	morphologyEx(morph_src, morph_dst, operate,element);
	imshow("Morphology Demo", morph_dst);
}

int morphology_main()
{
	int morph_kernel_size_max = 20;
	int morph_operator_max = 4;
	int share_max = 2;
	morph_src = imread("going.png");
	if (!morph_src.data){
		return -1;
	}
	namedWindow("Morphology Demo", CV_WINDOW_AUTOSIZE);
	/*
	��һ��������const string&���͵�trackbarname����ʾ�켣�������֣������������Ǵ����Ĺ켣����
	�ڶ���������const string&���͵�winname����ڵ����֣���ʾ����켣�����������ĸ������ϣ�����ӦnamedWindow������������ʱ���ĳһ����������
	������������int* ���͵�value��һ��ָ�����͵�ָ�룬��ʾ�����λ�á������ڴ���ʱ������ĳ�ʼλ�þ��Ǹñ�����ǰ��ֵ��
	���ĸ�������int���͵�count����ʾ������Դﵽ�����λ�õ�ֵ��PS:������С��λ�õ�ֵʼ��Ϊ0��
	�����������TrackbarCallback���͵�onChange������ע������Ĭ��ֵ0������һ��ָ��ص�������ָ�룬ÿ�λ���λ�øı�ʱ���������������лص����������������ԭ�ͱ���Ϊvoid XXXX(int,void*);���е�һ�������ǹ켣����λ�ã��ڶ����������û����ݣ�������ĵ�����������������ص���NULLָ�룬��ʾû�лص������ĵ��ã�������������value�б仯��
	������������void*���͵�userdata����Ҳ��Ĭ��ֵ0������������û������ص����������ݣ���������켣���¼������ʹ�õĵ���������valueʵ����ȫ�ֱ����Ļ�����ȫ���Բ�ȥ�����userdata������
 
	���createTrackbar������Ϊ���Ǵ���һ�������ض����ƺͷ�Χ�Ĺ켣����Trackbar������˵�ǻ��鷶Χ���ƹ��ߣ���ָ��һ���͹켣��λ��ͬ���ı���������Ҫָ���ص�����onChange����������������ڹ켣��λ�øı��ʱ������������ص���������������֪���������Ĺ켣����ʾ��ָ����winname���ڶ���������������Ĵ����ϡ�
	*/

	createTrackbar("oparaton", "Morphology Demo", &morph_operator, morph_operator_max, Morphology);
	createTrackbar("element", "Morphology Demo", &morph_kernel_size, morph_kernel_size_max, Morphology);
	createTrackbar("share", "Morphology Demo", &kernel_share, share_max, Morphology);
	Morphology(0,0);

	waitKey(0);
	return 0;

}