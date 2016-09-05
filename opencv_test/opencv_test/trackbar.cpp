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
	进行 腐蚀 操作的函数是 erode 。 它接受了三个参数:
	src: 原图像
	erosion_dst: 输出图像
	element: 腐蚀操作的内核。 如果不指定，默认为一个简单的  矩阵。否则，我们就要明确指定它的形状，可以使用函数 getStructuringElement:
	Mat element = getStructuringElement( erosion_type,
										 Size( 2*erosion_size +1, 2*erosion_size+1 ),
										 Point( erosion_size, erosion_size ) );
	我们可以为我们的内核选择三种形状之一:
	矩形: MORPH_RECT
	交叉形: MORPH_CROSS
	椭圆形: MORPH_ELLIPSE
	然后，我们还需要指定内核大小，以及 锚点 位置。不指定锚点位置，则默认锚点在内核中心位置。
	就这些了，我们现在可以对图像进行腐蚀操作了。
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
	/// 创建腐蚀 Trackbar
	/*
	第一个参数，const string&类型的trackbarname，表示轨迹条的名字，用来代表我们创建的轨迹条。
	第二个参数，const string&类型的winname，填窗口的名字，表示这个轨迹条会依附到哪个窗口上，即对应namedWindow（）创建窗口时填的某一个窗口名。
	第三个参数，int* 类型的value，一个指向整型的指针，表示滑块的位置。并且在创建时，滑块的初始位置就是该变量当前的值。
	第四个参数，int类型的count，表示滑块可以达到的最大位置的值。PS:滑块最小的位置的值始终为0。
	第五个参数，TrackbarCallback类型的onChange，首先注意他有默认值0。这是一个指向回调函数的指针，每次滑块位置改变时，这个函数都会进行回调。并且这个函数的原型必须为void XXXX(int,void*);其中第一个参数是轨迹条的位置，第二个参数是用户数据（看下面的第六个参数）。如果回调是NULL指针，表示没有回调函数的调用，仅第三个参数value有变化。
	第六个参数，void*类型的userdata，他也有默认值0。这个参数是用户传给回调函数的数据，用来处理轨迹条事件。如果使用的第三个参数value实参是全局变量的话，完全可以不去管这个userdata参数。

	这个createTrackbar函数，为我们创建一个具有特定名称和范围的轨迹条（Trackbar，或者说是滑块范围控制工具），指定一个和轨迹条位置同步的变量。而且要指定回调函数onChange（第五个参数），在轨迹条位置改变的时候来调用这个回调函数。并且我们知道，创建的轨迹条显示在指定的winname（第二个参数）所代表的窗口上。
	*/
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
		&erosion_elem, max_elem,
		Erosion);

	createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
		&erosion_size, max_kernel_size,
		Erosion);

	/// 创建膨胀 Trackbar
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

