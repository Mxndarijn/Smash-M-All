#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
	component->setGameObject(this);
	components.push_back(component);
	if (drawComponent == nullptr)
		drawComponent = dynamic_pointer_cast<DrawComponent>(component)
}

void GameObject::update(double deltaTime)
{
	for (auto component : components) {
		component->update((float)deltaTime);
	}
}
