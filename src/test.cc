#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
    int board_width = 12;
    int board_height = 9;
    float square_size = 50.0f;  // 棋盘方格的实际尺寸（单位：毫米）

int main() {
  Mat img = imread("/home/yao/workspace/camera_model/workspace/c16_1/1678895361731876864.000000.jpg", IMREAD_GRAYSCALE);
  Size board_size(board_width, board_height);
  int flags = CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE;
  TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.001);
  vector<Point2f> corners;
  bool found = findChessboardCorners(img, board_size, corners, flags);
  std::cout << "found " << found << std::endl;
  if (found) {
      cornerSubPix(img, corners, Size(11, 11), Size(-1, -1), criteria);
  }
  drawChessboardCorners(img, board_size, corners, found);
  imshow("Chessboard Corners", img);
  waitKey(0);
  }