#pragma once
#include <list>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include "DrawComponent.h"
#include <glm/glm.hpp>

class Component;

class GameObject {
	std::shared_ptr<DrawComponent> drawComponent;
	std::list<std::shared_ptr<Component>> components;

public:
	GameObject();
	~GameObject();

	glm::vec3 position;
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	void addComponent(std::shared_ptr<Component> component);

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

	template<class T>
	std::shared_ptr<T> getComponent()
	{
		std::shared_ptr<T> t = dynamic_pointer_cast<T>(c);
		for (auto t : components)
		{
			if (t)
			{
				return t;
			}
		}
		return nullptr;
	}

	void draw(const glm::mat4& parentMatrix);
	std::list<std::shared_ptr<Component>> getComponents();
};