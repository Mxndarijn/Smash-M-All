#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "GameObject.h"
#include <memory>
class BoundingBoxComponent : public Component {
public:
	BoundingBoxComponent();
	BoundingBoxComponent(glm::vec3 min, glm::vec3 max);
	~BoundingBoxComponent();

	void update(float deltaTime) override;
	bool collide(std::shared_ptr<GameObject> obj);

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 lengths;
private:
	std::array<glm::vec3, 4> getCorners(glm::vec3 minCorner, glm::vec3 maxCorner);
	bool isColliding(glm::vec3 position, glm::vec3 minCorner, glm::vec3 maxCorner);
};