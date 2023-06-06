#include "HUDComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/compatibility.hpp"
#include "Texture.h"
#include "GameObject.h"

HUDComponent::HUDComponent(std::string path)
{
	if (path._Equal("webcam")) {
		webcam = new Webcam();
	}
	else {
		texture = new Texture(path);
	}
}

HUDComponent::~HUDComponent()
{
}

void HUDComponent::update(float deltaTime)
{
	//texture = &webcam->getWebcamFrame();
	updateHUDPosition();
}

void HUDComponent::updateHUDPosition() {
	glm::mat4 ret(1.0f);
	glm::vec3 position = -gameObject->position;

	// position of player
	ret = glm::translate(ret, position);

	// rotate hud
	ret = glm::rotate(ret, -gameObject->rotation.y, glm::vec3(0, 1, 0));

	// rotate hud around x-axis
	ret = glm::rotate(ret, -gameObject->rotation.x, glm::vec3(1, 0, 0));

	// distance from camera
	float zDistance = -.2f;

	// move HUD slightly in front of player
	position = glm::vec3(0.0f, 0.0f, zDistance);

	// place HUD
	ret = glm::translate(ret, position);

	this->mat = ret;
}

void HUDComponent::draw()
{
	tigl::shader->setModelMatrix(this->mat);
	bindHUD();

	// making texture transparent
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	texture->bind();
	tigl::shader->enableTexture(true);
	tigl::drawVertices(GL_QUADS, verts);
	tigl::shader->enableTexture(false);
	texture->unbind();

	glEnable(GL_DEPTH_TEST);
	unbindHUD();
}

void HUDComponent::bindHUD()
{
	// Change to 2D projection
	glMatrixMode(GL_PROJECTION);

	// Save current projection
	glPushMatrix();

	// Reset matrix
	glLoadIdentity();

	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void HUDComponent::unbindHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
