// main.cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include "image_processing.hpp"

void displayMenu() {
    std::cout << "\nSelect an option:" << std::endl;
    std::cout << "1. Show Grayscale Image" << std::endl;
    std::cout << "2. Show HSV Image" << std::endl;
    std::cout << "3. Show Blurred Image with Custom Kernel Size" << std::endl;
    std::cout << "4. Show Thresholded Image with Custom Threshold Value" << std::endl;
    std::cout << "5. Show Cropped Image" << std::endl;
    std::cout << "6. Show Resized Image" << std::endl;
    std::cout << "7. Show Rotated Image" << std::endl;
    std::cout << "8. Apply Convolution with Custom Kernel" << std::endl;
    std::cout << "9. Apply Erosion" << std::endl;
    std::cout << "A. Apply Dilation" << std::endl;
    std::cout << "B. Apply Canny Edge Detection" << std::endl; // Canny
    std::cout << "C. Detect Color in Image" << std::endl; // Color Detection
    std::cout << "Press ESC to exit." << std::endl;
}

void handleUserChoice(char userChoice, const cv::Mat& frame) {
    switch (userChoice) {
        case '1': showGrayscale(frame); break;
        case '2': showHSV(frame); break;
        case '3': showBlurred(frame); break;
        case '4': showThresholded(frame); break;
        case '5': showCropped(frame); break;
        case '6': showResized(frame); break;
        case '7': showRotated(frame); break;
        case '8': applyConvolution(frame); break;
        case '9': applyErosion(frame); break;
        case 'A': applyDilation(frame); break;
        case 'B': applyCanny(frame); break;  
        case 'C': detectColor(frame); break; 
        default: std::cout << "Invalid choice!" << std::endl;
    }
}

int main() {
    cv::VideoCapture cap(0); // Open the default camera (0)
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera!" << std::endl;
        return -1;
    }

    char userChoice = '0';
    while (true) {
        cv::Mat frame;
        cap.read(frame); // Capture a new frame

        if (frame.empty()) {
            std::cerr << "Error: Could not read frame!" << std::endl;
            break;
        }

        displayMenu();
        std::cout << "Enter your choice (or ESC to exit): ";
        std::cin >> userChoice;

        if (userChoice == 27) { // ESC key to exit
            break;
        }

        handleUserChoice(userChoice, frame);

        if (cv::waitKey(1) == 27) { // Press ESC to exit live view
            break;
        }

        cv::destroyAllWindows(); // Close previous windows if any
    }

    cap.release(); // Release the camera
    return 0;
}
