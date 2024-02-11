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

const int MIN_SHIP_AMOUNT = 1;
const int MAX_SHIP_AMOUNT = 4;

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

//ChunkObject::ChunkObject(float startHeight)
//    : Position(glm::vec2{0.0f, startHeight}), IsSolid(false), IsDisposed(false)
//{
//    //int enemiesAmount = getRandomValue(1, 4);
//    int enemiesAmount = createRandomNumber(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
//    for (int i = 0; i != enemiesAmount; ++i)
//    {
//        //Enemies.push_back(new EnemyObject(glm::vec2{ (float)getRandomValue(1, 8) * 100 - 90, (float)getRandomValue(-4, 0) * 100 }
//        Enemies.push_back(new EnemyObject(glm::vec2{ (float)createRandomNumber(1, 8) * 100 - 100, (float)createRandomNumber(0, 6) * 100 - Position.y}
//            , SHIP_SIZE
//            , ResourceManager::GetTexture("ship")
//            , glm::vec3(1.0f)
//            , CHUNK_VELOCITY));
//    }
//}

ChunkObject::ChunkObject(int width, int height, int number)
    : _offset((float)(-height * (number + 2)))//, _destroyed(false)
{
    IsDestroyed = false;

    float borderSize = (float)createRandomNumber(1, 5) * 40.0f;
    Borders.push_back(new BorderObject(glm::vec2{ 0.0f, _offset + height}, glm::vec2{ borderSize, height }));
    Borders.push_back(new BorderObject(glm::vec2{ width - borderSize, _offset + height }, glm::vec2{ borderSize, height }));

    int enemiesAmount = createRandomNumber(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
    //for (int i = 0; i != enemiesAmount; ++i)
    //{
    //    Enemies.push_back(new EnemyObject(glm::vec2{ (float)createRandomNumber(borderSize + SHIP_SIZE.x, width - borderSize - SHIP_SIZE.x)
    //        , _offset
    //        + height
    //        + (float)createRandomNumber(0, height / 100) * 100
    //        - SHIP_SIZE.y }
    //        , SHIP_SIZE
    //        , SHIP_VELOCITY
    //        , glm::vec3(1.0f)
    //        , ResourceManager::GetTexture("ship")));
    //}
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









