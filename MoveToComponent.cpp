#include "MoveToComponent.h"
#include <iostream>
#include <cmath>

#define DELTA_TIME 1.0f / 60.0f
#define DURATION 20.0f

MoveToComponent::MoveToComponent(glm::vec3 target, float degrees, bool& drawEndGUI, bool *spawnEnemy):
    target(target), degrees(degrees), drawEndGUI(drawEndGUI), spawnEnemy(spawnEnemy)
{
}

MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
    auto minDistanceTraveled = 0.1f;
    speed = 0.5f * elapsedTime;

    auto newPos = (1 - speed) * gameObject->position + speed * target;
    auto distanceTraveled = glm::length(newPos - gameObject->position);
    if (distanceTraveled < minDistanceTraveled && glm::length(gameObject->position - target) >= minDistanceTraveled) {
        // calculate newpos so it moves 0.1f
        glm::vec3 direction = glm::normalize(target - gameObject->position);
        newPos = gameObject->position + direction * minDistanceTraveled;
    }

    gameObject->position = newPos;

    auto pos = gameObject->position;

    auto radians = glm::radians(degrees);

    gameObject->rotation.y = interpolateRotationExponential(glm::degrees(gameObject->rotation.y), degrees, DELTA_TIME, DURATION * elapsedTime);

    if (glm::length(pos - target) < 0.01f && radians - gameObject->rotation.y < 0.01f) {
        gameObject->rotation.y = radians;
        gameObject->position = target;
        gameObject->removeComponent<MoveToComponent>();
        *spawnEnemy = true;
    }
}

float MoveToComponent::interpolateRotationExponential(float currentAngle, float targetAngle, float deltaTime, float duration)
{
    // Bereken de interpolatiefactor (tussen 0 en 1)
    float t = deltaTime / duration;
    t = clamp(t, 0.0f, 1.0f);  // Beperk de waarde tussen 0 en 1

    // Pas exponentiŽle interpolatie toe
    float interpolatedAngle = currentAngle + (targetAngle - currentAngle) * (1.0f - std::powf(2.0f, -10.0f * t));

    return glm::radians(interpolatedAngle);
}