#include "border_object.h"

BorderObject::BorderObject() : GameObject()
{
	Position = glm::vec2{-1, -1};
	Size = glm::vec2{ 1, 1 };
}

BorderObject::BorderObject(glm::vec2 pos, glm::vec2 size)
	: GameObject()
{
	Position = pos;
	Size = size;
	Velocity = glm::vec2(0.0f, -1.0f);
}

glm::vec2 BorderObject::Move(float dt)
{
    this->Position += this->Velocity * dt * Speed;

	return this->Position;
}

void BorderObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}
