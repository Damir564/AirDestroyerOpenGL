#pragma once


//#include <glad/glad.h>
//#include <glm/glm.hpp>

#include "game_object.h"
//#include "texture.h"


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class ProjectileObject : public GameObject
{
public:
    // ball state	
    //float   Radius;
    //bool    Stuck;
    //bool    Sticky, PassThrough;
    // float Speed = 400.0f;
    // bool IsDisposable = false;
    // constructor(s)
    ProjectileObject();
    ProjectileObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity);
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    // glm::vec2 Move(float dt);
    glm::vec2 Update(float dt, float playerPositionX);
    // resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};

