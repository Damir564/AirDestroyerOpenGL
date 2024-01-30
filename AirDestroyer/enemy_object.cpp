#include "enemy_object.h"
#include <iostream>

EnemyObject::EnemyObject() : GameObject()
{
}

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity )
	: GameObject()
{
	Position = pos;
	Size = size;
	Sprite = sprite;
	Velocity = glm::vec2(0.0f, 1.0f);
}

glm::vec2 EnemyObject::Move(float dt)
{
	this->Position += this->Velocity * dt * Speed;
	return this->Position;
}

void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}