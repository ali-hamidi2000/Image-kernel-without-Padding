#include <iostream>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void moveKernel(Mat img, float BlurKernel[3][3], Mat dst) {
  float SumOfIndex, ValueOne, ValueTwo;
  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      SumOfIndex = 0.0;
      for (int m = 0; m < 3; m++) {
        if (m == 0) {
          ValueOne = i;
        } else if (m == 1) {
          ValueOne = i + 1;
        } else if (m == 2) {
          ValueOne = i + 2;
        }

        for (int n = 0; n < 3; n++) {
          if (n == 0) {
            ValueTwo = j;
          } else if (n == 1) {
            ValueTwo = j + 1;
          } else if (n == 2) {
            ValueTwo = j + 2;
          }

          if (ValueOne > img.rows && ValueTwo > img.cols) {

          } else {
            SumOfIndex += BlurKernel[n][m] * img.at<uchar>(ValueOne, ValueTwo);
          }
        }
      }
      dst.at<uchar>(i, j) = SumOfIndex;
    }
  }
}

int main() {
  Mat img = imread("test.png", 0);
  float BlurKernel[3][3] = {
      {0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}};
    
  int dstRow = img.rows - 3 + 1;
  int dstCol = img.cols - 3 + 1;
  Mat dst(dstRow, dstCol, img.type());

  if (!img.data) {
    cout << "Error reading robot image" << endl;
    return -1;
  }
  // kernel with Blur Filter
  cout << "rows : " << img.rows << endl;
  cout << "cols : " << img.cols << endl;

  imshow("inputWindow", img);
  moveKernel(img, BlurKernel, dst);
  imshow("blur", dst);

  cout << "rows : " << dst.rows << endl;
  cout << "cols : " << dst.cols << endl;

  waitKey(0);
  destroyAllWindows();

  return 0;
}
