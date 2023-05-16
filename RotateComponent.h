#pragma once
#include "Component.h"

class RotateComponent : public Component {
public: 
	RotateComponent(GameObject* gameObject);
	~RotateComponent();

	void update(float elapsedTime) override;
private:
};