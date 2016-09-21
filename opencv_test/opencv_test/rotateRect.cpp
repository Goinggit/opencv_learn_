#include <opencv2/opencv.hpp>

#include <iostream>
using namespace std;
using namespace cv;
int rotate_main()
{
	Mat image(200, 200, CV_8UC3, Scalar(0));
	RotatedRect rRect = RotatedRect(Point2f(100, 100), Size2f(100, 100), 60);


	Point2f vertices[4];
	rRect.points(vertices);
	cout << rRect.size << endl;
	for (int i = 0; i < 4; i++)
		line(image, vertices[i], vertices[(i + 1) % 4], Scalar(255, 255, 255));//°×É«¾ØÐÎ

	Rect brect = rRect.boundingRect();
	rectangle(image, brect, Scalar(255, 0, 0));
	cout << brect.size() << endl;

	imshow("rectangles", image);
	Mat out;
	getRectSubPix(image, brect.size()-Size(1,1),
		rRect.center, out);
	imshow("out", out);
	waitKey();
	return 0;
}