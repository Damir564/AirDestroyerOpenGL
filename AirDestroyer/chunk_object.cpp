#include "chunk_object.h"
#include "game.h"
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int MIN_SHIP_AMOUNT = 1;
const int MAX_SHIP_AMOUNT = 4;

int createRandomNumber(int minValue, int maxValue)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minValue, maxValue);
    return dist6(rng);
}

ChunkObject::ChunkObject(int width, int height, int number)
    : _offset((float)(-height * (number + 2)))
{
    IsDestroyed = false;

    float borderSize = (float)createRandomNumber(1, 5) * 40.0f;
    Borders.push_back(new BorderObject(glm::vec2{ 0.0f, _offset + height}, glm::vec2{ borderSize, height }));
    Borders.push_back(new BorderObject(glm::vec2{ width - borderSize, _offset + height }, glm::vec2{ borderSize, height }));

    int enemiesAmount = createRandomNumber(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
    std::vector<int> heightPositions;
    for (int i = 1; i != height / 100 + 1; ++i)
    {
        heightPositions.push_back(i);
    }
    std::random_shuffle(heightPositions.begin(), heightPositions.end());
    std::vector<int> enemiesHeightPositions(heightPositions.begin(), heightPositions.begin() + enemiesAmount);  
    for (int heightPosition : enemiesHeightPositions)
    {
        std::cout << "height " << heightPosition << std::endl;
        Enemies.push_back(new EnemyObject(glm::vec2{ (float)createRandomNumber(borderSize, width - borderSize - SHIP_SIZE.x)
            , _offset
            + height
            + heightPosition * 100
            - SHIP_SIZE.y * 2 }
            , SHIP_SIZE
            , SHIP_VELOCITY
            , glm::vec3(1.0f)
            , ResourceManager::GetTexture("ship")));
    }
}

void ChunkObject::Move(float dt)
{
    for (EnemyObject* enemy : Enemies)
    {
        enemy->Move(dt, CHUNK_VELOCITY);
    }
    for (BorderObject* border : Borders)
    {
        border->Move(dt, CHUNK_VELOCITY);
    }
    // we have to add velocity to the parameter and use it with CHUNK_VELOCITY
    _offset += dt * CHUNK_VELOCITY.y;
    //if (Enemies[0]->Position.y >= 0)
    //    std::cout << _offset << std::endl;
    // std::cout << _offset << std::endl;
    // std::cout << Enemies[0]->Position.y << std::endl;
    if (_offset >= 0.0f)
    {
        //std::cout << _offset << std::endl;
        IsDestroyed = true;    
    }
}

//void ChunkObject::Draw(SpriteRenderer& spriteRenderer, ColorRenderer& colorRenderer)
//{
//    for (EnemyObject* enemy : Enemies)
//    {
//        enemy->Draw(spriteRenderer);
//    }
//}

void ChunkObject::Draw(SpriteRenderer& renderer)
{
    for (EnemyObject* enemy : Enemies)
    {
        enemy->Draw(renderer);
    }
}

void ChunkObject::Draw(ColorRenderer& renderer)
{
    for (BorderObject* border : Borders)
    {
        border->Draw(renderer);
    }
}









