#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "GameObject.h"
#include <memory>
#include <array>
class BoundingBoxComponent : public DrawComponent 
{
public:
	BoundingBoxComponent();
	BoundingBoxComponent(glm::vec3 min, glm::vec3 max);
	~BoundingBoxComponent();

	void update(float deltaTime) override;
	void draw() override;
	bool collide(glm::vec3 near, glm::vec3 far);

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 lengths;

	std::array<glm::vec3, 4> corners;

private:
	std::array<glm::vec3, 4> getCorners(glm::vec3 minCorner, glm::vec3 maxCorner);
	bool isColliding(glm::vec3 position, glm::vec3 near, glm::vec3 far);
};