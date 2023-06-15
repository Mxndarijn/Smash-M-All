#include "BoundingBoxComponent.h"
#include <glm/gtx/rotate_vector.hpp>
#include <array>
#include <algorithm>

BoundingBoxComponent::BoundingBoxComponent() {

}

BoundingBoxComponent::BoundingBoxComponent(glm::vec3 min, glm::vec3 max) : min(min), max(max), lengths(min - max)
{
}

BoundingBoxComponent::~BoundingBoxComponent()
{
}

bool BoundingBoxComponent::collide(glm::vec3 collisionPoint)
{
	auto cubeCorner1 = gameObject->position + min;
	auto cubeCorner2 = gameObject->position + max;

	auto corners = getCorners(-cubeCorner1, -cubeCorner2);

	for (int i = 0; i < corners.size(); i++) {
		if (isColliding(corners[i], collisionPoint)) {
			return true;
		}
	}
	return false;
}

bool BoundingBoxComponent::isColliding(glm::vec3 position, glm::vec3 collisionPoint) {
	glm::vec3 maxCorner = position + lengths;
	return glm::all(glm::greaterThanEqual(collisionPoint, position)) && glm::all(glm::lessThanEqual(collisionPoint, maxCorner));
}

std::array<glm::vec3, 4> BoundingBoxComponent::getCorners(glm::vec3 minCorner, glm::vec3 maxCorner)
{
	std::array<glm::vec3, 4> corners;

	glm::vec3 minimal = glm::min(minCorner, maxCorner);
	glm::vec3 maximal = glm::max(minCorner, maxCorner);

	corners[0] = minimal;
	corners[1] = glm::vec3(minimal.x, 1.f, maximal.z);
	corners[2] = glm::vec3(maximal.x, 1.f, minimal.z);
	corners[3] = glm::vec3(maximal.x, 0.f, maximal.z);

	return corners;
}

void BoundingBoxComponent::update(float deltaTime)
{
}
