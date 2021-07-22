#include <gflags/gflags.h>
#include "class_camera_calibrator.hpp"
#include<iostream>
#include<string> 

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;

int main()
{
	FLAGS_log_dir = "./";
	FLAGS_colorlogtostderr = true;
	google::InitGoogleLogging("calibrator");
	google::LogToStderr();
	std::vector<cv::String> images;
	// Load the images used for the calibration
	cv::glob("C:/Users/Manasa/Documents/camrera_calibration_zhang_method/images/*.jpg", images);
	std::vector<cv::Mat> vec_mat;
	for (const auto &path:images)
	{
		
		cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
		vec_mat.push_back(img);
	}

	CameraCalibrator m;
	Eigen::Matrix3d camera_matrix;
	Eigen::VectorXd k;
	std::vector<Eigen::MatrixXd> vec_extrinsics;

	m.set_input(vec_mat, cv::Size{ 7,9 }); // here 9x6 Number of inner corners per a chessboard row and column
	m.get_result(camera_matrix,k,vec_extrinsics);

	std::cout << "camera_matrix:\n" << camera_matrix << std::endl;
	std::cout << "k:\n" << k << std::endl;
	for (int i=0;i<vec_extrinsics.size();++i)
	{
		std::cout << "vec_extrinsics["<<i<<"]:\n" << vec_extrinsics[i] << std::endl;
	}
	
}