#include "projectile_object.h"
#include <iostream>

ProjectileObject::ProjectileObject() : GameObject()
{
}

ProjectileObject::ProjectileObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
	: GameObject()
{
	Position = pos;
	Size = size;
	Velocity = velocity;
}

glm::vec2 ProjectileObject::Move(float dt)
{
    this->Position.y += this->Velocity.y * dt;

	
	if (this->Position.y <= 0.0f)
	{
		IsDisposable = true;
		std::cout << this->Position.y << std::endl;
	}

	return this->Position;
}

void ProjectileObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}
