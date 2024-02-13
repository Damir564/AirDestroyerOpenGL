#include "game.h"
#include "projectile_object.h"
#include "player_object.h"
#include "chunk_object.h"
#include "utilities/resource_manager.h"
#include "utilities/sprite_renderer.h"
#include "utilities/color_renderer.h"
#include "collision_manager.h"


//Instantiate static variables
float Game::firstFrame;

// Game-related State data
SpriteRenderer* spriteRenderer;
ColorRenderer* colorRenderer;
//ProjectileObject* Projectile;
const int CHUNKS_AMOUNT_BUFFER = 8;
//PlayerObject* Player;
// ChunkObject* Chunk;

//float timer = 0.5f;

//void Game::SetFirstTime(float value)
//{
//    Game::firstFrame = value;
//}
//
//float Game::GetFirstTime()
//{
//    return Game::firstFrame;
//}

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_MENU), Keys(), KeysProcessed(), Width(width), Height(height)
{
	
}

Game::~Game()
{
}

void Game::GenerateChunks()
{
    std::cout << "Chunks generated" << std::endl;
    for (int i = 0; i != CHUNKS_AMOUNT_BUFFER; ++i)
    {
        CreateChunk(i);
    }
}

void Game::CreateChunk(int n)
{
    Chunks.push_back(new ChunkObject(Width, Height, n));
}

void Game::CreatePlayer()
{
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    // Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"), glm::vec3(1.0f), PLAYER_VELOCITY);
    Player = new PlayerObject(playerPos, PLAYER_SIZE, PLAYER_VELOCITY, glm::vec3(1.0f), ResourceManager::GetTexture("player"));
}

void Game::DestroyAll()
{
    // Player->IsDestroyed = true;
    for (ChunkObject* chunk : this->Chunks)
    {
        chunk->IsDestroyed = true;
    }
}

void Game::StartGame()
{
    this->GenerateChunks();
    this->CreatePlayer();
    this->State = GAME_ACTIVE;
}

void Game::EndGame()
{
    DestroyAll();
    this->State = GAME_MENU;
}

void Game::LoadTextures()
{
    ResourceManager::LoadTexture("resources/textures/plane.png", true, "player");
    //return;
    ResourceManager::LoadTexture("resources/textures/ship.png", true, "ship");
}

void Game::InitSpriteRenderer()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    Shader shader = ResourceManager::GetShader("sprite");
    spriteRenderer = new SpriteRenderer(shader);
}

void Game::InitColorRenderer()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::LoadShader("shaders/color.vert", "shaders/color.frag", nullptr, "color");
    ResourceManager::GetShader("color").Use();
    ResourceManager::GetShader("color").SetMatrix4("projection", projection);
    Shader colorShader = ResourceManager::GetShader("color");
    colorRenderer = new ColorRenderer(colorShader);
}


void Game::Init()
{
    this->InitSpriteRenderer();
    this->InitColorRenderer();
    this->LoadTextures();
}

void Game::ProcessInput(float dt)
{
    // float velocity = PLAYER_VELOCITY * dt;
    // move playerboard
    if (this->State == GAME_MENU)
    {
        if (this->Keys[GLFW_KEY_SPACE] && !this->KeysProcessed[GLFW_KEY_SPACE])
        {
            this->StartGame();
            this->KeysProcessed[GLFW_KEY_SPACE] = true;
        }
    }
    else if (this->State == GAME_ACTIVE)
    {
        if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_D])
        {
            Player->Turn(dt, *this);
        }
        if (this->Keys[GLFW_KEY_SPACE] && !this->KeysProcessed[GLFW_KEY_SPACE])
        {
            this->Fire();
            this->KeysProcessed[GLFW_KEY_SPACE] = true;
        }
    }
}

void Game::Fire()
{
    glm::vec2 projectilePos;
    if (Player->Shoot(projectilePos))
    {
         Projectiles.push_back(new ProjectileObject(projectilePos, PROJECTILE_SIZE, PROJECTILE_VELOCITY));
    }
}

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        if (Chunks.size() == 1)
            this->GenerateChunks();
        for (ChunkObject* chunk : Chunks)
        {
            chunk->Move(dt);
        }
        for (ProjectileObject* projectile : Projectiles)
        {
            // projectile->Move(dt);
            projectile->Move(dt, Player->Position.x);
        }
        this->DoCollisions();
    }
}

void Game::DoCollisions()
{
    for (ChunkObject* chunk : Chunks)
    {
        if (chunk->_offset + Height * 2 < 0)
            break;
        // std::cout << chunk->_offset << std::endl;
        // chunk->DoCollisions(Projectiles);
        for (BorderObject* border : chunk->Borders)
        {
            for (ProjectileObject* projectile : Projectiles)
            {
                if (CollisionManager::DoCollisions(border, projectile, false, false))
                {
                    projectile->IsDestroyed = true;
                    continue;
                }
            }
            if (!Player->IsDestroyed)
            {
                if (CollisionManager::DoCollisions(border, Player, false, true))
                {
                    Player->IsDestroyed = true;
                    this->EndGame();
                    return;
                }
            }
        }
        for (EnemyObject* enemy : chunk->Enemies)
        {
            for (ProjectileObject* projectile : Projectiles)
            {
                if (CollisionManager::DoCollisions(enemy, projectile, true, false))
                {
                    projectile->IsDestroyed = true;
                    enemy->IsDestroyed = true;
                    continue;
                }
            }
            if (Player != nullptr)
            {
                if (CollisionManager::DoCollisions(enemy, Player, true, true))
                {
                    Player->IsDestroyed = true;
                    // enemy->IsDestroyed = true;
                    this->EndGame();
                    
                    return;
                }
            }
        }
    }
    std::cout << std::endl << std::endl;
}

void Game::Render()
{ 
    if (this->State == GAME_ACTIVE)
    {
        Player->Draw(*spriteRenderer);
        for (ProjectileObject* projectile : Projectiles)
        {
            projectile->Draw(*colorRenderer);
        }
        for (ChunkObject* chunk : Chunks)
        {
            //chunk->Draw(*spriteRenderer, *colorRenderer);
            chunk->Draw(*spriteRenderer);
            chunk->Draw(*colorRenderer);
        }
    }
}

void Game::Dispose()
{
    for (auto it = Projectiles.begin(); it != Projectiles.end(); ) {
        if ((*it)->IsDestroyed) {
            delete* it;
            it = Projectiles.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = Chunks.begin(); it != Chunks.end(); ) {
        // (*it)->Dispose();
        if ((*it)->Dispose()) {
            delete* it;
            it = Chunks.erase(it);
        }
        else {
            ++it;
        }   
    }
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    //Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
    // also disable all active powerups
    //Effects->Chaos = Effects->Confuse = false;
    //Ball->PassThrough = Ball->Sticky = false;
    Player->Color = glm::vec3(1.0f);
    //Ball->Color = glm::vec3(1.0f);
}
