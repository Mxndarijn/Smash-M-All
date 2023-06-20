#pragma once
#include <list>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "ObjModel.h"
#include "Timerf.h"

class GameManager
{
public:
	int score = 0;
	int lives = 3;
	bool enableEnemySpawn = false;

	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<ObjModel*>& models, std::shared_ptr<GameObject>& camera, int &difficulty);
	~GameManager();

	void spawnEnemy();
	void update(bool& endscreen);
	void init();
	void despawnEnemies();

private:
	std::shared_ptr<GameObject>& camera;
	std::list<std::shared_ptr<GameObject>>& objects;
	std::vector<ObjModel*>& models;
	const float spawnEnemyOffset;
	Timerf* spawnTimer;
	int getRandomEnemy();
	glm::vec3 randomizeEnemyPos(std::shared_ptr<GameObject>& camera);
	int& difficulty;
};

