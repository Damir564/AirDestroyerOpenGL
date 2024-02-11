#pragma once

#include <glm/glm.hpp>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "game.h"
#include "game_object.h"
#include "game.h"
//#include "projectile_object.h"
//#include "texture.h"

class PlayerObject : public GameObject
{
public:
    
    //float   Radius;
    //bool    Stuck;
    //bool    Sticky, PassThrough;
    // float projectileSpeed = 200.0f;
    // constructor(s)
    PlayerObject();
    PlayerObject(glm::vec2 pos
        , glm::vec2 size
        , glm::vec2 velocity = glm::vec2(0.0f, 0.0f)
        , glm::vec3 color = glm::vec3(1.0f)
        , Texture2D sprite = Texture2D());
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    //glm::vec2 Update(float dt);
    //glm::vec2 ProcessInput(float dt, Game* game);
    void Turn(float dt, Game& game);
    bool Shoot(glm::vec2& projectilePos);
    // resets the ball to original state with given position and velocity
    // void      Reset(glm::vec2 position, glm::vec2 velocity);
private:
    bool _canShoot;
    float _shootTime = 0.0f;
    float _coolDown = 0.2f;
};

