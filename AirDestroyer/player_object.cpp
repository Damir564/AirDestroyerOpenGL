#include "player_object.h"
#include "utilities/resource_manager.h"
#include <thread>
#include <chrono>
#include <iostream>


PlayerObject::PlayerObject() : GameObject(), m_canShoot(true), m_shootTime(0.0f), m_fDistance(0.0f)
{ }

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, glm::vec3 color, Texture2D sprite)
    : GameObject(pos, size, velocity, color, sprite), m_canShoot(true), m_shootTime(0.0f), m_fDistance(0.0f)// , m_pSoundEffectsPlayer(std::make_unique<SoundEffectsPlayer>())
{ }

void PlayerObject::Update(const float dt)
{
    if ((float)glfwGetTime() - this->m_shootTime > SHOOT_COOL_DOWN)
    {
        m_canShoot = true;
    }
    m_fDistance += Velocity.y * dt * DISTANCE_MULTIPLIER;
}

void PlayerObject::Move(const float dt, const Game& game)
{
    
    if (game.Keys[GLFW_KEY_A] || game.Keys[GLFW_KEY_LEFT])
    {
        Position.x -= Velocity.x * dt;
        Sprite = ResourceManager::GetTexture("player_left");     
    }
    if (game.Keys[GLFW_KEY_D] || game.Keys[GLFW_KEY_RIGHT])
    {
        Position.x += Velocity.x * dt;
        Sprite = ResourceManager::GetTexture("player_right");
    }
    if (!(game.Keys[GLFW_KEY_A] || game.Keys[GLFW_KEY_LEFT]
        || game.Keys[GLFW_KEY_D] || game.Keys[GLFW_KEY_RIGHT]))
    {
        Sprite = ResourceManager::GetTexture("player");
    }

    if (game.Keys[GLFW_KEY_W] || game.Keys[GLFW_KEY_UP])
        Velocity.y = PLAYER_VELOCITY_Y_UP;
    else if (game.Keys[GLFW_KEY_S] || game.Keys[GLFW_KEY_DOWN])
        Velocity.y = PLAYER_VELOCITY_Y_DOWN;
    else
        Velocity.y = PLAYER_VELOCITY_Y_BASE;
}

bool PlayerObject::Shoot(glm::vec2& projectilePos)
{
    if (m_canShoot)
    {
        game.PlaySound(ResourceManager::Sounds["fire"]);

        m_canShoot = false;
        m_shootTime = (float)glfwGetTime();

        projectilePos = glm::vec2(Position.x + (PLAYER_SIZE.x - PROJECTILE_SIZE.x) / 2, Position.y);

        return true;
    }
    //if ((float)glfwGetTime() - this->m_shootTime > m_coolDown)
    //{
    //    m_canShoot = true;

    //    // return false;
    //}
    return false;
}

int PlayerObject::GetDistance()
{
    return (int)m_fDistance;
}

PlayerObject::~PlayerObject()
{
    // m_pSoundEffectsPlayer->Stop();
    // m_pSoundEffectsPlayer->~SoundEffectsPlayer();
}

