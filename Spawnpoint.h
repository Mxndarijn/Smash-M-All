#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Spawnpoint {
public:
	glm::vec3 pos;
	int rot;
	Spawnpoint(glm::vec3 pos, int rot);
	~Spawnpoint();
};