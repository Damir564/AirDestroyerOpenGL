#pragma once

#include <glm/glm.hpp>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "game.h"
#include "game_object.h"
#include "game.h"
//#include "projectile_object.h"
//#include "texture.h"

const float PLAYER_VELOCITY_Y_BASE = 400.0f;
const float PLAYER_VELOCITY_Y_UP = PLAYER_VELOCITY_Y_BASE * 1.5f;
const float PLAYER_VELOCITY_Y_DOWN = PLAYER_VELOCITY_Y_BASE / 2.0f;
const float SHOOT_COOL_DOWN = 0.5f;
const float DISTANCE_MULTIPLIER = 0.002f;

class PlayerObject : public GameObject
{
public:
    
    //float   Radius;
    //bool    Stuck;
    //bool    Sticky, PassThrough;
    // float projectileSpeed = 200.0f;
    // constructor(s)
    // std::unique_ptr<SoundEffectsPlayer> m_pSoundEffectsPlayer;
    PlayerObject();
    PlayerObject(glm::vec2 pos
        , glm::vec2 size
        , glm::vec2 velocity = glm::vec2(0.0f, 0.0f)
        , glm::vec3 color = glm::vec3(1.0f)
        , Texture2D sprite = Texture2D());
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    void Update(const float dt);
    //glm::vec2 ProcessInput(float dt, Game* game);
    void Move(const float dt, const Game& game);
    bool Shoot(glm::vec2& projectilePos);
    int GetDistance();
    ~PlayerObject() override;
    // resets the ball to original state with given position and velocity
    // void      Reset(glm::vec2 position, glm::vec2 velocity);
private:
    bool m_canShoot;
    float m_shootTime;
    float m_fDistance;
};

