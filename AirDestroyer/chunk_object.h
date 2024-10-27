#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "utilities/resource_manager.h"
#include "utilities/sprite_renderer.h"
#include "utilities/color_renderer.h"
#include "game_object.h"
#include "enemy_object.h"
#include "border_object.h"

class ProjectileObject;


class ChunkObject : public GameObject
{
public:
    //glm::vec2   Position;
    //bool        IsSolid;
    std::vector<EnemyObject> Enemies;
    std::vector<BorderObject> Borders;

    // ChunkObject(float startHeight);
    ChunkObject(int width, int height, int number);
    void Move(const float dt, const float fPlayerVelocityY);
     
    // void Draw(SpriteRenderer& spriteRenderer, ColorRenderer& colorRenderer);
    void Draw(SpriteRenderer& renderer) override;
    void Draw(ColorRenderer& renderer) override;

    bool Dispose();
    float _offset;
    // Physics
    // void DoCollisions(std::vector<ProjectileObject*> projectiles);
//    bool Destroyed() { return _destroyed; }
//private:
//    bool _destroyed;
private:
    // float _offset;
};
