#pragma once
#include "Component.h"

class PlayerComponent : public Component
{

	float speed = 500;
public:
	PlayerComponent();
	~PlayerComponent();
	void move(float angle, float fac, float elapsedTime);
	virtual void update(float elapsedTime) override;
};