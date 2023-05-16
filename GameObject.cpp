#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::addComponent(Component &component) 
{
	component.setGameObject(this);
}

void GameObject::update(double deltaTime)
{
	for (auto component : components) {
		component->update((float)deltaTime);
	}
}
