#include "HUDComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/compatibility.hpp"
#include "Texture.h"
#include "GameObject.h"
#include <iostream>
#include "RayCastComponent.h"

const bool color = false;

HUDComponent::HUDComponent(GLFWwindow* window, Webcam* webcam, std::string path)
{
	if (path._Equal("webcam") || webcam != nullptr) {
		std::cout << "webcam initialised\n";
		if (webcam)
			this->webcam = webcam;
		else
			webcam = new Webcam(window);
	}
	else {
		texture = new Texture(path);
	}

	// size for hud
	const float width = 1.f;
	const float height = 1.f;

	if (color) {
		verts.push_back(tigl::Vertex::PC(glm::vec3(-width, -height, 0.0f), glm::vec4(0, 0, 0, 1)));
		verts.push_back(tigl::Vertex::PC(glm::vec3(width, -height, 0.0f), glm::vec4(0, 0, 0, 1)));
		verts.push_back(tigl::Vertex::PC(glm::vec3(width, height, 0.0f), glm::vec4(0, 0, 0, 1)));
		verts.push_back(tigl::Vertex::PC(glm::vec3(-width, height, 0.0f), glm::vec4(0, 0, 0, 1)));
	}
	else {
		// vertices for quad of hud
		verts.push_back(tigl::Vertex::PT(glm::vec3(-width, -height, 0.0f), glm::vec2(0, 0)));
		verts.push_back(tigl::Vertex::PT(glm::vec3(width, -height, 0.0f), glm::vec2(1, 0)));
		verts.push_back(tigl::Vertex::PT(glm::vec3(width, height, 0.0f), glm::vec2(1, 1)));
		verts.push_back(tigl::Vertex::PT(glm::vec3(-width, height, 0.0f), glm::vec2(0, 1)));
	}
}


HUDComponent::~HUDComponent()
{
}

void HUDComponent::update(float deltaTime)
{
	delete texture;
	if (webcam)
		texture = webcam->getWebcamFrame();
	//updateHUDPosition();
}

void HUDComponent::updateHUDPosition() {

	glm::mat4 ret(1.0f);
	glm::vec3 position = -gameObject->position;
	//glm::vec3 position = glm::vec3(50, 0, 50);
	//std::cout << "Position: " << gameObject->position.x << " , " << gameObject->position.y << " , " << gameObject->position.z << std::endl;
	//std::cout << "Position matrix: " << position.x << " , " << position.y << " , " << position.z << std::endl;

	position.y *= -1;
	// position of player
	ret = glm::translate(ret, position);

	// rotate hud
	ret = glm::rotate(ret, -gameObject->rotation.y, glm::vec3(0, 1, 0));

	// rotate hud around x-axis
	ret = glm::rotate(ret, -gameObject->rotation.x, glm::vec3(1, 0, 0));

	// distance from camera
	float zDistance = -.4f;

	// move HUD slightly in front of player
	position = glm::vec3(0.0f, 0.0f, zDistance);

	// place HUD
	ret = glm::translate(ret, position);

	this->mat = ret;
}

void HUDComponent::draw()
{
	updateHUDPosition();
	tigl::shader->setModelMatrix(this->mat);
	bindHUD();

	// making texture transparent
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	texture->bind();
	tigl::shader->enableTexture(true);
	tigl::drawVertices(GL_QUADS, verts);
	tigl::shader->enableTexture(false);
	texture->unbind();

	unbindHUD();
}

void HUDComponent::bindHUD()
{
	glDisable(GL_DEPTH_TEST);
	tigl::shader->setProjectionMatrix(glm::ortho(-1.f, 1.0f, -1.f, 1.0f, -1.0f, 1.0f));
}

void HUDComponent::unbindHUD()
{
	auto camera = gameObject->getComponent<CameraComponent>();
	tigl::shader->setProjectionMatrix(projectionMatrix);
	if (camera)
		tigl::shader->setViewMatrix(camera->getMatrix());
	glEnable(GL_DEPTH_TEST);
}
