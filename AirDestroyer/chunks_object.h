#pragma once
#include "game.h"

EnemyObject* Enemy;
class ChunksObject
{
public:
	glm::vec2  Position, Size, Velocity;
	std::vector<EnemyObject> Enemies;
	ChunksObject(glm::vec2 size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	glm::vec2 Move(float dt);
	glm::vec2 MoveEnemy(float dt);
};
