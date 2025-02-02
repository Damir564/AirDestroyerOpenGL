#include "border_object.h"
#include "game.h"

BorderObject::BorderObject() : GameObject() { }

BorderObject::BorderObject(glm::vec2 pos, glm::vec2 size)
	: GameObject(glm::vec2{pos.x, pos.y}, size, glm::vec2{0.0f}, BORDER_COLOR) { }

glm::vec2 BorderObject::Update(float dt, const float parentVelocity)
{
	this->Position.y += dt * (parentVelocity + this->Velocity.y);
	return this->Position;
}
