#pragma once
#include "Component.h"

class PlayerComponent : public Component {
public:
	PlayerComponent();
	~PlayerComponent();

	void update(float elapsedTime) override;
private:
	
};