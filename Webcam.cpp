#include "Webcam.h"
#include "Texture.h"

Webcam::Webcam()
{
    // size for hud
    const float width = 0.295f;
    const float height = 0.168f;

    // vertices for quad of hud
    verts.push_back(tigl::Vertex::PT(glm::vec3(-width, -height, 0.0f), glm::vec2(0, 0)));
    verts.push_back(tigl::Vertex::PT(glm::vec3(width, -height, 0.0f), glm::vec2(1, 0)));
    verts.push_back(tigl::Vertex::PT(glm::vec3(width, height, 0.0f), glm::vec2(1, 1)));
    verts.push_back(tigl::Vertex::PT(glm::vec3(-width, height, 0.0f), glm::vec2(0, 1)));

    capture = cv::VideoCapture(0);
}

Webcam::~Webcam()
{
}

Texture Webcam::getWebcamFrame()
{
    cv::Mat frame;
    cv::Mat result;
    capture >> frame;
    cutPerson(frame, result);
    return Texture(result);
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
}