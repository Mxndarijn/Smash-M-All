#pragma once
#include <list>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include "DrawComponent.h"
#include <glm/glm.hpp>
#include <typeindex>

class Component;

class GameObject {
	std::list<std::type_index> removeComponentTypes;
	std::shared_ptr<DrawComponent> drawComponent;
	std::list<std::shared_ptr<Component>> components;

public:
	GameObject();
	~GameObject();

	glm::vec3 position;
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	bool isDead = false;
	std::list<std::shared_ptr<Component>> getComponents();

	void draw(const glm::mat4 & = glm::mat4(1.0f));
	void addComponent(std::shared_ptr<Component> component);

	void update(float deltaTime);

	template<class T>
	void removeComponent()
	{
		removeComponentTypes.push_back(std::type_index(typeid(T)));
	}

	template<class T>
	std::shared_ptr<T> getComponent()
	{
		
		for (auto c : components)
		{
			std::shared_ptr<T> t = dynamic_pointer_cast<T>(c);
			if (t)
			{
				return t;
			}
		}
		return nullptr;
	}


};