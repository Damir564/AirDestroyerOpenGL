#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
//#include <tuple>
#include <iostream>
// #include "game_object.h"
//#include "program.h"
//#include "game_level.h"
//#include "power_up.h"

// Represents the current state of the game
//enum GameState {
//    GAME_ACTIVE,
//    GAME_MENU,
//    GAME_WIN
//};
//
//// Represents the four possible (collision) directions
//enum Direction {
//    UP,
//    RIGHT,
//    DOWN,
//    LEFT
//};
// Defines a Collision typedef that represents collision data
//typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(50.0f, 50.0f);
const float PLAYER_OFFSET_Y = 170.0f;
const float PLAYER_OFFSET_X = 50.0f;
// const float PLAYER_POSITION_Y = 170.0f;
const glm::vec2 PLAYER_VELOCITY(300.0f, 200.0f);
// const glm::vec2 PLAYER_VELOCITY(300.0f, 500.0f);

const glm::vec2 PROJECTILE_SIZE(8.0f, 30.0f);
const glm::vec2 PROJECTILE_VELOCITY(0.0f, -1400.0f);
// const glm::vec2 PROJECTILE_VELOCITY(0.0f, -50.0f);
const glm::vec3 PROJECTILE_COLOR = { 230.0f / 255.0f, 230.0f / 255.0f, 62.0f / 255.0f };
// const glm::vec3 PROJECTILE_COLOR = { 250.0f / 255.0f, 0.0f / 255.0f, 62.0f / 255.0f };

const glm::vec2 SHIP_SIZE(120.0f, 30.0f);
const glm::vec2 SHIP_VELOCITY(0.0f, 0.0f);

// const glm::vec2 ENEMY_VELOCITY(0.0f, 200.0f);

// const glm::vec2 CHUNK_VELOCITY(0.0f, 50.0f);
const glm::vec2 CHUNK_VELOCITY(0.0f, 400.0f);

const glm::vec2 BORDER_SIZE(125.0f, 0.0f);
const glm::vec3 BORDER_COLOR = { 0.333f, 0.651f, 0.220f };

class ProjectileObject;
class ChunkObject;
class PlayerObject;


class Game
{
public:
	//static void SetFirstTime(float value);
	//static float GetFirstTime();
    // game state
    //GameState               State;
    bool                    Keys[1024];
    bool                    KeysProcessed[1024];
    unsigned int            Width, Height;

    std::vector<ProjectileObject*> Projectiles;
    std::vector<ChunkObject*> Chunks;
    PlayerObject* Player;
    //std::vector<GameLevel>  Levels;
    //std::vector<PowerUp>    PowerUps;
    //unsigned int            Level;
    //unsigned int            Lives;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Fire();
    void Update(float dt);
    void DoCollisions();
    void Render();
    void Dispose();
    //void DoCollisions();
    // reset
    //void ResetLevel();
    void ResetPlayer();
    // powerups
    //void SpawnPowerUps(GameObject& block);
    //void UpdatePowerUps(float dt);
private:
    static float firstFrame;
    void GenerateChunks();
    void CreateChunk(int n);

    void CreatePlayer();

    void InitSpriteRenderer();
    void LoadTextures();
    void InitColorRenderer();
};
