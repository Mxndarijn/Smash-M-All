#include "RotateComponent.h"
#include "GameObject.h"

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
	gameObject->rotation.y -= (float)(lastX - x) / 100.f;

	lastX = x;
	lastY = y;
}
