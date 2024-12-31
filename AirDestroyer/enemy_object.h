#pragma once

#include "game_object.h"

#define ENEMY_SCORE 1

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
    // EnemyObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    EnemyObject(glm::vec2 pos
        , glm::vec2 size
        , glm::vec2 velocity = glm::vec2(0.0f, 0.0f)
        , glm::vec3 color = glm::vec3(0.0f)
        , Texture2D sprite = Texture2D());
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(float dt, const float parentVelocity = 0.0f);
    // resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);

    // Physics part (has to implement interface or absract class for it later)
    //bool DoCollisions(GameObject* gameObject);
    //bool CheckCollision(glm::vec2 aPosition
    //    , glm::vec2 aSize
    //    , glm::vec2 bPosition
    //    , glm::vec2 bSize);
};