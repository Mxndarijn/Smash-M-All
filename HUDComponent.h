#pragma once
#include "DrawComponent.h"
#include "tigl.h"
#include <string>
#include "Webcam.h"
#include "GLFW/glfw3.h"

class Texture;

class HUDComponent : public DrawComponent {
	std::vector<tigl::Vertex> verts;
public:
	HUDComponent(GLFWwindow* window, Webcam* webcam = nullptr, std::string path = "resources/textures/test.png");
	~HUDComponent();

	void update(float deltaTime) override;
	void draw() override;

	inline void updateTexture(Texture* texture) { this->texture = texture; }
private:
	Texture* texture = nullptr;
	Webcam* webcam = nullptr;
	glm::mat4 mat;	

	std::vector<Texture*> heartTextures;
	std::vector<tigl::Vertex> heartVerts;
private:
	void bindHUD(const float& size);
	void unbindHUD();
	void updateHUDPosition();
};