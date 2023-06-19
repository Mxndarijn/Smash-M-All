#include "BoundingBoxComponent.h"
#include <glm/gtx/rotate_vector.hpp>
#include <array>
#include <algorithm>
#include "RayCastComponent.h"
#include "tigl.h"
#include <iostream>

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
    return isLineInsideCube(corners[0], corners[1], near, far);
}

bool BoundingBoxComponent::isColliding(glm::vec3 position, glm::vec3 near, glm::vec3 far) {
	glm::vec3 minimal = glm::min(near, far);
	glm::vec3 maximal = glm::max(near, far);

	return glm::all(glm::greaterThanEqual(position, minimal)) && glm::all(glm::lessThanEqual(position, maximal));
}

std::array<glm::vec3, 2> BoundingBoxComponent::getCorners(glm::vec3 minCorner, glm::vec3 maxCorner)
{

	glm::vec3 minimal = glm::min(minCorner, maxCorner);
	glm::vec3 maximal = glm::max(minCorner, maxCorner);

	corners[0] = minimal;
	corners[1] = maximal;
	//corners[2] = glm::vec3(maximal.x, 1.f, minimal.z);
	//corners[3] = glm::vec3(maximal.x, 0.f, maximal.z);

	return corners;
}

bool BoundingBoxComponent::isLineInsideCube(const glm::vec3& cubeMin, const glm::vec3& cubeMax, const glm::vec3& lineStart, const glm::vec3& lineEnd) {
    // Check if any of the line's endpoints are inside the cube
    if (lineStart.x >= cubeMin.x && lineStart.x <= cubeMax.x &&
        lineStart.y >= cubeMin.y && lineStart.y <= cubeMax.y &&
        lineStart.z >= cubeMin.z && lineStart.z <= cubeMax.z) {
        return true;
    }
    if (lineEnd.x >= cubeMin.x && lineEnd.x <= cubeMax.x &&
        lineEnd.y >= cubeMin.y && lineEnd.y <= cubeMax.y &&
        lineEnd.z >= cubeMin.z && lineEnd.z <= cubeMax.z) {
        return true;
    }

    // Calculate line direction vector
    glm::vec3 direction = lineEnd - lineStart;

    // Calculate intersection parameter values with the cube's bounding box
    float tMin = (cubeMin.x - lineStart.x) / direction.x;
    float tMax = (cubeMax.x - lineStart.x) / direction.x;

    if (tMin > tMax) std::swap(tMin, tMax);

    float tyMin = (cubeMin.y - lineStart.y) / direction.y;
    float tyMax = (cubeMax.y - lineStart.y) / direction.y;

    if (tyMin > tyMax) std::swap(tyMin, tyMax);

    if ((tMin > tyMax) || (tyMin > tMax)) return false;

    if (tyMin > tMin) tMin = tyMin;
    if (tyMax < tMax) tMax = tyMax;

    float tzMin = (cubeMin.z - lineStart.z) / direction.z;
    float tzMax = (cubeMax.z - lineStart.z) / direction.z;

    if (tzMin > tzMax) std::swap(tzMin, tzMax);

    if ((tMin > tzMax) || (tzMin > tMax)) return false;

    return true;
}


void BoundingBoxComponent::update(float deltaTime)
{
	auto cornerTopLeft = gameObject->position + min;
	auto cornerBottomRight = gameObject->position + max;

	corners = getCorners(-cornerTopLeft, -cornerBottomRight);
}


void BoundingBoxComponent::draw()
{
    std::cout << "draw bound" << std::endl;
    glBegin(GL_LINES);

    auto minCorner = corners[0];
    auto maxCorner = corners[1];
    // Get the corners of the cube
    glm::vec3 corner1 = minCorner;
    glm::vec3 corner2 = glm::vec3(maxCorner.x, minCorner.y, minCorner.z);
    glm::vec3 corner3 = glm::vec3(minCorner.x, maxCorner.y, minCorner.z);
    glm::vec3 corner4 = glm::vec3(minCorner.x, minCorner.y, maxCorner.z);
    glm::vec3 corner5 = glm::vec3(maxCorner.x, maxCorner.y, minCorner.z);
    glm::vec3 corner6 = glm::vec3(minCorner.x, maxCorner.y, maxCorner.z);
    glm::vec3 corner7 = glm::vec3(maxCorner.x, minCorner.y, maxCorner.z);
    glm::vec3 corner8 = maxCorner;

    // Draw lines between corners
    glVertex3f(corner1.x, corner1.y, corner1.z);
    glVertex3f(corner2.x, corner2.y, corner2.z);

    glVertex3f(corner1.x, corner1.y, corner1.z);
    glVertex3f(corner3.x, corner3.y, corner3.z);

    glVertex3f(corner1.x, corner1.y, corner1.z);
    glVertex3f(corner4.x, corner4.y, corner4.z);

    glVertex3f(corner2.x, corner2.y, corner2.z);
    glVertex3f(corner5.x, corner5.y, corner5.z);

    glVertex3f(corner2.x, corner2.y, corner2.z);
    glVertex3f(corner7.x, corner7.y, corner7.z);

    glVertex3f(corner3.x, corner3.y, corner3.z);
    glVertex3f(corner5.x, corner5.y, corner5.z);

    glVertex3f(corner3.x, corner3.y, corner3.z);
    glVertex3f(corner6.x, corner6.y, corner6.z);

    glVertex3f(corner4.x, corner4.y, corner4.z);
    glVertex3f(corner6.x, corner6.y, corner6.z);

    glVertex3f(corner4.x, corner4.y, corner4.z);
    glVertex3f(corner7.x, corner7.y, corner7.z);

    glVertex3f(corner5.x, corner5.y, corner5.z);
    glVertex3f(corner8.x, corner8.y, corner8.z);

    glVertex3f(corner6.x, corner6.y, corner6.z);
    glVertex3f(corner8.x, corner8.y, corner8.z);

    glVertex3f(corner7.x, corner7.y, corner7.z);
    glVertex3f(corner8.x, corner8.y, corner8.z);

    glEnd();
}
