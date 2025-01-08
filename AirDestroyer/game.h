#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "utilities/sound_manager.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_END,
    GAME_WIN
};

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
//const glm::vec2 CHUNK_VELOCITY(0.0f, 400.0f);

const glm::vec2 BORDER_SIZE(125.0f, 0.0f);
const glm::vec3 BORDER_COLOR = { 0.333f, 0.651f, 0.220f };

// std::unique_ptr<SoundEffectsPlayer> m_pSoundEffectsPlayer;

class ProjectileObject;
class ChunkObject;
class PlayerObject;

class Game
{
public:
    GameState               State;
    bool                    Keys[1024];
    bool                    KeysProcessed[1024];
    unsigned int            Width, Height;

    
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
    void AddScore(const int scoreToAdd);
    //void DoCollisions();
    // reset
    //void ResetLevel();
    void ResetPlayer();
    void PlaySound(ALuint buffer);
    // powerups
    //void SpawnPowerUps(GameObject& block);
    //void UpdatePowerUps(float dt);
private:
    int m_score;
    // std::unique_ptr<MusicBuffer> m_pMusicBuffer;
    std::unique_ptr<SoundEffectsPlayer> m_pSoundEffectsPlayer;
    std::vector<ProjectileObject> m_vecProjectiles;
    std::vector<ChunkObject> m_vecChunks;
    std::unique_ptr<PlayerObject> m_pPlayer;
    // std::unique_ptr<SoundDevice> m_pSoundDevice;

    static float firstFrame;
    void GenerateChunks();
    void CreateChunk(int n);

    void CreatePlayer();
    void DestroyAll();

    void StartGame();
    void EndGame();

    void InitSpriteRenderer();
    void LoadTextures();
    void InitColorRenderer();

    void InitTextRenderer();
    void LoadFreeType();

    void InitSounds();
    void LoadSounds();
};

extern Game game;
