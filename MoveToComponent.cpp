#include "MoveToComponent.h"
#include <iostream>

MoveToComponent::MoveToComponent(glm::vec3 target) :
	target(target)
{
}

MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	gameObject->position = (1 - speed) * gameObject->position + speed * target;

	float angle = atan2(gameObject->position.z - target.z, gameObject->position.x - target.x);

	gameObject->rotation.y = 0.05f * angle + 0.95f * gameObject->rotation.y;

	auto pos = gameObject->position;
	float distance = glm::length(pos - target);
	float distanceThreshold = 0.1f; // Adjust this threshold as needed

	if (distance < distanceThreshold) {
		gameObject->position = target;
		std::cout << "Removing MoveTo" << std::endl;
		gameObject->removeComponent<MoveToComponent>();
	}
}
