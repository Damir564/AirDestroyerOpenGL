#include "chunk_object.h"
#include "game.h"
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>


//ChunkObject::ChunkObject(glm::vec2 pos)
//    : Position(pos), IsSolid(false), Destroyed(false)
//{
//    Enemies.push_back(new EnemyObject(Position, PLAYER_SIZE, ResourceManager::GetTexture("player"), glm::vec3(1.0f), ENEMY_VELOCITY));
//}

int createRandomNumber(int minValue, int maxValue)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minValue, maxValue);
    return dist6(rng);
}

//int getRandomValue(int minValue, int maxValue) {
//    srand(time(NULL)); // seed the random number generator with the current time
//    int range = maxValue - minValue + 1; // calculate the range of values to choose from
//    int randomValue = rand() % range + minValue; // generate a random value within the range
//    return randomValue;
//}

ChunkObject::ChunkObject(float startHeight)
    : Position(glm::vec2{0.0f, startHeight}), IsSolid(false), IsDisposable(false)
{
    //int enemiesAmount = getRandomValue(1, 4);
    int enemiesAmount = createRandomNumber(1, 8);
    for (int i = 0; i != enemiesAmount; ++i)
    {
        //Enemies.push_back(new EnemyObject(glm::vec2{ (float)getRandomValue(1, 8) * 100 - 90, (float)getRandomValue(-4, 0) * 100 }
        Enemies.push_back(new EnemyObject(glm::vec2{ (float)createRandomNumber(1, 8) * 100 - 100, (float)createRandomNumber(0, 6) * 100 - 600}
            , SHIP_SIZE
            , ResourceManager::GetTexture("ship")
            , glm::vec3(1.0f)
            , CHUNK_VELOCITY));
    }
}

void ChunkObject::Move(float dt)
{
    for (EnemyObject* enemy : Enemies)
    {
        enemy->Move(dt);
    }
    Position.y += CHUNK_VELOCITY.y * dt;
    if (Position.y >= 600)
    {
        IsDisposable = true;
    }
}

void ChunkObject::Draw(SpriteRenderer& renderer)
{
    for (EnemyObject* enemy : Enemies)
    {
        enemy->Draw(renderer);
    }
}









