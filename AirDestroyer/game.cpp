#include "chunk_object.h"
#include "collision_manager.h"
#include "game.h"
#include "player_object.h"
#include "projectile_object.h"
#include "utilities/color_renderer.h"
#include "utilities/resource_manager.h"
#include "utilities/sprite_renderer.h"
#include "utilities/text_renderer.h"


//Instantiate static variables
float Game::firstFrame;

// Game-related State data
std::unique_ptr<SpriteRenderer> m_pSpriteRenderer;
std::unique_ptr<ColorRenderer> m_pColorRenderer;
std::unique_ptr<TextRenderer> m_pTextRenderer;
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
    : State(GAME_MENU), Keys(), KeysProcessed(), Width(width), Height(height), m_score(0)
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
    Chunks.push_back(ChunkObject(Width, Height, n));
}

void Game::CreatePlayer()
{
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    // Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"), glm::vec3(1.0f), PLAYER_VELOCITY);
    Player = std::make_unique<PlayerObject>(playerPos, PLAYER_SIZE, PLAYER_VELOCITY, glm::vec3(1.0f), ResourceManager::GetTexture("player"));
    m_score = 0;
}

void Game::DestroyAll()
{
    // Player->IsDestroyed = true;
    for (auto& chunk : this->Chunks)
    {
        chunk.IsDestroyed = true;
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
    this->State = GAME_END;
}

void Game::LoadTextures()
{
    ResourceManager::LoadTexture("resources/textures/plane.png", true, "player");
    ResourceManager::LoadTexture("resources/textures/plane_right.png", true, "player_right");
    ResourceManager::LoadTexture("resources/textures/plane_left.png", true, "player_left");
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
    m_pSpriteRenderer = std::make_unique<SpriteRenderer>(shader);
}

void Game::InitColorRenderer()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::LoadShader("shaders/color.vert", "shaders/color.frag", nullptr, "color");
    ResourceManager::GetShader("color").Use();
    ResourceManager::GetShader("color").SetMatrix4("projection", projection);
    Shader colorShader = ResourceManager::GetShader("color");
    m_pColorRenderer = std::make_unique<ColorRenderer>(colorShader);
}

void Game::InitTextRenderer()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 0.0f, static_cast<float>(this->Height), -1.0f, 1.0f);
    ResourceManager::LoadShader("shaders/text.vert", "shaders/text.frag", nullptr, "text");
    ResourceManager::GetShader("text").Use();
    ResourceManager::GetShader("text").SetMatrix4("projection", projection);
    Shader textShader = ResourceManager::GetShader("text");
    m_pTextRenderer = std::make_unique<TextRenderer>(textShader);
}

void Game::LoadFreeType()
{

}


void Game::Init()
{
    this->InitSpriteRenderer();
    this->InitColorRenderer();
    this->InitTextRenderer();
    this->LoadTextures();
    this->LoadFreeType();
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_MENU || this->State == GAME_END)
    {
        if (this->Keys[GLFW_KEY_SPACE] && !this->KeysProcessed[GLFW_KEY_SPACE])
        {
            if (this->State == GAME_MENU)
                this->StartGame();
            else
                this->State = GAME_MENU;
            this->KeysProcessed[GLFW_KEY_SPACE] = true;
        }
    }
    else if (this->State == GAME_ACTIVE)
    {
        Player->Move(dt, *this);

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
         Projectiles.push_back(ProjectileObject(projectilePos, PROJECTILE_SIZE, PROJECTILE_VELOCITY));
    }
}

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        if (Player)
            Player->Update(dt);
        if (Chunks.size() == 1)
            this->GenerateChunks();
        for (auto& chunk : Chunks)
        {
            chunk.Move(dt, Player->Velocity.y);
        }
        for (auto& projectile : Projectiles)
        {
            projectile.Move(dt, Player->Position.x);
        }
        this->DoCollisions();
    }
}

void Game::DoCollisions()
{
    for (auto& chunk : Chunks)
    {
        if (chunk._offset + Height * 2 < 0)
            break;
        for (auto& border : chunk.Borders)
        {
            for (auto& projectile : Projectiles)
            {
                if (CollisionManager::DoCollisions(&border, &projectile, false, false))
                {
                    projectile.IsDestroyed = true;
                    continue;
                }
            }
            if (!Player->IsDestroyed)
            {
                if (CollisionManager::DoCollisions(&border, Player.get(), false, true))
                {
                    Player->IsDestroyed = true;
                    this->EndGame();
                    return;
                }
            }
        }
        for (auto& enemy : chunk.Enemies)
        {
            for (auto& projectile : Projectiles)
            {
                if (CollisionManager::DoCollisions(&enemy, &projectile, true, false))
                {
                    AddScore(ENEMY_SCORE);
                    projectile.IsDestroyed = true;
                    enemy.IsDestroyed = true; 
                    continue;
                }
            }
            if (Player != nullptr)
            {
                if (CollisionManager::DoCollisions(&enemy, Player.get(), true, true))
                {
                    Player->IsDestroyed = true;
                    enemy.IsDestroyed = true;
                    this->EndGame();
                    
                    return;
                }
            }
        }
    }
}

void Game::Render()
{ 
    if (this->State == GAME_ACTIVE)
    {
        Player->Draw(m_pSpriteRenderer);
        for (auto& projectile : Projectiles)
        {
            projectile.Draw(m_pColorRenderer);
        }
        for (auto& chunk : Chunks)
        {
            //chunk->Draw(*spriteRenderer, *colorRenderer);
            chunk.Draw(m_pSpriteRenderer);
            chunk.Draw(m_pColorRenderer);
        }
        // std::string strScore = std::to_string(m_score);
        m_pTextRenderer->DrawText(std::to_string(m_score), glm::vec2(50.0f, 50.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    else if (this->State == GAME_MENU)
    {
        m_pTextRenderer->DrawText("PRESS SPACE", glm::vec2(this->Width / 3.2f, this->Height / 2.1f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    else if (this->State == GAME_END)
    {
        m_pTextRenderer->DrawText("GAME OVER", glm::vec2(this->Width / 3.2f + 50.0f, this->Height / 2.1f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        m_pTextRenderer->DrawText(std::to_string(m_score), glm::vec2(this->Width / 2.0f, this->Height / 3.2f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
}

void Game::Dispose()
{
    for (auto it = Projectiles.begin(); it != Projectiles.end(); ) {
        if (it->IsDestroyed) {
            it = Projectiles.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = Chunks.begin(); it != Chunks.end(); ) {
        if (it->Dispose()) {
            it = Chunks.erase(it);
        }
        else {
            ++it;
        }   
    }
}

void Game::AddScore(const int scoreToAdd)
{
    m_score += scoreToAdd;
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    Player->Velocity.y = PLAYER_VELOCITY_Y_BASE;
    //Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
    // also disable all active powerups
    //Effects->Chaos = Effects->Confuse = false;
    //Ball->PassThrough = Ball->Sticky = false;
    Player->Color = glm::vec3(1.0f);
    //Ball->Color = glm::vec3(1.0f);
}
