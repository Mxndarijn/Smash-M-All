#pragma once
#include <string>
#include <vector>
#include "tigl.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

class VideoCapture;
class Texture;

class Webcam {
public:
	Webcam();
	~Webcam();

	Texture getWebcamFrame();
protected:
	Texture* texture;
	std::vector<tigl::Vertex> verts;
	cv::VideoCapture capture;

protected:
	void cutPerson(cv::Mat& frame, cv::Mat& result);
	std::vector<unsigned char> matToBytes(cv::Mat image);
};