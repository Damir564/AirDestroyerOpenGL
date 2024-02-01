#include "chunk_object.h"
#include "game.h"


ChunkObject::ChunkObject()
    : Position(0.0f, 0.0f), Size(0.5f, 0.5f), Velocity(0.0f), IsSolid(false), Destroyed(false) 
{
    Enemies.push_back(new EnemyObject(glm::vec2 {0.0f, 0.0f}, PLAYER_SIZE, ResourceManager::GetTexture("player")));
}

ChunkObject::ChunkObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), IsSolid(false), Destroyed(false) { }

void ChunkObject::Move(float dt)
{
    for (EnemyObject* enemy : Enemies)
    {
        enemy->Move(dt);
    }
}

void ChunkObject::Draw(SpriteRenderer& renderer)
{
    for (EnemyObject* enemy : Enemies)
    {
        enemy->Draw(renderer);
    }
}








