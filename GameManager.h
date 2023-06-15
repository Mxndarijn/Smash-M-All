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

	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<ObjModel*>& models, std::shared_ptr<GameObject>& camera);
	~GameManager();

	void spawnEnemy();
	void update();
	void init();
	void despawnEnemies();

private:
	std::shared_ptr<GameObject>& camera;
	std::list<std::shared_ptr<GameObject>>& objects;
	std::vector<ObjModel*>& models;
	const float spawnEnemyOffset;
	bool enableEnemySpawn = false;
	Timerf* spawnTimer;

	int getRandomEnemy();
};

