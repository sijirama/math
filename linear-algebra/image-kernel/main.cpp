#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "Project for matric convolution!" << std::endl;

    std::string inputImagePath = "./images/1.jpg";
    cv::Mat inputImage = cv::imread(inputImagePath);
    if(!inputImage.data) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    std::printf("Input image loaded successfully.\n");
    std::cout << "Image dimensions: " << inputImage.rows << "x" << inputImage.cols << std::endl;

    return 0;
}
