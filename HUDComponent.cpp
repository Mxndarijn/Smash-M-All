#include "HUDComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/compatibility.hpp"
#include "Texture.h"
#include "GameObject.h"
#include <iostream>
#include "RayCastComponent.h"
#include "GameManager.h"
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

	if(path.substr(path.size() - 4)._Equal(".png")) {
		texture = new Texture(path);
	}
	else if(path._Equal("resources/textures/")){
		for (int i = 0; i <= lives; i++) {
			std::cout << "filename: " << path << "Hearts" << std::to_string(i) << "\n";
			heartTextures.push_back(new Texture(path + "Hearts" + std::to_string(i) + ".png"));
		}
	}

	// size for hud and hearts
	const float width = 1.f;
	const float height = 1.f;

	const float rightBottom = 5.f;

	heartVerts.push_back(tigl::Vertex::PT(glm::vec3(-width + rightBottom, -height + -rightBottom, 0.0f), glm::vec2(0, 0)));
	heartVerts.push_back(tigl::Vertex::PT(glm::vec3(width + rightBottom, -height + -rightBottom, 0.0f), glm::vec2(1, 0)));
	heartVerts.push_back(tigl::Vertex::PT(glm::vec3(width + rightBottom, height + -rightBottom, 0.0f), glm::vec2(1, 1)));
	heartVerts.push_back(tigl::Vertex::PT(glm::vec3(-width + rightBottom, height + -rightBottom, 0.0f), glm::vec2(0, 1)));

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
}

void HUDComponent::updateHUDPosition() {

	glm::mat4 ret(1.0f);
	glm::vec3 position = -gameObject->position;

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
	bindHUD(1.f);

	// making texture transparent
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	tigl::shader->enableTexture(true);

	texture->bind();
	tigl::drawVertices(GL_QUADS, verts);
	texture->unbind();

	bindHUD(6.f);
	if(lives > 0)
	{
		heartTextures[lives]->bind();
		tigl::drawVertices(GL_QUADS, heartVerts);
		heartTextures[lives]->unbind();
	} else
	{
		heartTextures[0]->bind();
		tigl::drawVertices(GL_QUADS, heartVerts);
		heartTextures[0]->unbind();
	}

	tigl::shader->enableTexture(false);

	unbindHUD();
}

void HUDComponent::bindHUD(const float& size)
{
	glDisable(GL_DEPTH_TEST);
	tigl::shader->setProjectionMatrix(glm::ortho(-size, size, -size, size, -size, size));
}

void HUDComponent::unbindHUD()
{
	auto camera = gameObject->getComponent<CameraComponent>();
	tigl::shader->setProjectionMatrix(projectionMatrix);
	if (camera)
		tigl::shader->setViewMatrix(camera->getMatrix());
	glEnable(GL_DEPTH_TEST);
}
