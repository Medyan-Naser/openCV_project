#include <opencv2/opencv.hpp>
#include <iostream>
#include "image_processing.hpp"
#include <thread>
#include <atomic>
#include <string>


// g++ -std=c++11 -o my_program main.cpp image_processing.cpp     -I/usr/local/include/opencv4     -L/usr/local/lib     -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio

struct ProcessingParams {
    int kernelSize = 15;
    int thresholdValue = 128;
    int cropX = 0, cropY = 0, cropWidth = 100, cropHeight = 100;
    int resizeWidth = 640, resizeHeight = 480;
    double rotationAngle = 0;
    int erosionKernelSize = 3;
    int dilationKernelSize = 3;
    int cannyLowerThreshold = 50, cannyUpperThreshold = 150;
    // cv::Scalar lowerBound = cv::Scalar(0, 0, 0); // Default lower bound for color detection
    // cv::Scalar upperBound = cv::Scalar(255, 255, 255); // Default upper bound for color detection
    int lowerBound[3] = {0, 0, 0}; // Lower bound for color detection as int array
    int upperBound[3] = {255, 255, 255}; // Upper bound for color detection as int array
    
    std::string choice = "BGR";
};


std::atomic<bool> userInputReceived(true);

void checkUserInput() {
    char userInput;
    while (true) {
        if (std::cin >> userInput) {
            std::cout << "User input: " << userInput << std::endl;
            // if (key == 27 || key == 'm' || key == 'M'){
            //     userInputReceived = true;
            // }
            userInputReceived = true;
        }
    }
}


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
    std::cout << "B. Apply Canny Edge Detection" << std::endl;
    std::cout << "C. Detect Color in Image" << std::endl;
    std::cout << "Press ESC to exit." << std::endl;
}

void gatherParameters(char choice, ProcessingParams &params) {
    switch (choice) {
        case '3':
            std::cout << "Enter kernel size for Gaussian Blur (odd number greater than 0): ";
            std::cin >> params.kernelSize;
            if (params.kernelSize <= 0 || params.kernelSize % 2 == 0) {
                std::cout << "Invalid kernel size. Using default kernel size of 15." << std::endl;
                params.kernelSize = 15;
            }
            break;
        case '4':
            std::cout << "Enter threshold value (0-255): ";
            std::cin >> params.thresholdValue;
            if (params.thresholdValue < 0 || params.thresholdValue > 255) {
                std::cout << "Invalid value. Using default threshold of 128." << std::endl;
                params.thresholdValue = 128;
            }
            break;
        case '5':
            std::cout << "Enter x, y, width, height for cropping (e.g., 50 50 100 100): ";
            std::cin >> params.cropX >> params.cropY >> params.cropWidth >> params.cropHeight;
            break;
        case '6':
            std::cout << "Enter new width and height for resizing: ";
            std::cin >> params.resizeWidth >> params.resizeHeight;
            break;
        case '7':
            std::cout << "Enter angle for rotation: ";
            std::cin >> params.rotationAngle;
            break;
        case '9':
            std::cout << "Enter kernel size for erosion (odd number > 0): ";
            std::cin >> params.erosionKernelSize;
            if (params.erosionKernelSize <= 0 || params.erosionKernelSize % 2 == 0) {
                std::cout << "Invalid size. Using default 3." << std::endl;
                params.erosionKernelSize = 3;
            }
            break;
        case 'A':
            std::cout << "Enter kernel size for dilation (odd number > 0): ";
            std::cin >> params.dilationKernelSize;
            if (params.dilationKernelSize <= 0 || params.dilationKernelSize % 2 == 0) {
                std::cout << "Invalid size. Using default 3." << std::endl;
                params.dilationKernelSize = 3;
            }
            break;
        case 'B':
            std::cout << "Enter lower and upper thresholds for Canny (e.g., 50 150): ";
            std::cin >> params.cannyLowerThreshold >> params.cannyUpperThreshold;
            break;
        case 'C':
            std::cout << "Enter lower (R G B) and upper (R G B) color bounds (e.g., 0 0 0 255 255 255): ";
            std::cin >> params.lowerBound[0] >> params.lowerBound[1] >> params.lowerBound[2]
                     >> params.upperBound[0] >> params.upperBound[1] >> params.upperBound[2];
            std::cout << "Choose a color format: (HSV/BGR) ";
            std::cin >> params.choice;
            break;
        default:
            break;
    }
}

void onTrackbarChange(int, void* userdata) {
    // Callback function does nothing; it’s here to satisfy OpenCV’s API
}



void printScalar(const cv::Scalar &scalar, const std::string &name) {
    std::cout << name << ": [";
    for (int i = 0; i < 4; ++i) {
        std::cout << scalar[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void handleUserChoice(char userChoice,  ProcessingParams &params, const cv::Mat &frame) {

    switch (userChoice) {
        case '1': showGrayscale(frame); break;
        case '2': showHSV(frame); break;
        case '3': showBlurred(frame, params.kernelSize); break;
        case '4': showThresholded(frame, params.thresholdValue); break;
        case '5': showCropped(frame, params.cropX, params.cropY, params.cropWidth, params.cropHeight); break;
        case '6': showResized(frame, params.resizeWidth, params.resizeHeight); break;
        case '7': showRotated(frame, params.rotationAngle); break;
        case '9': applyErosion(frame, params.erosionKernelSize); break;
        case 'A': applyDilation(frame, params.dilationKernelSize); break;
        case 'B': applyCanny(frame, params.cannyLowerThreshold, params.cannyUpperThreshold); break;
        case 'C': {
            // Create trackbars
            // Create a window for color detection
            const std::string windowName = "Color Detection";
            cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
            // Pair to hold references to bounds
            std::string lowerLabel = "Lower " + std::string(1, params.choice[0]);
            std::cout << lowerLabel << std::endl;
            std::cout << params.choice[0] << std::endl;

            cv::createTrackbar("Lower " + std::string(1, params.choice[0]), windowName, &params.lowerBound[0], 179, onTrackbarChange);
            cv::createTrackbar("Lower " + std::string(1, params.choice[1]), windowName, &params.lowerBound[1], 255, onTrackbarChange);
            cv::createTrackbar("Lower " + std::string(1, params.choice[2]), windowName, &params.lowerBound[2], 255, onTrackbarChange);
            cv::createTrackbar("Upper " + std::string(1, params.choice[0]), windowName, &params.upperBound[0], 179, onTrackbarChange);
            cv::createTrackbar("Upper " + std::string(1, params.choice[1]), windowName, &params.upperBound[1], 255, onTrackbarChange);
            cv::createTrackbar("Upper " + std::string(1, params.choice[2]), windowName, &params.upperBound[2], 255, onTrackbarChange);


            std::cout << params.lowerBound[0] << std::endl;

            detectColor(frame, params.choice, params.lowerBound, params.upperBound); 
            // printScalar(params.lowerBound, "Lower Bound");
            // printScalar(params.upperBound, "Upper Bound");
            break;
        }
        default: std::cout << "Invalid choice!" << std::endl; break;
    
    }
}


int main() {
    cv::VideoCapture cap(0); // Open the default camera (0)
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera!" << std::endl;
        return -1;
    }

    // userInputReceived = true;
    ProcessingParams params;
    char userChoice;
    while (true) {
        cv::destroyAllWindows();
        displayMenu();
        std::cout << "Enter your choice (or ESC to exit): ";
        std::cin >> userChoice;

        if (userChoice == 27) break; // ESC key to exit

        // Gather additional parameters if required
        gatherParameters(userChoice, params);
        
        cv::Mat frame;
        while (true) {
            cap.read(frame); // Capture a new frame
            if (frame.empty()) {
                std::cerr << "Error: Could not read frame!" << std::endl;
                break;
            }

            // Process and display the frame
            handleUserChoice(userChoice, params, frame);
            cv::imshow("Processed Frame", frame);

            char key = cv::waitKey(1);
            if (key == 27 || key == 'm' || key == 'M') break; // Exit or menu
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
