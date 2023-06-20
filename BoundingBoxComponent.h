#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "GameObject.h"
#include <memory>
#include <array>
class BoundingBoxComponent : public Component 
{
public:
	BoundingBoxComponent();
	BoundingBoxComponent(glm::vec3 min, glm::vec3 max);
	~BoundingBoxComponent();

	void update(float deltaTime) override;
	bool collide(glm::vec3 near, glm::vec3 far);

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 lengths;

	std::array<glm::vec3, 2> corners;
	void draw();

private:
	std::array<glm::vec3, 2> getCorners(glm::vec3 minCorner, glm::vec3 maxCorner);
	bool isColliding(glm::vec3 position, glm::vec3 near, glm::vec3 far);
	bool isLineInsideCube(const glm::vec3& cubeMin, const glm::vec3& cubeMax, const glm::vec3& lineStart, const glm::vec3& lineEnd);
};