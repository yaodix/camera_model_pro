#include <iostream>
#include <vector>

#include <eigen3/Eigen/Dense>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core/eigen.hpp>


#include <camera_model/camera_models/CameraFactory.h>

using namespace cv;
using namespace std;

int board_width = 8;
int board_height = 11;
float square_size = 50.0f;  // 棋盘方格的实际尺寸（单位：毫米）

void PrintVersion() {
 cout << "OpenCV version : " << CV_VERSION << endl;
  cout << "Major version : " << CV_MAJOR_VERSION << endl;
  cout << "Minor version : " << CV_MINOR_VERSION << endl;
  cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;
}

// 
void test_findcorners() {
  Mat img = imread("/home/yao/workspace/camera_model/workspace/c16_1/1678895361731876864.000000.jpg", IMREAD_GRAYSCALE);
  Size board_size(board_width, board_height);
  int flags = CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE;
  TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.001);
  vector<Point2f> corners;
  // bool found = findChessboardCorners(img, board_size, corners, flags);
  bool found = cv::findChessboardCornersSB(img, board_size, corners, cv::CALIB_CB_EXHAUSTIVE | cv::CALIB_CB_ACCURACY);
  std::cout << "found " << found << std::endl;
  // if (found) {
  //     cornerSubPix(img, corners, Size(11, 11), Size(-1, -1), criteria);
  // }
  drawChessboardCorners(img, board_size, corners, found);
  imshow("Chessboard Corners", img);
  waitKey(0);

}

int test_proj() {
  return 0;
}

int test_undistort() {
  Mat img = imread("/home/yao/workspace/camera_model_gw/workspace/c16_1/1678895361731876864.000000.jpg", IMREAD_GRAYSCALE);
  camera_model::CameraPtr cam;
  std::string camera_model_file = "/home/yao/workspace/camera_model_gw/camera_camera_calib.yaml";
  cam = camera_model::CameraFactory::instance()->generateCameraFromYamlFile(camera_model_file);

  cv::Mat map1, map2;
  Eigen::AngleAxisd rotation_vectorX_(0 / 6, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd rotation_vectorY_(0/6,  Eigen::Vector3d::UnitY());    
  Eigen::AngleAxisd rotation_vectorZ_(0,  Eigen::Vector3d::UnitZ());  

  Eigen::Matrix3d rotation_matrix_ = rotation_vectorX_.toRotationMatrix() * rotation_vectorY_.toRotationMatrix() * rotation_vectorZ_.toRotationMatrix();
  cv::Mat rmat;
  cv::eigen2cv(rotation_matrix_, rmat);
  cam->initUndistortRectifyMap(map1, map2, 500, 500,cv::Size(0,0), -1, -1, rmat);

  cv::Mat undistorted_img;
  cv::remap(img, undistorted_img, map1, map2, cv::INTER_LINEAR);

  imshow("Undistorted Image", undistorted_img);
  waitKey(0);

  return 0;
}

int main() {
  // PrintVersion();

test_undistort();


}
