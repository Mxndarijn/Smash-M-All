#include "Spawnpoint.h"
#include <glm/gtc/matrix_transform.hpp>

Spawnpoint::Spawnpoint(glm::vec3 pos, int rot) : pos(pos), rot(rot)
{
}

Spawnpoint::~Spawnpoint() {}