#ifndef QTOPENCVTOOLS_H
#define QTOPENCVTOOLS_H

#include <opencv2\opencv.hpp>
#include <QImage>
using namespace cv;

cv::Mat QImageToMat(QImage image);
QImage MatToQImage(const cv::Mat& mat);
bool JfzStereoImgGet(unsigned int cameraNum = 0);

#endif // QTOPENCVTOOLS_H
