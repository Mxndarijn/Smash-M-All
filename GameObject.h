#pragma once
#include <list>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

class Component;

class GameObject {
public:
	GameObject();
	~GameObject();

	void addComponent(Component &component);

	void update(double deltaTime);
	virtual void draw() = 0;


	template<class T>
	void removeComponent()
	{
		components.remove_if([](Component* c)
			{
				T* t = dynamic_cast<T*>(c);
				return t != nullptr;
			});
	}


protected:
	std::list<std::shared_ptr<Component>> components;

	glm::vec3 transform;
	glm::vec3 rotate;
	glm::vec3 translate;
};