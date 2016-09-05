#include <iostream> // for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;


Mat emap_src, emap_dst;
Mat map_x, map_y;
char* remap_window = "Remap demo";
int ind = 0;

/// Function Headers
void update_map(void);

/** * @function main */
int emapping_main(int argc, char** argv)
{
	/// Load the image
	emap_src = imread("1.jpg");

	/// Create dst, map_x and map_y with the same size as src:
	emap_dst.create(emap_src.size(), emap_src.type());
	map_x.create(emap_src.size(), CV_32FC1);
	map_y.create(emap_src.size(), CV_32FC1);

	/// Create window
	namedWindow(remap_window, CV_WINDOW_AUTOSIZE);

	/// Loop
	while (true)
	{
		/// Each 1 sec. Press ESC to exit the programint 
		int c = waitKey( 1000 );

		if ((char)c == 27)
		{
			break;
		}

		/// Update map_x & map_y. Then apply remap
		update_map();
		remap(emap_src, emap_dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

		/*

		src: 源图像
		dst: 目标图像，与 src 相同大小
		map_x: x方向的映射参数. 它相当于方法  的第一个参数
		map_y: y方向的映射参数. 注意 map_y 和 map_x 与 src 的大小一致。
		CV_INTER_LINEAR: 非整数像素坐标插值标志. 这里给出的是默认值(双线性插值).
		BORDER_CONSTANT: 默认

		*/

		/// Display results
		imshow(remap_window, emap_dst);
	}
	return 0;
}

/** * @function update_map * @brief Fill the map_x and map_y matrices with 4 types of mappings */
void update_map(void)
{
	ind = ind % 4;

	for (int j = 0; j < emap_src.rows; j++)
	{
		for (int i = 0; i < emap_src.cols; i++)
		{
			switch (ind)
			{
			case 0:if (i > emap_src.cols*0.25&& i < emap_src.cols*0.75&& j > emap_src.rows*0.25&& j < emap_src.rows*0.75)
			{
				map_x.at<float>(j, i) = 2 * (i - emap_src.cols*0.25) + 0.5;
				map_y.at<float>(j, i) = 2 * (j - emap_src.rows*0.25) + 0.5;
			}
				  else
				  {
					  map_x.at<float>(j, i) = 0;
					  map_y.at<float>(j, i) = 0;
				  }
				  break;
			  case 1:
				  map_x.at<float>(j, i) = i;
				  map_y.at<float>(j, i) = emap_src.rows - j;
				  break;
			  case 2:
				  map_x.at<float>(j, i) = emap_src.cols - i;
				  map_y.at<float>(j, i) = j;
				  break;
			  case 3:
				  map_x.at<float>(j, i) = emap_src.cols - i;
				  map_y.at<float>(j, i) = emap_src.rows - j;
				  break;
			} // end of switch
		}
	}
	ind++;
}