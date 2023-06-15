#pragma once
#include "tigl.h"
#include "GLFW/glfw3.h"

#include <opencv2/imgcodecs.hpp>
class RayCast {
public:
	RayCast(cv::Point webcamResolution);
	~RayCast();

	glm::vec3 pointToVec3(cv::Point point);
protected:
	cv::Point webcamResolution;
	cv::Point opticalCenter;
	const float focalLength = 1000.f;
};