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
const glm::vec2 PLAYER_SIZE(50.0f, 45.0f);
const float PLAYER_OFFSET_Y = 150.0f;
const float PLAYER_OFFSET_X = 50.0f;
const glm::vec2 PLAYER_VELOCITY(300.0f, 200.0f);

const glm::vec2 PROJECTILE_SIZE(6.0f, 6.0f);
const glm::vec2 PROJECTILE_VELOCITY(0.0f, -300.0f);

const glm::vec2 SHIP_SIZE(100.0f, 25.0f);

// const glm::vec2 ENEMY_VELOCITY(0.0f, 200.0f);

const glm::vec2 CHUNK_VELOCITY(0.0f, 200.0f);
//// Initial velocity of the Ball
//const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
//const float BALL_RADIUS = 12.5f;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
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

    void CreateSpriteRenderer();
    void LoadTextures();
    void CreateColorRenderer();
};
