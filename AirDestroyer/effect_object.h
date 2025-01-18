#pragma once
#include "game_object.h"

const float ANIM_TIME = 0.4f;

class EffectObject : public GameObject
{
public:
    // EffectObject();
    EffectObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, glm::vec3 color, Texture2D sprite);
    // void Update(const float dt);
    glm::vec2 Update(const float dt, const float parentVelocity = 0.0f);
    // glm::vec2 Move(float dt, float playerPositionX);
    // resets the ball to original state with given position and velocity
    // void      Reset(glm::vec2 position, glm::vec2 velocity);
private:
    float m_fTimeLastChangeSprite;
    short m_iCurrentSprite;
};

