#pragma once

//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include "utilities/texture.h"
#include "utilities/sprite_renderer.h"
#include "utilities/color_renderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    // bool        IsSolid;
    bool        IsDestroyed;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    // GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(0.0f), Texture2D sprite = Texture2D());
    // draw sprite
    virtual void Draw(std::unique_ptr<SpriteRenderer>& renderer);
    virtual void Draw(std::unique_ptr<ColorRenderer>& renderer);
    virtual ~GameObject();
    // virtual void Draw(SpriteRenderer& spriteRenderer, ColorRenderer& colorRenderer);
};

