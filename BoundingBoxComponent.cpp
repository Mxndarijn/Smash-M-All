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

bool BoundingBoxComponent::collide(std::shared_ptr<GameObject> obj)
{
	auto boundingBoxComponent = obj->getComponent<BoundingBoxComponent>();
	if (!boundingBoxComponent)
		return false;

	auto cubeCorner1 = gameObject->position + min;
	auto cubeCorner2 = gameObject->position + max;

	auto corners = getCorners(-cubeCorner1, -cubeCorner2);

	auto checkingCubeCorner1 = obj->position + boundingBoxComponent->min;
	auto checkingCubeCorner2 = obj->position + boundingBoxComponent->max;

	for (int i = 0; i < corners.size(); i++) {
		if (isColliding(corners[i], checkingCubeCorner1, checkingCubeCorner2)) {
			return true;
		}
	}
	return false;
}

bool BoundingBoxComponent::isColliding(glm::vec3 position, glm::vec3 minCorner, glm::vec3 maxCorner) {
	glm::vec3 minimal = glm::min(minCorner, maxCorner);
	glm::vec3 maximal = glm::max(minCorner, maxCorner);

	return glm::all(glm::greaterThanEqual(position, minimal)) && glm::all(glm::lessThanEqual(position, maximal));
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
