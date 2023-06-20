#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include "Camera.h"

class GameObject;

class GUIManager
{
public:
	GUIManager(bool& drawGUI, bool& drawEndGUI, irrklang::ISoundEngine* soundEngine, int& volume, bool *spawnEnemy, int &difficulty);
	~GUIManager();

	void renderGUI(const std::shared_ptr<GameObject>& camera);
	void renderEndGUI(GLFWwindow* window, const std::shared_ptr<GameObject>& camera, int& score, int& lives);
	void update();
	void init(GLFWwindow* window);
	void shutdown();
	void createFrame();
	void setColors();

private:
	bool& drawGUI;
	bool& drawEndGUI;
	int& volume;
	int &difficulty;
	bool* spawnEnemy;
	irrklang::ISoundEngine* soundEngine;

	void difficultyMenu();
};
