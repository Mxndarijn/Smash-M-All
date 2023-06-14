#pragma once
#include <memory>
#include <glm/vec3.hpp>

#include "Component.h"

class MoveEnemyComponent : public Component
{
public:
	float speed = 0.075f;
	std::shared_ptr<GameObject>& camera;
	MoveEnemyComponent(std::shared_ptr<GameObject>& camera);
	~MoveEnemyComponent();

	virtual void update(float elapsedTime) override;
};
