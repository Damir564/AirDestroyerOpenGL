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
#include "effect_object.h"

// class ProjectileObject;


class ChunkObject : public GameObject
{
public:
    //glm::vec2   Position;
    //bool        IsSolid;
    std::vector<EnemyObject> Enemies;
    std::vector<BorderObject> Borders;
    std::vector<EffectObject> Effects;

    // ChunkObject(float startHeight);
    ChunkObject(int width, int height, int number);
    void Update(const float dt, const float fPlayerVelocityY);
    void CreateEffect(const glm::vec2 pos);
     
    // void Draw(SpriteRenderer& spriteRenderer, ColorRenderer& colorRenderer);
    void Draw(std::unique_ptr<SpriteRenderer>& renderer) override;
    void Draw(std::unique_ptr<ColorRenderer>& renderer) override;

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
