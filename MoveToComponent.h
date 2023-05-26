#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "GameObject.h"

class MoveToComponent :
	public Component
{
public:
	float speed = 0.05f;
	glm::vec3 target;

	MoveToComponent(glm::vec3 target);
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
};