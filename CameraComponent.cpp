#include "CameraComponent.h"
#include <GLFW/glfw3.h>
#include "GameObject.h"
#include <iostream>

CameraComponent::~CameraComponent() {

}

CameraComponent::CameraComponent(GLFWwindow* window) : window(window) {

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

}

void CameraComponent::update(float elapsedTime)
{
	
}

glm::mat4 CameraComponent::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, gameObject->rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, gameObject->rotation.y, glm::vec3(0, 1, 0));
	ret = glm::rotate(ret, gameObject->rotation.z, glm::vec3(0, 0, 1));
	gameObject->position.y = gameObject->position.y * -1;
	ret = glm::translate(ret, gameObject->position);
	gameObject->position.y = gameObject->position.y * -1;
	return ret;
}