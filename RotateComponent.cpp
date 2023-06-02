#include "RotateComponent.h"
#include "GameObject.h"
#include <iostream>

RotateComponent::RotateComponent()
{
}

RotateComponent::~RotateComponent()
{
}

void RotateComponent::update(float elapsedTime)
{
	static double x = 0;
	static double y = 0;

	static double lastX = x;
	static double lastY = y;

	x += 1;

	float tempX = gameObject->rotation.x - (float)(lastY - y) / 100.f;

	if (tempX < 1.4f && tempX > -1.0f)
		gameObject->rotation.x = tempX;
	gameObject->rotation.y -= (float)(lastX - x) / 5.f * elapsedTime;

	lastX = x;
	lastY = y;

	std::cout << glm::degrees(gameObject->rotation.y) << std::endl;

	if (glm::degrees(gameObject->rotation.y) >= 360)
	{	
		gameObject->rotation.y = 0;
	}
}
