#include "image_processing.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

// Convert the frame to grayscale and display it
void showGrayscale(const cv::Mat& frame) {
    cv::Mat grayscaleImage;
    cv::cvtColor(frame, grayscaleImage, cv::COLOR_BGR2GRAY); // Convert the input frame to grayscale
    cv::imshow("Grayscale Image", grayscaleImage); // Display the grayscale image
}

// Convert the frame to HSV and display it
void showHSV(const cv::Mat& frame) {
    cv::Mat hsvImage;
    cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV); // Convert the input frame to HSV color space
    cv::imshow("HSV Image", hsvImage); // Display the HSV image
}

// Apply Gaussian blur to the image and display it
void showBlurred(const cv::Mat& frame, int kernelSize) {
    // Ensure the kernel size is valid
    if (kernelSize <= 0 || kernelSize % 2 == 0) {
        std::cout << "Invalid kernel size. Using default kernel size of 15." << std::endl;
        kernelSize = 15; // Set default kernel size if input is invalid
    }

    cv::Mat blurredImage;
    cv::GaussianBlur(frame, blurredImage, cv::Size(kernelSize, kernelSize), 0); // Apply Gaussian blur
    cv::imshow("Blurred Image", blurredImage); // Display the blurred image
}

// Apply thresholding to the grayscale image and display the result
void showThresholded(const cv::Mat& frame, int thresholdValue) {
    // Ensure the threshold value is valid
    if (thresholdValue < 0 || thresholdValue > 255) {
        std::cout << "Invalid threshold value. Using default threshold of 128." << std::endl;
        thresholdValue = 128; // Use default threshold if input is invalid
    }

    cv::Mat grayscaleImage, thresholdedImage;
    cv::cvtColor(frame, grayscaleImage, cv::COLOR_BGR2GRAY); // Convert to grayscale
    cv::threshold(grayscaleImage, thresholdedImage, thresholdValue, 255, cv::THRESH_BINARY); // Apply binary thresholding
    cv::imshow("Thresholded Image", thresholdedImage); // Display the thresholded image
}

// Crop the image and display it
void showCropped(const cv::Mat& frame, int x, int y, int width, int height) {
    // Ensure the cropping dimensions are valid
    if (x >= 0 && y >= 0 && x + width <= frame.cols && y + height <= frame.rows) {
        cv::Mat croppedImage = frame(cv::Rect(x, y, width, height)); // Crop the image
        cv::imshow("Cropped Image", croppedImage); // Display the cropped image
    } else {
        std::cout << "Invalid cropping dimensions!" << std::endl;
    }
}

// Resize the image and display it
void showResized(const cv::Mat& frame, int newWidth, int newHeight) {
    // Ensure valid resizing dimensions
    if (newWidth > 0 && newHeight > 0) {
        cv::Mat resizedImage;
        cv::resize(frame, resizedImage, cv::Size(newWidth, newHeight)); // Resize the image
        cv::imshow("Resized Image", resizedImage); // Display the resized image
    } else {
        std::cout << "Invalid dimensions for resizing!" << std::endl;
    }
}

// Rotate the image and display it
void showRotated(const cv::Mat& frame, double angle) {
    // Define the center of the image for rotation
    cv::Point2f center(frame.cols / 2.0f, frame.rows / 2.0f);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0); // Generate rotation matrix
    cv::Mat rotatedImage;
    cv::warpAffine(frame, rotatedImage, rotationMatrix, frame.size()); // Rotate the image
    cv::imshow("Rotated Image", rotatedImage); // Display the rotated image
}

// Apply convolution to the image and display the result
void applyConvolution(const cv::Mat& frame, const cv::Mat& kernel) {
    // Validate the kernel size
    if (kernel.empty() || kernel.rows % 2 == 0 || kernel.cols % 2 == 0) {
        std::cout << "Invalid kernel. Please provide a valid odd-sized kernel." << std::endl;
        return;
    }

    cv::Mat result;
    cv::filter2D(frame, result, -1, kernel); // Perform 2D convolution
    cv::imshow("Convolution Result", result); // Display the result of the convolution
}

// Apply erosion to the image and display the result
void applyErosion(const cv::Mat& frame, int kernelSize) {
    // Validate the kernel size
    if (kernelSize <= 0 || kernelSize % 2 == 0) {
        std::cout << "Invalid kernel size. Using default size of 3." << std::endl;
        kernelSize = 3; // Use default kernel size if input is invalid
    }

    // Define the kernel for erosion
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
    cv::Mat erodedImage;
    cv::erode(frame, erodedImage, element); // Apply erosion
    cv::imshow("Eroded Image", erodedImage); // Display the eroded image
}

// Apply dilation to the image and display the result
void applyDilation(const cv::Mat& frame, int kernelSize) {
    // Validate the kernel size
    if (kernelSize <= 0 || kernelSize % 2 == 0) {
        std::cout << "Invalid kernel size. Using default size of 3." << std::endl;
        kernelSize = 3; // Use default kernel size if input is invalid
    }

    // Define the kernel for dilation
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
    cv::Mat dilatedImage;
    cv::dilate(frame, dilatedImage, element); // Apply dilation
    cv::imshow("Dilated Image", dilatedImage); // Display the dilated image
}

// Perform Canny edge detection and display the result
void applyCanny(const cv::Mat& frame, int lowerThreshold, int upperThreshold) {
    cv::Mat edges, imgGray;
    cv::cvtColor(frame, imgGray, cv::COLOR_BGR2GRAY);
    cv::Canny(imgGray, edges, lowerThreshold, upperThreshold); // Apply Canny edge detection
    cv::imshow("Canny Edge Detection", edges); // Display edge-detected image
}


void detectColor(const cv::Mat& frame, const cv::Scalar& lowerBound, const cv::Scalar& upperBound) {
    cv::Mat mask, result;
    cv::inRange(frame, lowerBound, upperBound, mask); // Mask the image based on the color range
    cv::bitwise_and(frame, frame, result, mask); // Apply the mask to the original frame
    cv::imshow("Detected Color", result); // Display the result
}