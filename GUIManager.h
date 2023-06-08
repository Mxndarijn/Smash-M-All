#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include "Camera.h"

class GameObject;

class GUIManager
{
public:
	GUIManager(bool& drawGUI, bool& drawEndGUI, irrklang::ISoundEngine* soundEngine, int& volume);
	~GUIManager();

	void renderGUI(const std::shared_ptr<GameObject>& camera);
	void renderEndGUI(const std::shared_ptr<GameObject>& camera, int score);
	void update();
	void init(GLFWwindow* window);
	void shutdown();
	void createFrame();
	void setColors();

private:
	bool& drawGUI;
	bool& drawEndGUI;
	int& volume;
	irrklang::ISoundEngine* soundEngine;
};