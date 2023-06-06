#include "Webcam.h"
#include "Texture.h"

Webcam::Webcam()
{

    capture = cv::VideoCapture(0);
}

Webcam::~Webcam()
{
}

Texture* Webcam::getWebcamFrame()
{
    cv::Mat frame;
    cv::Mat result;
    capture >> frame;
    cutPerson(frame, result);
    texture = new Texture(result);
    return texture;
}

std::vector<unsigned char> Webcam::matToBytes(cv::Mat image) {
    std::vector<unsigned char> byteArray;
    cv::imencode(".png", image, byteArray);
    return byteArray;
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
