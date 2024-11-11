#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <opencv2/opencv.hpp>

void showGrayscale(const cv::Mat& frame);
void showHSV(const cv::Mat& frame);
void showBlurred(const cv::Mat& frame);
void showThresholded(const cv::Mat& frame);
void showCropped(const cv::Mat& frame);
void showResized(const cv::Mat& frame);
void showRotated(const cv::Mat& frame);
void applyConvolution(const cv::Mat& frame);
void applyErosion(const cv::Mat& frame);
void applyDilation(const cv::Mat& frame);
void applyCanny(const cv::Mat& frame);
void detectColor(const cv::Mat& frame);

#endif // IMAGE_PROCESSING_HPP
