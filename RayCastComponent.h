#pragma once
#include "DrawComponent.h"
#include "glm/glm.hpp"
#include <list>
class RayCastComponent : public DrawComponent {
public:
	RayCastComponent(glm::vec2 webcamResolution, std::list<glm::vec2>* points);
	~RayCastComponent();

	void update(float deltaTime) override;
	void draw() override;
protected:
	glm::vec2 webcamResolution;
	glm::vec2 opticalCenter;
	std::list<glm::vec2>* points;
	std::list<glm::vec3> lines;
protected:
	glm::vec3 pointToVec3(glm::vec2 point);
};