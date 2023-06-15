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
	/*auto newPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * OFFSET)) * speed / elapsedTime, camera->position.y, -(camera->position.z + (cos(camera->rotation.y) * OFFSET)));

	gameObject->position = (1 - speed) * gameObject->position + speed * newPos;
	std::cout << gameObject->position.x << "," << gameObject->position.y << "," << gameObject->position.z << "\n";*/

    auto minDistanceTraveled = 0.025f;
    speed = 0.0005f / elapsedTime;

    auto target = glm::vec3( -camera->position.x, camera->position.y, -camera->position.z);

    auto newPos = (1 - speed) * gameObject->position + speed * target;
    auto distanceTraveled = glm::length(newPos - gameObject->position);
    if (distanceTraveled < minDistanceTraveled && glm::length(gameObject->position - target) >= minDistanceTraveled) {
        // calculate newpos so it moves 0.1f
        glm::vec3 direction = glm::normalize(target - gameObject->position);
        newPos = gameObject->position + direction * minDistanceTraveled;
    }

    gameObject->position = newPos;
}