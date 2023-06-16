#pragma once
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>

struct GLFWwindow;

class CameraComponent : public Component {
public:
	CameraComponent(GLFWwindow* window);
	~CameraComponent();

	void update(float elapsedTime) override;
	glm::mat4 getMatrix();
	glm::vec3 getForward();
protected:
	GLFWwindow* window;

};