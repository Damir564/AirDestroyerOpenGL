#include "projectile_object.h"

ProjectileObject::ProjectileObject() : GameObject()
{
}

ProjectileObject::ProjectileObject(glm::vec2 pos, glm::vec2 size)
	: GameObject()
{
	Position = pos;
	Size = size;
	Velocity = glm::vec2(0.0f, -1.0f);
}

glm::vec2 ProjectileObject::Move(float dt)
{
    this->Position += this->Velocity * dt * Speed;

	return this->Position;
}

void ProjectileObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}
