#include "chunks_object.h"

ChunksObject::ChunksObject(glm::vec2 size, glm::vec2 velocity) 
{
	Size = size;
	Velocity = velocity;
	Position = glm::vec2(0.0f);
}

glm::vec2 ChunksObject::Move(float dt)
{
	return glm::vec2();
}

glm::vec2 ChunksObject::MoveEnemy(float dt) 
{
    Enemy->Move(dt);
    if (Enemy->Position.y >= this->Height) {
        srand(time(NULL));
        const float enemyPosX = (rand() % 6) * Width / 6;
        glm::vec2 enemyPos = glm::vec2(enemyPosX, 50.0f);
        Enemy = new EnemyObject(enemyPos, PLAYER_SIZE, ResourceManager::GetTexture("enemy"));
    }
}