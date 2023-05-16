#pragma once
#include "Component.h"

class MoveToComponent : public Component {
public:
	MoveToComponent(GameObject* gameObject);
	~MoveToComponent();

	void update(float elapsedTime) override;
private:

};