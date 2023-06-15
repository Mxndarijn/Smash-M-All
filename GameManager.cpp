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
	auto gameWorld = std::make_shared<GameObject>();
	gameWorld->position = glm::vec3(0, 0, 0);
	gameWorld->addComponent(std::make_shared<ModelComponent>(models[0]));
	objects.push_back(gameWorld);
}

void GameManager::spawnEnemy(std::shared_ptr<GameObject>& camera) 
{
	auto enemy = std::make_shared<GameObject>();
	enemy->position = randomizeEnemyPos(camera);
	if ((camera->rotation.y <= 100 && camera->rotation.y > 80) || camera->rotation.y > 230)
	{
		enemy->rotation.y = camera->rotation.y + glm::radians(180.f);
	}
	else
	{
		enemy->rotation.y = -camera->rotation.y;
	}
	enemy->addComponent(std::make_shared<ModelComponent>(models[getRandomEnemy()]));
	enemy->addComponent(std::make_shared<MoveEnemyComponent>(camera)); // camera type?
	objects.push_back(enemy);
}

int GameManager::getRandomEnemy() {
	int listSize = models.size();
	return 2 + (rand() % (listSize - 2)); // -2 and +2 because index 0 is the world and index 1 is a powerup, not an enemy.
}

void GameManager::update()
{

}

glm::vec3 GameManager::randomizeEnemyPos(std::shared_ptr<GameObject>& camera) {
	glm::vec3 enemyPos;

	int random = rand() % 2;

	if (random == 0)
	{
		enemyPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * spawnEnemyOffset) + (rand() % 100)), camera->position.y - (rand() % 20), -(camera->position.z + (cos(camera->rotation.y) * spawnEnemyOffset)) + (rand() % 100));
	}
	else 
	{
		enemyPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * spawnEnemyOffset) - (rand() % 100)), camera->position.y + (rand() % 20), -(camera->position.z + (cos(camera->rotation.y) * spawnEnemyOffset)) - (rand() % 100));
	}
	return enemyPos;
}

void GameManager::despawnEnemies()
{
	objects.remove_if(removeDead);
}
