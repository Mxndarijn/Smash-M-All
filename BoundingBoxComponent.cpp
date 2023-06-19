#include "BoundingBoxComponent.h"
#include <glm/gtx/rotate_vector.hpp>
#include <array>
#include <algorithm>
#include "RayCastComponent.h"
#include "tigl.h"

BoundingBoxComponent::BoundingBoxComponent()
{

}

BoundingBoxComponent::BoundingBoxComponent(glm::vec3 min, glm::vec3 max) : min(min), max(max), lengths(min - max)
{

}

BoundingBoxComponent::~BoundingBoxComponent()
{

}

bool BoundingBoxComponent::collide(glm::vec3 near, glm::vec3 far)
{
	for (int i = 0; i < corners.size(); i++) {
		if (isColliding(corners[i], near, far)) {
			return true;
		}
	}
	return false;
}

bool BoundingBoxComponent::isColliding(glm::vec3 position, glm::vec3 near, glm::vec3 far) {
	glm::vec3 minimal = glm::min(near, far);
	glm::vec3 maximal = glm::max(near, far);

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
	auto cornerTopLeft = gameObject->position + min;
	auto cornerBottomRight = gameObject->position + max;

	corners = getCorners(-cornerTopLeft, -cornerBottomRight);
}

void BoundingBoxComponent::draw()
{
	tigl::begin(GL_QUADS);
	for (int i = 0; i < 4; i++)
		tigl::addVertex(tigl::Vertex::P(corners[i]));
	tigl::end();
}