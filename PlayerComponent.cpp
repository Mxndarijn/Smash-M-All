#include "PlayerComponent.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>

extern GLFWwindow* window;

PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::move(float angle, float fac, float elapsedTime)
{
	gameObject->position.x += (float)cos(gameObject->rotation.y + glm::radians(angle)) * fac * speed * elapsedTime;
	gameObject->position.z += (float)sin(gameObject->rotation.y + glm::radians(angle)) * fac * speed * elapsedTime;
}

void PlayerComponent::update(float elapsedTime)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, 0.05f, elapsedTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, 0.05f, elapsedTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, 0.05f, elapsedTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, 0.05f, elapsedTime);

}