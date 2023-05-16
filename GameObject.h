#pragma once
#include <vector>

class Component;
class GameObject {
public:
	GameObject();
	~GameObject();

	virtual void update(double deltaTime) = 0;
	virtual void draw() = 0;
private:
	std::vector<Component> components;
};