#pragma once
#include <list>
#include <memory>
#include "GameObject.h"

class GameManager
{
public:
	GameManager(std::list<std::shared_ptr<GameObject>>& objects);
	~GameManager();

	void spawnEnemies();
	void update();
	void init();
	void despawnEnemies();

private:
	std::list<std::shared_ptr<GameObject>>& objects;
};

