#include "Webcam.h"
#include "Texture.h"

#include <iostream>

Webcam::Webcam(GLFWwindow* window) : window(window)
{
    capture = new cv::VideoCapture(0);
}

Webcam::~Webcam()
{
    delete capture;
}

Texture* Webcam::getWebcamFrame()
{
    detectionPoints.clear();
    resizedDetectionPoints.clear();

    cv::Mat frame;
    cv::Mat result;
    *capture >> frame;
    cutPerson(frame, result);
    findMovement(frame);

    int imageWidth = result.cols;
    int imageHeight = result.rows;

    int screenWidth, screenHeight;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);


    cv::rectangle(result, cv::Rect(0,0, imageWidth, imageHeight), cv::Scalar(0,0,255,255), 1);
    for (auto& point : detectionPoints) {
        //Debugging
        cv::circle(result, point, 5, cv::Scalar(0, 0, 10, 15), -1);
        int pointX = ((double) point.x / imageWidth) * screenWidth;
        int pointY = screenHeight - ((double) point.y / imageHeight) * screenHeight;
        glm::vec2 realPoint = glm::vec2(pointX, pointY);
        resizedDetectionPoints.push_back(realPoint);
    }
    /*auto point = cv::Point(400, 400);
    cv::circle(result, point, 10, cv::Scalar(0, 0, 10, 15), -1);

    int pointX = ((double) point.x / imageWidth) * screenWidth;
    int pointY = screenHeight - ((double) point.y / imageHeight) * screenHeight;*/

    //resizedDetectionPoints.push_back(glm::vec2(pointX, pointY));




    texture = new Texture(result);
    return texture;
}

glm::vec2 Webcam::getResolution()
{
    if (capture) {
        unsigned width = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_WIDTH));
        unsigned height = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_HEIGHT));

        return glm::vec2(width, height);
    }
    return glm::vec2(-1, -1);
}

std::vector<unsigned char> Webcam::matToBytes(cv::Mat image) {
    std::vector<unsigned char> byteArray;
    cv::imencode(".png", image, byteArray);
    return byteArray;
}

void Webcam::findMovement(cv::Mat& frame) {

    cv::Mat frameDiff, motionMask;
    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);  // Convert to grayscale

    if (previousFrame.empty())
    {
        previousFrame = frame;
    }

    // Compute absolute difference between the current and previous frame
    cv::absdiff(frame, previousFrame, frameDiff);

    // Apply threshold to obtain the motion mask
    cv::threshold(frameDiff, motionMask, motionThreshold, 255, cv::THRESH_BINARY);

    // Apply morphological operations to remove noise
    cv::erode(motionMask, motionMask, cv::Mat());
    cv::dilate(motionMask, motionMask, cv::Mat());

    // Find contours of the motion areas
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(motionMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    detectionPoints.clear();
    for (const auto& contour : contours)
    {
        cv::Rect rectangle = cv::boundingRect(contour);
        auto point = cv::Point(rectangle.x + rectangle.width / 2, rectangle.y + rectangle.height / 2);
        detectionPoints.push_back(point);
    }

    previousFrame = frame.clone();

}

void Webcam::cutPerson(cv::Mat& frame, cv::Mat& result) {
    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    // Define the range of green color in HSV
    cv::Scalar lower_green(35, 50, 50);
    cv::Scalar upper_green(85, 255, 255);

    // Create a binary mask by thresholding the image
    cv::Mat mask;
    cv::inRange(hsv, lower_green, upper_green, mask);

    bitwise_not(mask, mask);

    // Splitting channels of the colored image
    std::vector<cv::Mat> channels;
    cv::split(frame, channels);
    cv::Mat b = channels[0];
    cv::Mat g = channels[1];
    cv::Mat r = channels[2];

    // Making list of Red, Green, Blue Channels and alpha
    std::vector<cv::Mat> rgba = { b, g, r, mask };

    // Merge rgba into a colored/multi-channeled image
    cv::merge(rgba, result);

    result = makeTransparent(result);
}

cv::Mat Webcam::makeTransparent(cv::Mat& image) {
    cv::Mat result;
    image.convertTo(result, CV_32FC4);  // Convert to float type

    std::vector<cv::Mat> channels;
    cv::split(result, channels);
    cv::Mat alpha = channels[3];

    alpha *= 0.7;  // Reduce alpha values by 50%

    cv::merge(channels, result);
    result.convertTo(result, CV_8UC4);  // Convert back to 8-bit type

    return result;
}
