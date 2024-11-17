#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <opencv2/opencv.hpp>

void showGrayscale(const cv::Mat& frame);
void showHSV(const cv::Mat& frame);
void showBlurred(const cv::Mat& frame, int kernelSize);
void showThresholded(const cv::Mat& frame, int thresholdValue);
void showCropped(const cv::Mat& frame, int x, int y, int width, int height);
void showResized(const cv::Mat& frame, int newWidth, int newHeight);
void showRotated(const cv::Mat& frame, double angle);
void applyConvolution(const cv::Mat& frame, const cv::Mat& kernel);
void applyErosion(const cv::Mat& frame, int kernelSize);
void applyDilation(const cv::Mat& frame, int kernelSize);
void applyCanny(const cv::Mat& frame, int lowerThreshold, int upperThreshold);
void detectColor(const cv::Mat& frame, const cv::Scalar& lowerBound, const cv::Scalar& upperBound);

#endif // IMAGE_PROCESSING_HPP
