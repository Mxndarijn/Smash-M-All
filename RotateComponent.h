#pragma once
#include "Component.h"

class RotateComponent : public Component {
public: 
	RotateComponent();
	~RotateComponent();

	void update(float elapsedTime) override;
private:
};