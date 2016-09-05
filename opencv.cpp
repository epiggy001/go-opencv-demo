#include "opencv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;

class ImageOperator
{
  public:
    void read(char* filename);
    void resize(int width, int height);
    void rotate(double angle);
    void write(char* filename);
    ~ImageOperator();
  private:
    Mat m;
};

void ImageOperator::read(char* filename) {
  m  = imread(filename, IMREAD_COLOR);
}

void ImageOperator::resize(int width, int height) {
  Mat dst;
  cv::resize(m, dst, Size(width, height));
  m = dst;
}

void ImageOperator::rotate(double angle) {
  Mat dst;
  Point2f pt(m.cols/2., m.rows/2.);
  Mat r = getRotationMatrix2D(pt, angle, 1.0);
  warpAffine(m, dst, r, Size(m.cols, m.rows));
  m = dst;
}

void ImageOperator::write(char* filename) {
  imwrite(filename, m);
}

ImageOperator::~ImageOperator() {
}

void* loadImage(char* filename) {
  ImageOperator* op = new ImageOperator();
  op->read(filename);
  return static_cast<void*>(op);
}

void resizeImage(void* img, int width, int height) {
  ImageOperator* op = static_cast<ImageOperator*>(img);
  op->resize(width, height);
}

void rotateImage(void* img, double angle) {
  ImageOperator* op = static_cast<ImageOperator*>(img);
  op->rotate(angle);
}

void saveImage(void* img, char* filename) {
  ImageOperator* op = static_cast<ImageOperator*>(img);
  op->write(filename);
}

void releaseImage(void *img) {
  ImageOperator* op = static_cast<ImageOperator*>(img);
  delete op;
}
