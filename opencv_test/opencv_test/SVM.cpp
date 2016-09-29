#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;

int main()
{
	// Data for visual representation
	int width = 512, height = 512;
	Mat image = Mat::zeros(height, width, CV_8UC3);

	// Set up training data
	int labels[12] = { 1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };
	Mat labelsMat(12, 1, CV_32SC1, labels);
	std::cout << labelsMat <<std::endl;

	float trainingData[12][2] = { { 255, 255 }, { 227, 155 }, { 280, 200 }, { 10, 501 }, { 511, 501 }, { 100, 501 }, { 10, 10 }, { 111, 111 } 
	, { 120, 11 }, { 488, 111 }, { 477, 115 }, { 8, 111 } };
	Mat trainingDataMat(12, 2, CV_32FC1, trainingData);


	std::cout << trainingDataMat << std::endl;
	// Set up SVM's parameters
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

	// Train the SVM
	CvSVM SVM;
	//SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);


	// auto train 
	CvSVMParams SVM_params;
	SVM_params.svm_type = CvSVM::C_SVC;
	// SVM_params.kernel_type = CvSVM::LINEAR; //CvSVM::LINEAR;
	// 线型，也就是无核
	SVM_params.kernel_type =
		CvSVM::RBF;  // CvSVM::RBF 径向基函数，也就是高斯核
	SVM_params.degree = 0.1;
	SVM_params.gamma = 1;
	SVM_params.coef0 = 0.1;
	SVM_params.C = 1;
	SVM_params.nu = 0.1;
	SVM_params.p = 0.1;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100000, 0.0001);
	SVM.train_auto(trainingDataMat, labelsMat, cv::Mat(),
		cv::Mat(), SVM_params, 10,
		CvSVM::get_default_grid(CvSVM::C),
		CvSVM::get_default_grid(CvSVM::GAMMA),
		CvSVM::get_default_grid(CvSVM::P),
		CvSVM::get_default_grid(CvSVM::NU),
		CvSVM::get_default_grid(CvSVM::COEF),
		CvSVM::get_default_grid(CvSVM::DEGREE), true);

	Vec3b green(0, 0, 255), blue(255, 0, 0);
	// Show the decision regions given by the SVM
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
		{
			Mat sampleMat = (Mat_<float>(1, 2) << i, j);
			float response = SVM.predict(sampleMat);

			if (response == 1)
				image.at<Vec3b>(j, i) = green;
			else if (response == -1)
				image.at<Vec3b>(j, i) = blue;
		}

	// Show the training data
	int thickness = -1;
	int lineType = 8;
	circle(image, Point(501, 10), 5, Scalar(0, 0, 0), thickness, lineType);
	circle(image, Point(255, 10), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
	circle(image, Point(10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

	// Show support vectors
	thickness = 2;
	lineType = 8;
	int c = SVM.get_support_vector_count();

	for (int i = 0; i < c; ++i)
	{
		const float* v = SVM.get_support_vector(i);
		circle(image, Point((int)v[0], (int)v[1]), 6, Scalar(0, 255, 0), thickness, lineType);
		std::cout << Point((int)v[0], (int)v[1]) << std::endl;
	}

	imwrite("result.png", image);        // save the image 

	imshow("SVM Simple Example", image); // show it to the user
	waitKey(0);

}