#pragma once

class GameObject;

class Component {
public:
	Component();
	~Component();

	virtual void update(float elapsedTime) {};

	inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
protected:
	GameObject* gameObject;
};