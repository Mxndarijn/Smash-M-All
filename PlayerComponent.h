#pragma once
#include "Component.h"

class PlayerComponent : public Component {
public:
	PlayerComponent(GameObject* gameObject);
	~PlayerComponent();

	void update(float elapsedTime) override;
private:
	
};