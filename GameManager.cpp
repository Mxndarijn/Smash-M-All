#include "GameManager.h"
#include <iostream>
#include "MoveEnemyComponent.h"
#include "ModelComponent.h"
#include "BoundingBoxComponent.h"
#include "RayCastComponent.h"

#define SPAWN_OFFSET 100
#define TIME_MAX 100

int aliveEnemies = 0;
int count = 2;

int lives;

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

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<ObjModel*>& models, std::shared_ptr<GameObject>& camera, int &difficulty) : objects(objects), models(models), camera(camera), spawnEnemyOffset(75.f), difficulty(difficulty)
{
	lives = 3;
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
	enemy->addComponent(std::make_shared<BoundingBoxComponent>(glm::vec3(-1, 2, -1), glm::vec3(1, 4.5, 1)));
	objects.push_back(enemy);
	aliveEnemies++;
}

void GameManager::update(bool& endscreen)
{
	auto lines = camera->getComponent<RayCastComponent>()->lines;

	if (lives <= 0)
	{
		for (const auto& enemy : objects)
		{
			if(enemy->getComponent<BoundingBoxComponent>() != nullptr)
				enemy->isDead = true;

		}
			
		spawnTimer->started = false;
		enableEnemySpawn = false;
		endscreen = true;
	}

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
	}

	if (enableEnemySpawn) {
		spawnEnemy();
		enableEnemySpawn = false;

		if (!spawnTimer->started)
		{
			spawnTimer->changeDelay((rand() % TIME_MAX) + difficulty);
			spawnTimer->startTimer();
		}
		if (count <= 0)
		{
			spawnTimer->started = false;
		}
	}

	for (const auto& object : objects)
	{
		auto boundingBox = object->getComponent<BoundingBoxComponent>();

		if (boundingBox != nullptr)
		{
			for (const auto& line : lines)
			{
				if (boundingBox->collide(std::get<0>(line), std::get<1>(line)) && lives > 0)
				{
					std::cout << "Found collision removing object\n";
					score++;
					object->isDead = true;
				}
			}
		}
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
		enemyPos = glm::vec3(-(camera->position.x + (-sin(camera->rotation.y) * spawnEnemyOffset) - rand() % 50), camera->position.y + (rand() % 20), -(camera->position.z + (cos(camera->rotation.y) * spawnEnemyOffset)) + rand() % 50);
	}
	return enemyPos;
}

void GameManager::despawnEnemies()
{
	objects.remove_if(removeDead);
}
