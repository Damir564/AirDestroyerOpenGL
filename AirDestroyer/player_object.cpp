#include "player_object.h"


PlayerObject::PlayerObject() : GameObject()
{
    CanShoot = true;
}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : GameObject(pos, size, sprite, color, velocity)
{
    CanShoot = true;
}

void PlayerObject::Move(float velocity)
{
    this->Position.x += velocity;
}

