#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

/*
    we are assuming here that every image matrix and kernel matrix will have the same rowxcolumn
    and will always be a 3x3 matric
*/
float apply_effect(cv::Mat image_region, std::vector<std::vector<float>> kernel_matrix) {
    float result = 0.0f;

    // ensure we have a 3x3 region
    if(image_region.rows != 3 || image_region.cols != 3) {
        std::cerr << "Error: Expected 3x3 image region" << std::endl;
        return 0.0f;
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            float pixel_value;
            if(image_region.channels() == 1) {
                pixel_value = static_cast<float>(image_region.at<uchar>(i, j));
            } else {
                cv::Vec3b pixel = image_region.at<cv::Vec3b>(i, j);
                pixel_value =
                    0.299f * pixel[2] + 0.587f * pixel[1] + 0.114f * pixel[0];  // RGB to grayscale
            }
            result += pixel_value * kernel_matrix[i][j];
        }
    }

    return result;
}

int main() {
    std::cout << "Project for matric convolution!" << std::endl;

    std::string inputImagePath = "./images/3.jpeg";
    cv::Mat inputImage = cv::imread(inputImagePath);
    if(!inputImage.data) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    std::printf("Input image loaded successfully.\n");
    std::cout << "Image dimensions: " << inputImage.rows << "x" << inputImage.cols << std::endl;
    std::cout << "Channels: " << inputImage.channels() << std::endl;
    std::cout << "Data type: " << inputImage.depth() << std::endl;

    // Gaussian Blur kernel
    std::vector<std::vector<float>> gaussian_kernel = {{1.0f / 16, 2.0f / 16, 1.0f / 16},
                                                       {2.0f / 16, 4.0f / 16, 2.0f / 16},
                                                       {1.0f / 16, 2.0f / 16, 1.0f / 16}};

    // Edge detection kernel (Sobel X)
    std::vector<std::vector<float>> sobel_x_kernel = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    // Sharpen kernel
    std::vector<std::vector<float>> sharpen_kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    // Identity kernel
    std::vector<std::vector<float>> identity_kernel = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    // Edge detection kernel 0
    std::vector<std::vector<float>> edge0_kernel = {{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}};

    // Emboss kernel
    std::vector<std::vector<float>> emboss_kernel = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};

    // Edge detection kernel 1 (Laplacian)
    std::vector<std::vector<float>> edge1_kernel = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

    // Edge detection kernel 2 (Laplacian, 8-connected)
    std::vector<std::vector<float>> edge2_kernel = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};

    // Choose which kernel to use
    auto current_kernel = edge2_kernel;

    cv::Mat outputImage = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8UC1);

    for(int i = 1; i < inputImage.rows - 1; ++i) {
        for(int j = 1; j < inputImage.cols - 1; ++j) {
            cv::Rect roi(j - 1, i - 1, 3, 3);  // (x, y, width, height)
            cv::Mat roiImage = inputImage(roi);

            // apply convolution
            float convolved_value = apply_effect(roiImage, current_kernel);

            // the result to valid pixel range [0, 255]
            convolved_value = std::max(0.0f, std::min(255.0f, convolved_value));

            // set the output pixel
            outputImage.at<uchar>(i, j) = static_cast<uchar>(convolved_value);
        }
    }

    // cv::imshow("Original Image", inputImage);
    cv::imshow("Processed Image", outputImage);

    cv::imwrite("./images/output_processed.jpg", outputImage);
    std::cout << "Processed image saved as 'output_processed.jpg'" << std::endl;

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
