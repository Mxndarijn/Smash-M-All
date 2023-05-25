#pragma once
#include "Component.h"

class MoveToComponent : public Component {
public:
	MoveToComponent();
	~MoveToComponent();

	void update(float elapsedTime) override;
private:

};