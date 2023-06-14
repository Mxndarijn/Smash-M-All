#pragma once
#include <string>
#include <vector>
#include "tigl.h"
#include "GLFW/glfw3.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

class VideoCapture;
class Texture;

class Webcam {
public:
	Webcam(GLFWwindow* window);
	~Webcam();

	Texture* getWebcamFrame();
protected:
	Texture* texture;
	std::vector<tigl::Vertex> verts;
	std::list<cv::Point> detectionPoints;
	std::list<cv::Point> resizedDetectionPoints;

	cv::VideoCapture capture;
	cv::Mat previousFrame;
	int motionThreshold = 40;

	GLFWwindow* window;

protected:
	inline std::list<cv::Point> getDetectionPoints() { return resizedDetectionPoints; }
	void cutPerson(cv::Mat& frame, cv::Mat& result);
	void findMovement(cv::Mat& frame);
	std::vector<unsigned char> matToBytes(cv::Mat image);
	cv::Mat makeTransparent(cv::Mat& image);
	

};