#include "player_object.h"


PlayerObject::PlayerObject() : GameObject(), CanShoot(true)
{ }

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : GameObject(pos, size, sprite, color, velocity), CanShoot(true)
{ }

void PlayerObject::Move(float dt, Game* game)
{
    
    if (game->Keys[GLFW_KEY_A])
    {
        if (Position.x >= PLAYER_OFFSET_X)
        {
            Position.x -= Velocity.x * dt;
        }
    }
    if (game->Keys[GLFW_KEY_D])
    {
        if (Position.x <= game->Width - Size.x - PLAYER_OFFSET_X)
        {
            Position.x += Velocity.x * dt;
        }
    }
}

bool PlayerObject::Shoot(Game* game, glm::vec2* projectilePos)
{
    if (CanShoot)
    {
        // Process Audio
        std::cout << "Piu" << std::endl;

        CanShoot = false;
        ShootTime = (float)glfwGetTime();

        *projectilePos = glm::vec2(Position.x + 20.0f, Position.y);

        return true;
    }
    if ((float)glfwGetTime() - this->ShootTime >= CoolDown)
    {
        CanShoot = true;

        return false;
    }
}

