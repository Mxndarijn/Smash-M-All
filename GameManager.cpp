#include "GameManager.h"
#include <iostream>
#include "MoveEnemyComponent.h"
#include "ModelComponent.h"
int aliveEnemies = 0;
int count = 2;

auto removeDead = [](std::shared_ptr<GameObject> object)
{
	if (object->isDead)
	{
		aliveEnemies--;
		std::cout << "Removing enemies\nAlive enemies: " << aliveEnemies << std::endl;;
		return true;
	}
	return false;
};

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<ObjModel*>& models, std::shared_ptr<GameObject>& camera) : objects(objects), models(models), camera(camera), spawnEnemyOffset(75.f)
{

}

GameManager::~GameManager()
{
	delete spawnTimer;
}

void GameManager::init()
{
	auto gameWorld = std::make_shared<GameObject>();
	gameWorld->position = glm::vec3(0, 0, 0);
	gameWorld->addComponent(std::make_shared<ModelComponent>(models[0]));
	objects.push_back(gameWorld);

	spawnTimer = new Timerf(5000, enableEnemySpawn);
}

void GameManager::spawnEnemy() 
{
	auto enemy = std::make_shared<GameObject>();
	enemy->position = randomizeEnemyPos(camera);
	enemy->rotation.y = -camera->rotation.y;
	enemy->addComponent(std::make_shared<ModelComponent>(models[getRandomEnemy()]));
	enemy->addComponent(std::make_shared<MoveEnemyComponent>(camera)); 
	objects.push_back(enemy);
	aliveEnemies++;
}

void GameManager::update(bool& endscreen)
{
	if (enableEnemySpawn) {
		spawnEnemy();
		enableEnemySpawn = false;
		count--;

		if (!spawnTimer->started)
			spawnTimer->startTimer();
		if (count <= 0)
		{
			spawnTimer->started = false;
		}
	}
	//if (count <= 0 && aliveEnemies <= 0)
	//	endscreen = true;

	for (const auto& enemy : objects)
	{
		if (!enemy->isDead)
		{
			auto target = glm::vec3(-camera->position.x, camera->position.y, -camera->position.z);
			glm::vec3 direction = glm::normalize(target - enemy->position);
			if (enemy->position.x >= target.x - 10.0f && enemy->position.z >= target.z - 10.0f && direction.x >= 0 && direction.z >= 0)
			{
				enemy->isDead = true;
				lives--;
			}
			if (enemy->position.x <= target.x + 10.0f && enemy->position.z <= target.z + 10.0f && direction.x <= 0 && direction.z <= 0)
			{
				enemy->isDead = true;
				lives--;
			}
			if (enemy->position.x >= target.x - 10.0f && enemy->position.z <= target.z + 10.0f && direction.x >= 0 && direction.z <= 0)
			{
				enemy->isDead = true;
				lives--;
			}
			if (enemy->position.x <= target.x + 10.0f && enemy->position.z >= target.z - 10.0f && direction.x <= 0 && direction.z >= 0)
			{
				enemy->isDead = true;
				lives--;
			}
		}

		if (lives <= 0)
			endscreen = true;
	}
}

int GameManager::getRandomEnemy() {
	int listSize = models.size();
	return 2 + (rand() % (listSize - 2)); // -2 and +2 because index 0 is the world and index 1 is a powerup, not an enemy.
}

glm::vec3 GameManager::randomizeEnemyPos(std::shared_ptr<GameObject>& camera) {
	glm::vec3 enemyPos;
	int random = rand() % 2;

	if (random == 0)
	{
		enemyPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * spawnEnemyOffset) + rand() % 50), camera->position.y - (rand() % 20), -(camera->position.z + (cos(camera->rotation.y) * spawnEnemyOffset)) + rand() % 50);
	}
	else 
	{
		enemyPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * spawnEnemyOffset) - rand() % 50), camera->position.y + (rand() % 20), -(camera->position.z + (cos(camera->rotation.y) * spawnEnemyOffset)) - rand() % 50);
	}
	return enemyPos;
}

void GameManager::despawnEnemies()
{
	objects.remove_if(removeDead);
}
