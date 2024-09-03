#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include <iostream>
#include <vector>

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
  
}
int main() {
  // PrintVersion();



}
