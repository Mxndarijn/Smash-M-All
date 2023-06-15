#pragma once
#include "DrawComponent.h"
#include "glm/glm.hpp"
#include <list>
class RayCastComponent : public DrawComponent {
public:
	RayCastComponent(glm::vec2 webcamResolution, glm::mat4* projection, std::list<glm::vec2>* points);
	~RayCastComponent();

	void update(float deltaTime) override;
	void draw() override;
protected:
	glm::vec2 webcamResolution;
	glm::vec2 opticalCenter;
	std::list<glm::vec2>* points;
	std::list<glm::vec3> lines;

	glm::mat4* projectionMat;
protected:
	glm::vec3 pointToVec3(glm::vec2 point);
};