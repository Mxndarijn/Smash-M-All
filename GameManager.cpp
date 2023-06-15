#include "GameManager.h"
#include <iostream>

auto removeDead = [](std::shared_ptr<GameObject> object)
{
	if (object->isDead)
	{
		std::cout << "Removing enemies\n";
		return true;
	}
	return false;
};

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects) : objects(objects)
{

}

GameManager::~GameManager() 
{

}

void GameManager::init() 
{

}

void GameManager::spawnEnemies() 
{

}

void GameManager::update() 
{

}

void GameManager::despawnEnemies() 
{
	objects.remove_if(removeDead);
}
