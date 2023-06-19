#include "RayCastComponent.h"
#include "tigl.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include <iostream>

#define focalLength 1000

glm::mat4 projectionMatrix;

RayCastComponent::RayCastComponent(glm::vec2 webcamResolution, glm::mat4* projection, std::list<glm::vec2>* points) : webcamResolution(webcamResolution),
opticalCenter(glm::vec2(webcamResolution.x / 2, webcamResolution.y / 2)), points(points), projectionMat(projection)
{

}

RayCastComponent::~RayCastComponent()
{

}

void RayCastComponent::update(float deltaTime)
{
	if (points->empty()) 
		return;
	
	for (auto& point : *points) {
		lines.push_back(pointToVec3(point));
	}
}

void RayCastComponent::draw()
{
	glBegin(GL_LINES);
	glEnable(GL_DEPTH_TEST);
	
	tigl::shader->enableColor(true);
	glColor4f(1.0f, 0.0f, 0.0f, 1.f);  // Red color

	for (auto& line : lines) {
		glm::vec3 near = std::get<0>(line);
		glm::vec3 far = std::get<1>(line);
		glVertex3f(near.x, near.y, near.z);
		glVertex3f(far.x, far.y, far.z);
	}

	tigl::shader->enableColor(false);
	glEnd();
}


std::tuple<glm::vec3, glm::vec3> RayCastComponent::pointToVec3(glm::vec2 point)
{
	auto cameraComponent = gameObject->getComponent<CameraComponent>();

	int viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort);
	//std::cout << "Point: " << point.x << " " << point.y << std::endl;

	auto testPoint = glm::vec2(5, 5) + point;
	glm::vec3 retNear = glm::unProject(glm::vec3(point, 0.0f), cameraComponent->getMatrix(), projectionMatrix, glm::vec4(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));
	glm::vec3 retFar = glm::unProject(glm::vec3(testPoint, 1.0f), cameraComponent->getMatrix(), projectionMatrix, glm::vec4(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));

	return std::make_tuple(retNear, retFar);
}