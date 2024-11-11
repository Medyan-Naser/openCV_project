#include <opencv2/opencv.hpp>
#include <vector>
#include <iostrem>


// cv::imread function - Load an image from a file
// Parameters:
//   - filename: The path to the image file to be loaded (string).
//   - flags: Flag to specify color type (optional).
//     - cv::IMREAD_COLOR: Loads the image in color (default).
//     - cv::IMREAD_GRAYSCALE: Loads the image as grayscale.
//     - cv::IMREAD_UNCHANGED: Loads the image including alpha channel.
void imageIOExample() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::imshow("Loaded Image", image); 
    cv::imwrite("output.jpg", image); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}

// cv::resize function - Resizes an image
// Parameters:
//   - src: The source image to be resized (cv::Mat).
//   - dst: The destination image (cv::Mat).
//   - dsize: The new size of the image (cv::Size).
//   - fx: Scale factor in the X direction (optional).
//   - fy: Scale factor in the Y direction (optional).
//   - interpolation: Interpolation method used to resize (optional).
//     - cv::INTER_LINEAR: Bilinear interpolation (default).
//     - cv::INTER_NEAREST: Nearest neighbor interpolation.
//     - cv::INTER_CUBIC: Bicubic interpolation.
void basicImageProcessing() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(300, 300)); 
    cv::imshow("Resized Image", resizedImage); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}

// cv::cvtColor function - Converts an image from one color space to another
// Parameters:
//   - src: The source image (cv::Mat).
//   - dst: The destination image (cv::Mat).
//   - code: The color conversion code (int).
//     - cv::COLOR_BGR2GRAY: Converts from BGR to grayscale.
//     - cv::COLOR_BGR2HSV: Converts from BGR to HSV color space.
void colorConversion() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::Mat grayImage, hsvImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); 
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV); 
    cv::imshow("Gray Image", grayImage); 
    cv::imshow("HSV Image", hsvImage); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}

// cv::GaussianBlur function - Applies a Gaussian blur to an image
// Parameters:
//   - src: The source image (cv::Mat).
//   - dst: The destination image (cv::Mat).
//   - ksize: The size of the kernel (cv::Size).
//   - sigmaX: The standard deviation in the X direction (double).
//   - sigmaY: The standard deviation in the Y direction (optional).
void filteringAndConvolution() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(15, 15), 0); 
    cv::imshow("Blurred Image", blurredImage); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}

// cv::Sobel function - Computes the Sobel derivative of an image
// Parameters:
//   - src: The source image (cv::Mat).
//   - dst: The destination image (cv::Mat).
//   - ddepth: The depth of the output image (e.g., CV_8U, CV_16S).
//   - dx: The order of the derivative in the X direction (int).
//   - dy: The order of the derivative in the Y direction (int).
//   - ksize: The size of the kernel used for the Sobel operation (int).
void filteringAndConvolution() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::Mat sobelImage;
    cv::Sobel(image, sobelImage, CV_8U, 1, 0, 3); 
    cv::imshow("Sobel Edge Detection", sobelImage); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}

// cv::Canny function - Detects edges using the Canny edge detector
// Parameters:
//   - image: The input image (cv::Mat).
//   - edges: The output edge map (cv::Mat).
//   - threshold1: The first threshold for the Canny edge detector (double).
//   - threshold2: The second threshold for the Canny edge detector (double).
void contourDetection() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::Mat grayImage, edges;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); 
    cv::Canny(grayImage, edges, 100, 200); 
    cv::imshow("Edges", edges); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}

// cv::findContours function - Finds contours in a binary image
// Parameters:
//   - image: The input binary image (cv::Mat).
//   - contours: A vector of contours (std::vector<std::vector<cv::Point>>).
//   - hierarchy: The output hierarchy (optional).
//   - mode: The contour retrieval mode (int).
//     - cv::RETR_EXTERNAL: Retrieves only the outer contours.
//     - cv::RETR_TREE: Retrieves all contours and reconstructs a full hierarchy.
void contourDetection() {
    cv::Mat image = cv::imread("input.jpg"); 
    if (image.empty()) { 
        std::cout << "Could not open or find the image!" << std::endl; 
        return; 
    }
    cv::Mat grayImage, edges, contourImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); 
    cv::Canny(grayImage, edges, 100, 200); 
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE); 
    contourImage = image.clone(); 
    cv::drawContours(contourImage, contours, -1, cv::Scalar(0, 255, 0), 2); 
    cv::imshow("Contours", contourImage); 
    cv::waitKey(0); 
    cv::destroyAllWindows();
}


int main() {
    imageIOExample();
    basicImageProcessing();
    colorConversion();
    filteringAndConvolution();
    contourDetection();
    return 0;
}
