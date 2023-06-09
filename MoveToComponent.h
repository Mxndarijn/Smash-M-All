#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "GameObject.h"


class MoveToComponent :
	public Component
{
public:
	float speed = 0.01f;
	float degrees;
	bool& drawEndGUI;
	bool* spawnEnemy;
	glm::vec3 target;

	MoveToComponent(glm::vec3 target, float degrees, bool& drawEndGUI, bool* spawnEnemy);
	~MoveToComponent();

	virtual void update(float elapsedTime) override;

private:
	float interpolateRotationExponential(float currentAngle, float targetAngle, float deltaTime, float duration);


	template <typename T>
	constexpr const T & clamp(const T & value, const T & min, const T & max)
	{
		return value < min ? min : (value > max ? max : value);
	}
};