#include "GameManager.h"
#include <iostream>
#include "MoveEnemyComponent.h"
#include "ModelComponent.h"

auto removeDead = [](std::shared_ptr<GameObject> object)
{
	if (object->isDead)
	{
		std::cout << "Removing enemies\n";
		return true;
	}
	return false;
};

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<ObjModel*>& models) : objects(objects), models(models), spawnEnemyOffset(75.f)
{

}

GameManager::~GameManager()
{

}

void GameManager::init()
{
	//load world
}

void GameManager::spawnEnemy(std::shared_ptr<GameObject>& camera) {

	auto enemey = std::make_shared<GameObject>();
	enemey->position = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * spawnEnemyOffset)), camera->position.y, -(camera->position.z + (cos(camera->rotation.y) * spawnEnemyOffset)));
	if ((camera->rotation.y <= 100 && camera->rotation.y > 80) || camera->rotation.y > 230)
	{
		enemey->rotation.y = camera->rotation.y + glm::radians(180.f);
	}
	else
	{
		enemey->rotation.y = -camera->rotation.y;
	}

	enemey->addComponent(std::make_shared<ModelComponent>(models[getRandomEnemy()]));
	enemey->addComponent(std::make_shared<MoveEnemyComponent>(camera)); // camera type?
	objects.push_back(enemey);
}

int GameManager::getRandomEnemy() {
	int listSize = models.size();
	return 1 + (rand() % (listSize - 1));
}

void GameManager::update()
{

}

void GameManager::despawnEnemies()
{
	objects.remove_if(removeDead);
}
