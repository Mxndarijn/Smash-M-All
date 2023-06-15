#include "RayCast.h"
#include <iostream>
RayCast::RayCast(cv::Point webcamResolution) : webcamResolution(webcamResolution),
opticalCenter(cv::Point(webcamResolution.x / 2, webcamResolution.y / 2))
{
}

RayCast::~RayCast()
{
}

glm::vec3 RayCast::pointToVec3(cv::Point point)
{
	glm::vec3 position;
	// Vertaal 2D-beeldcoördinaten naar genormaliseerde apparaatcoördinaten (-1.0 tot 1.0)
	float normalized_x = 2.0 * (point.x - opticalCenter.x) / webcamResolution.x;
	float normalized_y = 2.0 * (point.y - opticalCenter.y) / webcamResolution.y;

	// Projectie van genormaliseerde apparaatcoördinaten naar 3D-coördinaten
	cv::Mat projection_matrix = cv::Mat::eye(4, 4, CV_32F);
	projection_matrix.at<float>(0, 0) = focalLength / (1 * webcamResolution.x);
	projection_matrix.at<float>(1, 1) = focalLength / (1 * webcamResolution.y);

	cv::Mat homogeneous_coords = (cv::Mat_<float>(4, 1) << normalized_x, normalized_y, 0.0, 1.0);
	cv::Mat transformed_coords = projection_matrix * homogeneous_coords;

	position.x = -transformed_coords.at<float>(0);
	position.y = -transformed_coords.at<float>(1);
	position.z = -0;

	//std::cout << "position: " << position.x << ", " << position.y << ", " << position.z << "\n";
	return position;
}
