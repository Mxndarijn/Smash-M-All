#pragma once

class GameObject;

class Component {
public:
	Component(GameObject *gameObject);
	~Component();

	virtual void update(float elapsedTime) = 0;
protected:
	GameObject* gameObject;
};