#pragma once
#include "DrawComponent.h"
#include "glm/glm.hpp"
#include <list>
#include <tuple>
#include "GameObject.h"
#include "CameraComponent.h"
class RayCastComponent : public Component {
public:
	RayCastComponent(glm::vec2 webcamResolution, glm::mat4* projection, std::list<glm::vec2>* points);
	~RayCastComponent();

	void update(float deltaTime) override;
	void draw();

	std::list<std::tuple<glm::vec3, glm::vec3>> lines;

protected:
	glm::vec2 webcamResolution;
	glm::vec2 opticalCenter;
	std::list<glm::vec2>* points;

	glm::mat4* projectionMat;
protected:
	std::tuple<glm::vec3, glm::vec3>pointToVec3(glm::vec2 point);
};

extern glm::mat4 projectionMatrix;