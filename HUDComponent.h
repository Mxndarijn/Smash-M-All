#pragma once
#include "DrawComponent.h"
#include "tigl.h"
#include <string>
#include "Webcam.h"

class Texture;

class HUDComponent : public DrawComponent {
	std::vector<tigl::Vertex> verts;
public:
	HUDComponent(std::string path = "resource/textures/test.png");
	~HUDComponent();

	void update(float deltaTime) override;
	void draw() override;

	inline void updateTexture(Texture* texture) { this->texture = texture; }
private:
	Texture* texture;
	glm::mat4 mat;

	Webcam* webcam;
private:
	void bindHUD();
	void unbindHUD();
	void updateHUDPosition();
};