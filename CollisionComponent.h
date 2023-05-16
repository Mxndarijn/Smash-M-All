#pragma once
#include "Component.h"

class CollisionComponent : public Component {
public:
	CollisionComponent();
	~CollisionComponent();

	void update(float elapsedTime) override;
private:
};