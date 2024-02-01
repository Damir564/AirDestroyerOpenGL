#pragma once

#include "game_object.h"

class EnemyObject : public GameObject
{
public:
    // ball state	
    //float   Radius;
    //bool    Stuck;
    //bool    Sticky, PassThrough;
    // float Speed = 200.0f;
    // constructor(s)
    EnemyObject();
    EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(float dt);
    // resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};