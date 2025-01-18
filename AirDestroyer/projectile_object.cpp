#include "projectile_object.h"
#include "game.h"
#include <iostream>

ProjectileObject::ProjectileObject() : GameObject()
{
}

ProjectileObject::ProjectileObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
	: GameObject(pos, size, velocity, PROJECTILE_COLOR) { }

//glm::vec2 ProjectileObject::Move(float dt)
//{
//    this->Position.y += this->Velocity.y * dt;
//
//	
//	if (this->Position.y <= -PROJECTILE_SIZE.y)
//	{
//		IsDestroyed = true;
//		std::cout << this->Position.y << std::endl;
//	}
//
//	return this->Position;
//}

glm::vec2 ProjectileObject::Update(float dt, float playerPositionX)
{
	this->Position.y += this->Velocity.y * dt;
	this->Position.x = playerPositionX + (PLAYER_SIZE.x - PROJECTILE_SIZE.x) / 2;


	if (this->Position.y < 0)
	{
		IsDestroyed = true;
	}

	return this->Position;
}

void ProjectileObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}
