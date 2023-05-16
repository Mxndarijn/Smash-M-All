#pragma once
#include "Component.h"

class CollisionComponent : public Component {
public:
	CollisionComponent(GameObject* gameObject);
	~CollisionComponent();

	void update(float elapsedTime) override;
private:
};