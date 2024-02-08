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
    //glm::vec2   Position;
    //bool        IsSolid;
    std::vector<EnemyObject*> Enemies;

    // ChunkObject(float startHeight);
    ChunkObject(int width, int height, int number);
    void Move(float dt);
    void Draw(SpriteRenderer& renderer);

    bool IsDisposable() { return _isDisposable; }
private:
    bool _isDisposable;
    float _offset;
};
