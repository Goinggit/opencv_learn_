#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)

#include <iostream>  

using namespace cv;
using namespace std;

int loDiff = 20, upDiff = 20;
Mat image0, image, mask;
int newMaskVal = 255;

static void onMouse(int event, int x, int y, int, void*){
	if (event != CV_EVENT_LBUTTONDOWN)
		return;
	Mat dst = image;
	Point seed = Point(x, y);
	Scalar newVal = Scalar(0, 0, 0);
	Rect ccomp;
	int lo = loDiff;
	int up = upDiff;
	int flags = 8 + (newMaskVal << 8) + CV_FLOODFILL_FIXED_RANGE;

	floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo), Scalar(up, up, up), flags);
	/*
	������һ����ܵĲ�����⡣���˵ڶ��������⣬�����Ĳ������ǹ��õġ�
	��һ��������InputOutputArray���͵�image, ����/���1ͨ����3ͨ����8λ�򸡵�ͼ�񣬾��������֮��Ĳ�������ָ����
	�ڶ��������� InputOutputArray���͵�mask�����ǵڶ����汾��floodFill����Ĳ�������ʾ������ģ,����Ӧ��Ϊ��ͨ����8λ�����Ϳ��϶�������ͼ�� image ���������ص��ͼ�񡣵ڶ����汾��floodFill��Ҫʹ���Լ�������Ĥ���������mask��������һ��Ҫ����׼���ò����ڴ˴�����Ҫע����ǣ���ˮ��䲻�������Ĥmask�ķ��������������磬һ����Ե������ӵ��������������Ϊ��Ĥ���Է�ֹ��䵽��Ե��ͬ���ģ�Ҳ�����ڶ�εĺ���������ʹ��ͬһ����Ĥ���Ա�֤�������򲻻��ص���������Ҫע����ǣ���Ĥmask���������ͼ������� mask ��������ͼ��(x,y)���ص����Ӧ�ĵ������Ϊ(x+1,y+1)��
	������������Point���͵�seedPoint����ˮ����㷨����ʼ�㡣
	���ĸ�������Scalar���͵�newVal�����ص㱻Ⱦɫ��ֵ�������ػ��������ص���ֵ��
	�����������Rect*���͵�rect����Ĭ��ֵ0��һ����ѡ�Ĳ�������������floodFill������Ҫ�ػ��������С�߽��������
	������������Scalar���͵�loDiff����Ĭ��ֵScalar( )����ʾ��ǰ�۲�����ֵ���䲿����������ֵ���ߴ�����ò�������������֮������Ȼ���ɫ֮���lower brightness/color difference�������ֵ�� 
	���߸�������Scalar���͵�upDiff����Ĭ��ֵScalar( )����ʾ��ǰ�۲�����ֵ���䲿����������ֵ���ߴ�����ò�������������֮������Ȼ���ɫ֮���lower brightness/color difference�������ֵ��
	�ڰ˸�������int���͵�flags��������־�����˲��������������֣��Ƚϸ��ӣ�����һ����ϸ������

	�Ͱ�λ����0~7λ�����ڿ����㷨����ͨ�ԣ���ȡ4 (4Ϊȱʡֵ) ���� 8�������Ϊ4����ʾ����㷨ֻ���ǵ�ǰ����ˮƽ����ʹ�ֱ��������ڵ㣻�����Ϊ 8�����������ڵ��⣬��������Խ��߷�������ڵ㡣
	�߰�λ���֣�16~23λ������Ϊ0 ������������ѡ���ʶ������ϣ�     
                                                                                    
	FLOODFILL_FIXED_RANGE - �������Ϊ�����ʶ���Ļ����ͻῼ�ǵ�ǰ��������������֮��Ĳ����Ϳ��ǵ�ǰ���������������صĲҲ����˵�������Χ�Ǹ����ġ�
	FLOODFILL_MASK_ONLY - �������Ϊ�����ʶ���Ļ�����������ȥ���ı�ԭʼͼ�� (Ҳ���Ǻ��Ե���������newVal), ����ȥ�����ģͼ��mask���������ʶ��ֻ�Եڶ����汾��floodFill���ã����һ���汾����ѹ����û��mask������

	�м��λ���֣�������ڸ߰�λFLOODFILL_MASK_ONLY��ʶ�����Ѿ�˵�ĺ����ԣ���Ҫ�������Ҫ������롣Floodfill��flags�������м��λ��ֵ��������ָ���������ͼ���ֵ�ġ������flags�м��λ��ֵΪ0�����������1����䡣
	������flags������or��������������������|�������磬�������8������䣬�����̶�����ֵ��Χ�����������������Դͼ���Լ������ֵΪ38����ô����Ĳ�����������
	*/
	imshow("image", dst);
}

int floodfill_main(int argc, char** argv){
	char* filename = "1.jpg";
	image0 = imread(filename, 1);
	image0.copyTo(image);

	mask.create(image0.rows + 2, image0.cols + 2, CV_8UC1);
	cv::rectangle(mask, cvPoint(0, 0), cvPoint(100, 100), cvScalar(255, 255, 255), 8);

	namedWindow("image", 1);
	createTrackbar("lo_diff", "image", &loDiff, 255, 0);
	createTrackbar("up_diff", "image", &upDiff, 255, 0);

	imshow("image", image);
	imshow("22", mask);
	setMouseCallback("image", onMouse, 0);

	waitKey(0);
	return 0;
}