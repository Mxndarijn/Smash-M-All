#pragma once
#include <list>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "ObjModel.h"

class GameManager
{
public:
	int score = 0;
	int lives = 3;

	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<ObjModel*>& models);
	~GameManager();

	void spawnEnemy(std::shared_ptr<GameObject>& camera);
	void update();
	void init();
	void despawnEnemies();

private:
	std::list<std::shared_ptr<GameObject>>& objects;
	std::vector<ObjModel*>& models;
	const float spawnEnemyOffset;

	int getRandomEnemy();
};

