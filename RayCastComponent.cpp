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
	/*if (points->empty()) 
		return;
	
	for (auto& point : *points) {
		lines.push_back(pointToVec3(point));
	}*/
}

void RayCastComponent::draw()
{
	auto cameraComponent = gameObject->getComponent<CameraComponent>();

	int viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort);

	int screenWidth = viewPort[2]; // Width of the viewport
	int screenHeight = viewPort[3]; // Height of the viewport


	// Calculate the center point of the screen
	glm::vec2 screenCenter(screenWidth / 4.0f, screenHeight / 4.0f);
	glm::vec2 screenCenter1(screenWidth / 4.0f + 5, screenHeight / 4.0f + 5);



	glm::vec3 retNear = glm::unProject(glm::vec3(screenCenter, 0.f), cameraComponent->getMatrix(), projectionMatrix, glm::vec4(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));
	glm::vec3 retFar = glm::unProject(glm::vec3(screenCenter1, 1.f), cameraComponent->getMatrix(), projectionMatrix, glm::vec4(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));

	glPointSize(20.0f); // Stel de grootte van het punt in

	glBegin(GL_LINES);
	glEnable(GL_DEPTH_TEST);

	glVertex3f(retNear.x, retNear.y, retNear.z); // Teken het punt met de opgegeven coördinaten
	glVertex3f(retFar.x, retFar.y, retFar.z); // Teken het punt met de opgegeven coördinaten
	//glVertex3f(-far.x, far.y, far.z); // Teken het punt met de opgegeven coördinaten

	glEnd(); // Eindig met het tekenen van punten



}


std::tuple<glm::vec3, glm::vec3> RayCastComponent::pointToVec3(glm::vec2 point)
{
	auto cameraComponent = gameObject->getComponent<CameraComponent>();

	int viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort);
	glm::vec3 retNear = glm::unProject(glm::vec3(point, 0.0f), cameraComponent->getMatrix(), *projectionMat, glm::vec4(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));
	glm::vec3 retFar = glm::unProject(glm::vec3(point, 1.0f), cameraComponent->getMatrix(), *projectionMat, glm::vec4(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));

	return std::make_tuple(retNear, retFar);
}