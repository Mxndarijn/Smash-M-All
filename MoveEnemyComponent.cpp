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
    auto minDistanceTraveled = 0.025f;
    speed = 0.5f * elapsedTime;

    auto target = glm::vec3( -camera->position.x, camera->position.y - 2, -camera->position.z);
    glm::vec3 direction = glm::normalize(target - gameObject->position);

    auto newPos = (1 - speed) * gameObject->position + speed * target;
    auto distanceTraveled = glm::length(newPos - gameObject->position);
    if (distanceTraveled < minDistanceTraveled && glm::length(gameObject->position - target) >= minDistanceTraveled) {
        // calculate newpos so it moves 0.1f
        newPos = gameObject->position + direction * minDistanceTraveled;
    }

    gameObject->position = newPos;

}