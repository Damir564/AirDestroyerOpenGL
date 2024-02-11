#include "player_object.h"


PlayerObject::PlayerObject() : GameObject(), _canShoot(true)
{ }

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, glm::vec3 color, Texture2D sprite)
    : GameObject(pos, size, velocity, color, sprite), _canShoot(true)
{ }

void PlayerObject::Turn(float dt, Game& game)
{
    
    if (game.Keys[GLFW_KEY_A])
    {
        if (Position.x >= PLAYER_OFFSET_X)
        {
            Position.x -= Velocity.x * dt;
        }
    }
    if (game.Keys[GLFW_KEY_D])
    {
        if (Position.x <= game.Width - Size.x - PLAYER_OFFSET_X)
        {
            Position.x += Velocity.x * dt;
        }
    }
}

bool PlayerObject::Shoot(glm::vec2& projectilePos)
{
    if (_canShoot)
    {
        // Process Audio
        std::cout << "Piu" << std::endl;

        _canShoot = false;
        _shootTime = (float)glfwGetTime();

        projectilePos = glm::vec2(Position.x + 20.0f, Position.y);

        return true;
    }
    if ((float)glfwGetTime() - this->_shootTime >= _coolDown)
    {
        _canShoot = true;

        // return false;
    }
    return false;
}

