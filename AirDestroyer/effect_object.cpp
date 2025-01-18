#include "effect_object.h"
#include "game.h"
#include <resource_manager.h>

EffectObject::EffectObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, glm::vec3 color, Texture2D sprite)
	: GameObject(pos, size, velocity, color, sprite)
	, m_fTimeLastChangeSprite(glfwGetTime())
	, m_iCurrentSprite(0){ }


glm::vec2 EffectObject::Update(const float dt, const float parentVelocity)
{
	if (((float)glfwGetTime() - m_fTimeLastChangeSprite) > ANIM_TIME)
	{
		m_iCurrentSprite = m_iCurrentSprite + 1;
		m_fTimeLastChangeSprite = (float)glfwGetTime();
		if (m_iCurrentSprite >= 3)
			this->IsDestroyed = true;
		else
			this->Sprite = ResourceManager::GetTexture(EXPLOSION_SPRITES[m_iCurrentSprite % EXPLOSION_SPRITES.size()]);
	}
	this->Position.y += dt * (parentVelocity + this->Velocity.y);
	return this->Position;
}
