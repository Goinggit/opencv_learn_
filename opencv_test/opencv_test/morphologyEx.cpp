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
	开运算：
			开运算是通过先对图像腐蚀再膨胀实现的。
			能够排除小团块物体(假设物体较背景明亮）

	Closing : MORPH_CLOSE : 3  
	闭运算：
			闭运算是通过先对图像膨胀再腐蚀实现的。
			能够排除小型黑洞(黑色区域)。

	Gradient : MORPH_GRADIENT : 4  
	形态梯度(Morphological Gradient)：
	膨胀图与腐蚀图之差
	能够保留物体的边缘轮廓，如下所示:

	Top Hat : MORPH_TOPHAT : 5
	顶帽(Top Hat)：
	原图像与开运算结果图之差

	Black Hat : MORPH_BLACKHAT : 6

	黑帽(Black Hat)
	闭运算结果图与原图像之差
	*/

	int operate = morph_operator + 2;

	
	//获取一个核，Point(-1, -1)，表示锚点在中心
	Mat element = getStructuringElement(share, Size(2 * morph_kernel_size + 1, 2 * morph_kernel_size + 1), Point(-1, -1));
	//形态操作
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
	第一个参数，const string&类型的trackbarname，表示轨迹条的名字，用来代表我们创建的轨迹条。
	第二个参数，const string&类型的winname，填窗口的名字，表示这个轨迹条会依附到哪个窗口上，即对应namedWindow（）创建窗口时填的某一个窗口名。
	第三个参数，int* 类型的value，一个指向整型的指针，表示滑块的位置。并且在创建时，滑块的初始位置就是该变量当前的值。
	第四个参数，int类型的count，表示滑块可以达到的最大位置的值。PS:滑块最小的位置的值始终为0。
	第五个参数，TrackbarCallback类型的onChange，首先注意他有默认值0。这是一个指向回调函数的指针，每次滑块位置改变时，这个函数都会进行回调。并且这个函数的原型必须为void XXXX(int,void*);其中第一个参数是轨迹条的位置，第二个参数是用户数据（看下面的第六个参数）。如果回调是NULL指针，表示没有回调函数的调用，仅第三个参数value有变化。
	第六个参数，void*类型的userdata，他也有默认值0。这个参数是用户传给回调函数的数据，用来处理轨迹条事件。如果使用的第三个参数value实参是全局变量的话，完全可以不去管这个userdata参数。
 
	这个createTrackbar函数，为我们创建一个具有特定名称和范围的轨迹条（Trackbar，或者说是滑块范围控制工具），指定一个和轨迹条位置同步的变量。而且要指定回调函数onChange（第五个参数），在轨迹条位置改变的时候来调用这个回调函数。并且我们知道，创建的轨迹条显示在指定的winname（第二个参数）所代表的窗口上。
	*/

	createTrackbar("oparaton", "Morphology Demo", &morph_operator, morph_operator_max, Morphology);
	createTrackbar("element", "Morphology Demo", &morph_kernel_size, morph_kernel_size_max, Morphology);
	createTrackbar("share", "Morphology Demo", &kernel_share, share_max, Morphology);
	Morphology(0,0);

	waitKey(0);
	return 0;

}