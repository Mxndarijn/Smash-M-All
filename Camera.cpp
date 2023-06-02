#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position);
	return ret;
}

void Camera::move(float angle, float fac) {
	position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}

void Camera::moveCam(GLFWwindow* window, float speed) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		move(90, speed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		move(0, speed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		move(180, speed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		move(-90, speed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position.y -= speed * 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position.y += speed * 2.0f;
	}
}

void Camera::update(GLFWwindow* window) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	float tempX = rotation.x - (float)(lastY - y) / 100.f;

	if (tempX < 1.5f && tempX > -1.0f)
		rotation.x = tempX;

	rotation.y -= (float)(lastX - x) / 100.0f;

	lastX = x;
	lastY = y;

	moveCam(window, 2.0f);
}