#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/features2d.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
// Mser����Ŀ����  
std::vector<cv::Rect> mserGetPlate(cv::Mat srcImage)
{
	// HSV�ռ�ת��  
	cv::Mat gray, gray_neg;
	cv::Mat hsi;
	cv::cvtColor(srcImage, hsi, CV_BGR2HSV);
	// ͨ������  
	std::vector<cv::Mat> channels;
	cv::split(hsi, channels);
	// ��ȡhͨ��  
	gray = channels[1];
	// �Ҷ�ת��   
	cv::cvtColor(srcImage, gray, CV_BGR2GRAY);
	// ȡ��ֵ�Ҷ�  
	gray_neg = 255 - gray;
	//imshow("src", gray);
	//imshow("nsrc", gray_neg);
	
	std::vector<std::vector<cv::Point> > regContours;
	std::vector<std::vector<cv::Point> > charContours;

	// ����MSER����  
	cv::MSER mesr1(2, 10, 5000, 0.5, 0.3);
	cv::MSER mesr2(2, 10, 400, 0.1, 0.3);


	cv::Mat bboxes1;
	cv::Mat bboxes2;
	// MSER+ ���  
	mesr1(gray, regContours, bboxes1);
	// MSER-����  
	mesr2(gray_neg, charContours, bboxes2);

	cv::Mat mserMapMat = cv::Mat::zeros(srcImage.size(), CV_8UC1);
	cv::Mat mserNegMapMat = cv::Mat::zeros(srcImage.size(), CV_8UC1);

	for (int i = (int)regContours.size() - 1; i >= 0; i--)
	{
		// ���ݼ�����������mser+���  
		const std::vector<cv::Point>& r = regContours[i];
		for (int j = 0; j < (int)r.size(); j++)
		{
			cv::Point pt = r[j];
			mserMapMat.at<unsigned char>(pt) = 255;
		}
	}
	// MSER- ���  
	for (int i = (int)charContours.size() - 1; i >= 0; i--)
	{
		// ���ݼ�����������mser-���  
		const std::vector<cv::Point>& r = charContours[i];
		for (int j = 0; j < (int)r.size(); j++)
		{
			cv::Point pt = r[j];
			mserNegMapMat.at<unsigned char>(pt) = 255;
		}
	}
	// mser������  
	cv::Mat mserResMat;
	// mser+��mser-λ�����  
	mserResMat = mserMapMat & mserNegMapMat;
	//cv::imshow("mserMapMat", mserMapMat);
	//cv::imshow("mserNegMapMat", mserNegMapMat);
	cv::imshow("mserResMat", mserResMat);
	// �ղ������ӷ�϶ 

	cv::Mat mserClosedMat;
	
	
	cv::morphologyEx(mserNegMapMat, mserClosedMat,
	cv::MORPH_CLOSE, cv::Mat::ones(1, 8, CV_8UC1));
	 
	/*
	cv::Mat element1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 10), cv::Point(-1, -1));
	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 1), cv::Point(-1, -1));
	dilate(mserResMat, mserClosedMat, element1);
	cv::imshow("mserClosedMat", mserClosedMat);
	cv::waitKey(0);
	erode(mserClosedMat, mserClosedMat, element2);
	*/
	
	
	

	cv::imshow("mserClosedMat", mserClosedMat);
	// Ѱ���ⲿ����  
	std::vector<std::vector<cv::Point> > plate_contours;
	cv::findContours(mserClosedMat, plate_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	// ��ѡ���������ж����  
	std::vector<cv::Rect> candidates;
	for (size_t i = 0; i != plate_contours.size(); ++i)
	{
		// �����С������  
		cv::Rect rect = boundingRect(plate_contours[i]);
		// ��߱���  

		double wh_ratio = rect.width / double(rect.height);
		// �����ϳߴ������ж�  
		if (rect.height > 10 && wh_ratio > 2 && wh_ratio < 5)
			candidates.push_back(rect);
	}
	return  candidates;
}
int mer_main()
{
	cv::Mat srcImage =
		cv::imread("C:\\Users\\going\\Desktop\\ͼƬ\\732315862878374431.jpg");
	if (srcImage.empty())
		return-1;
	if (srcImage.cols > 1200){
		resize(srcImage, srcImage, cv::Size(srcImage.cols / 2, srcImage.rows / 2));
		
	}
	cv::imshow("src Image", srcImage);
	// ��ѡ����������  
	std::vector<cv::Rect> candidates;
	candidates = mserGetPlate(srcImage);
	// ����������ʾ  
	for (int i = 0; i < candidates.size(); ++i)
	{
		cv::imshow("rect", srcImage(candidates[i]));
		cv::waitKey();
	}
	cv::waitKey(0);
	return 0;
}