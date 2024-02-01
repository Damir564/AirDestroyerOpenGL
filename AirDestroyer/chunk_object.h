#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "utilities/resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "enemy_object.h"


class ChunkObject
{
public:
    // object state
    glm::vec2   Position, Size, Velocity;
    bool        IsSolid;
    bool        Destroyed;
    std::vector<EnemyObject*> Enemies;
    

    
    // constructor(s)
    ChunkObject();
    ChunkObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    void Move(float dt);
    void Draw(SpriteRenderer& renderer);
    // draw sprite
    
};
