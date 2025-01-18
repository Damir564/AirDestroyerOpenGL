#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class BorderObject : public GameObject
{
public:
    // ball state	
    //float   Radius;
    //bool    Stuck;
    //bool    Sticky, PassThrough;
    // float Speed = 400.0f;
    // constructor(s)
    BorderObject();
    BorderObject(glm::vec2 pos, glm::vec2 size);
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Update(float dt, const float parentVelocity);
    // resets the ball to original state with given position and velocity
    // void      Reset(glm::vec2 position, glm::vec2 velocity);
};

