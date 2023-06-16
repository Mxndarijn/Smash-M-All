#include "CameraComponent.h"
#include <GLFW/glfw3.h>
#include "GameObject.h"
#include "PlayerComponent.h"
#include <iostream>

CameraComponent::~CameraComponent() {

}

CameraComponent::CameraComponent(GLFWwindow* window) : window(window) {
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

}

void CameraComponent::update(float elapsedTime)
{
	if (gameObject->getComponent<PlayerComponent>()) {
		static bool init = false;
		if (!init) {
			init = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		static double lastX = x;
		static double lastY = y;


		float tempX = gameObject->rotation.x - (float)(lastY - y) / 100.f;

		auto minWatchHeight = -1.f;
		auto maxWatchHeight = 1.4f;

		if (tempX < maxWatchHeight && tempX > minWatchHeight)
			gameObject->rotation.x = tempX;
		gameObject->rotation.y -= (float)(lastX - x) / 100.f;

		lastX = x;
		lastY = y;
	}
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

glm::vec3 CameraComponent::getForward() {
	// De kijkrichting van de camera is de negatieve richting van de 'forward'-vector van de viewmatrix.
	// Je kunt deze waarde aanpassen op basis van hoe je de kijkrichting in je camera-implementatie hebt opgeslagen.
	// Hier is een voorbeeld dat ervan uitgaat dat je een 'viewMatrix' hebt als een 4x4 glm::mat4.

	// Haal de 'forward'-vector op uit de viewmatrix.

	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, gameObject->rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, gameObject->rotation.y, glm::vec3(0, 1, 0));
	ret = glm::rotate(ret, gameObject->rotation.z, glm::vec3(0, 0, 1));

	auto viewMatrix = ret;
	glm::vec3 forward(-viewMatrix[2][0], -viewMatrix[2][1], -viewMatrix[2][2]);

	// Zorg ervoor dat de vector genormaliseerd is voordat je deze retourneert.
	return glm::normalize(forward);
}