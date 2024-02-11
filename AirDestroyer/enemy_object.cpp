#include "enemy_object.h"
#include <iostream>

EnemyObject::EnemyObject() : GameObject()
{
}

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, glm::vec3 color, Texture2D sprite)
	: GameObject(pos, size, velocity, color, sprite)
{
	//Position = pos;
	//Size = size;
	//Sprite = sprite;
	//Velocity = glm::vec2(0.0f, 1.0f);
}

glm::vec2 EnemyObject::Move(float dt, glm::vec2 parentVelocity)
{
	this->Position.y += dt * (parentVelocity.y + this->Velocity.y);
	return this->Position;
}

void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}