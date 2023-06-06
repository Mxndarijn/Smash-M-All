#pragma once
#include <memory>
#include <GLFW/glfw3.h>

#include "Camera.h"

class GameObject;

class GUIManager
{
public:
	GUIManager(GLFWwindow* window, bool& drawGUI, bool& drawEndGUI);
	~GUIManager();

	void renderGUI(std::shared_ptr<GameObject> camera);
	void renderEndGUI(std::shared_ptr<GameObject> camera, int score);
	void update();
	void init();
	void shutdown();
	void createFrame();
	void setColors();

private:
	GLFWwindow* window;
	bool& drawGUI;
	bool& drawEndGUI;
};
