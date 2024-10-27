#pragma once
#include "glm/glm.hpp"

class GameObject;

class CollisionManager
{
public:
    static bool DoCollisions(const GameObject* aGameObject, const GameObject* bGameObject, bool aPixelPerfectCollision = true, bool bPixelPerfectCollision = true);
    static bool CheckMask(const GameObject* aGameObject, int xOffset, int yOffset);
    //static bool CheckCOllisionAABB(glm::vec2 aPosition
    //    , glm::vec2 aSize
    //    , glm::vec2 bPosition
    //    , glm::vec2 bSize);
    //static bool CheckCollisionRect(GameObject* aGameObject, GameObject* bGameObject);
    // static bool CheckCollision(GameObject* aGameObject, GameObject* bGameObject, bool aPixelPerfectCollision, bool bPixelPerfectCollision);
    //static bool CheckCollisionPixelPerfect(GameObject* aGameObject, GameObject* bGameObject, bool aPixelPerfectCollision, bool bPixelPerfectCollision);
    //static bool CheckCollision(glm::vec2 aPosition
    //    , glm::vec2 aSize
    //    , glm::vec2 bPosition
    //    , glm::vec2 bSize);
private:
    CollisionManager() { }
};
