#include "chunk_object.h"
#include "game.h"
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
// #include "projectile_object.h"
#include "collision_manager.h"

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

    float borderSize = (float)createRandomNumber(1, 3) * BORDER_SIZE.x;
    Borders.push_back(BorderObject(glm::vec2{ 0.0f, _offset + height}, glm::vec2{ borderSize, height + 5.0f }));
    Borders.push_back(BorderObject(glm::vec2{ width - borderSize, _offset + height }, glm::vec2{ borderSize, height + 5.0f }));

    int enemiesAmount = createRandomNumber(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
    std::vector<int> heightPositions;
    for (int i = 1; i != height / 100 + 1; ++i)
    {
        heightPositions.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(heightPositions.begin(), heightPositions.end(), g);
    std::vector<int> enemiesHeightPositions(heightPositions.begin(), heightPositions.begin() + enemiesAmount);  
    for (int heightPosition : enemiesHeightPositions)
    {
        Enemies.push_back(EnemyObject(glm::vec2{ (float)createRandomNumber(borderSize, width - borderSize - SHIP_SIZE.x)
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

void ChunkObject::Update(float dt, float fPlayerVelocityY)
{
    for (auto& enemy : Enemies)
    {
        enemy.Update(dt, fPlayerVelocityY);
    }
    for (auto& border : Borders)
    {
        border.Update(dt, fPlayerVelocityY);
    }
    for (auto& effect : Effects)
    {
        effect.Update(dt, fPlayerVelocityY);
    }
    _offset += dt * fPlayerVelocityY;
    if (_offset >= 0.0f)
    {
        IsDestroyed = true;    
    }
}

void ChunkObject::CreateEffect(const glm::vec2 pos)
{
    Effects.push_back(EffectObject(pos, SHIP_SIZE, SHIP_VELOCITY, glm::vec3(1.0f), ResourceManager::GetTexture(EXPLOSION_SPRITES[0])));
}

void ChunkObject::Draw(std::unique_ptr<SpriteRenderer>& renderer)
{
    for (auto& enemy : Enemies)
    {
        enemy.Draw(renderer);
    }
    for (auto& effect : Effects)
    {
        effect.Draw(renderer);
    }
}

void ChunkObject::Draw(std::unique_ptr<ColorRenderer>& renderer)
{
    for (auto& border : Borders)
    {
        border.Draw(renderer);
    }
}

bool ChunkObject::Dispose()
{
    for (auto it = Enemies.begin(); it != Enemies.end(); ) {
        if (it->IsDestroyed) {
            //delete* it;
            it = Enemies.erase(it); 
        }
        else {
            ++it;
        }
    }
    for (auto it = Borders.begin(); it != Borders.end(); ) {
        if (it->IsDestroyed) {
            it = Borders.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = Effects.begin(); it != Effects.end(); ) {
        if (it->IsDestroyed) {
            it = Effects.erase(it);
        }
        else {
            ++it;
        }
    }

    return IsDestroyed;
}









