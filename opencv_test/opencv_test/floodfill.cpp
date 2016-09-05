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
	下面是一起介绍的参数详解。除了第二个参数外，其他的参数都是共用的。
	第一个参数，InputOutputArray类型的image, 输入/输出1通道或3通道，8位或浮点图像，具体参数由之后的参数具体指明。
	第二个参数， InputOutputArray类型的mask，这是第二个版本的floodFill独享的参数，表示操作掩模,。它应该为单通道、8位、长和宽上都比输入图像 image 大两个像素点的图像。第二个版本的floodFill需要使用以及更新掩膜，所以这个mask参数我们一定要将其准备好并填在此处。需要注意的是，漫水填充不会填充掩膜mask的非零像素区域。例如，一个边缘检测算子的输出可以用来作为掩膜，以防止填充到边缘。同样的，也可以在多次的函数调用中使用同一个掩膜，以保证填充的区域不会重叠。另外需要注意的是，掩膜mask会比需填充的图像大，所以 mask 中与输入图像(x,y)像素点相对应的点的坐标为(x+1,y+1)。
	第三个参数，Point类型的seedPoint，漫水填充算法的起始点。
	第四个参数，Scalar类型的newVal，像素点被染色的值，即在重绘区域像素的新值。
	第五个参数，Rect*类型的rect，有默认值0，一个可选的参数，用于设置floodFill函数将要重绘区域的最小边界矩形区域。
	第六个参数，Scalar类型的loDiff，有默认值Scalar( )，表示当前观察像素值与其部件邻域像素值或者待加入该部件的种子像素之间的亮度或颜色之负差（lower brightness/color difference）的最大值。 
	第七个参数，Scalar类型的upDiff，有默认值Scalar( )，表示当前观察像素值与其部件邻域像素值或者待加入该部件的种子像素之间的亮度或颜色之正差（lower brightness/color difference）的最大值。
	第八个参数，int类型的flags，操作标志符，此参数包含三个部分，比较复杂，我们一起详细看看。

	低八位（第0~7位）用于控制算法的连通性，可取4 (4为缺省值) 或者 8。如果设为4，表示填充算法只考虑当前像素水平方向和垂直方向的相邻点；如果设为 8，除上述相邻点外，还会包含对角线方向的相邻点。
	高八位部分（16~23位）可以为0 或者如下两种选项标识符的组合：     
                                                                                    
	FLOODFILL_FIXED_RANGE - 如果设置为这个标识符的话，就会考虑当前像素与种子像素之间的差，否则就考虑当前像素与其相邻像素的差。也就是说，这个范围是浮动的。
	FLOODFILL_MASK_ONLY - 如果设置为这个标识符的话，函数不会去填充改变原始图像 (也就是忽略第三个参数newVal), 而是去填充掩模图像（mask）。这个标识符只对第二个版本的floodFill有用，因第一个版本里面压根就没有mask参数。

	中间八位部分，上面关于高八位FLOODFILL_MASK_ONLY标识符中已经说的很明显，需要输入符合要求的掩码。Floodfill的flags参数的中间八位的值就是用于指定填充掩码图像的值的。但如果flags中间八位的值为0，则掩码会用1来填充。
	而所有flags可以用or操作符连接起来，即“|”。例如，如果想用8邻域填充，并填充固定像素值范围，填充掩码而不是填充源图像，以及设填充值为38，那么输入的参数是这样：
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