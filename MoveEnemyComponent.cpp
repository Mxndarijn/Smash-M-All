#include "MoveEnemyComponent.h"

#include <iostream>

#include "GameObject.h"
#define OFFSET 75

MoveEnemyComponent::MoveEnemyComponent(std::shared_ptr<GameObject>& camera) : camera(camera)
{

}

MoveEnemyComponent::~MoveEnemyComponent()
{
	
}

void MoveEnemyComponent::update(float elapsedTime)
{
	auto newPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * OFFSET)) * speed / elapsedTime, camera->position.y, -(camera->position.z + (cos(camera->rotation.y) * OFFSET)));

	gameObject->position = (1 - speed) * gameObject->position + speed * newPos;
	std::cout << gameObject->position.x << "," << gameObject->position.y << "," << gameObject->position.z << "\n";
}