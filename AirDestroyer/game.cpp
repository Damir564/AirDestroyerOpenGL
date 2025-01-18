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
#ifdef DEBUG
    std::cout << "Chunks generated" << std::endl;
#endif
    for (int i = 0; i != CHUNKS_AMOUNT_BUFFER; ++i)
    {
        CreateChunk(i);
    }
}

void Game::CreateChunk(int n)
{
    m_vecChunks.push_back(ChunkObject(Width, Height, n));
}

void Game::CreatePlayer()
{
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    // Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"), glm::vec3(1.0f), PLAYER_VELOCITY);
    m_pPlayer = std::make_unique<PlayerObject>(playerPos, PLAYER_SIZE, PLAYER_VELOCITY, glm::vec3(1.0f), ResourceManager::GetTexture("player"));
    m_score = 0;
}

void Game::DestroyAll()
{
    // Player->IsDestroyed = true;
    for (auto& chunk : this->m_vecChunks)
    {
        chunk.IsDestroyed = true;
    }
}

void Game::StartGame()
{
    //m_pMusicBuffer->Stop();
    ResourceManager::Musics["game_end"]->Stop();
    if (!ResourceManager::Musics["space"]->isPlaying())
        ResourceManager::Musics["space"]->Play();
    this->GenerateChunks();
    this->CreatePlayer();
    this->State = GAME_ACTIVE;
}

void Game::EndGame()
{
    DestroyAll();
    //m_pMusicBuffer->Play();
    // ResourceManager::Musics["space"]->Stop();
    ResourceManager::Musics["game_end"]->Play();
    this->State = GAME_END;
}

void Game::LoadTextures()
{
    ResourceManager::LoadTexture("resources/textures/plane.png", true, "player");
    ResourceManager::LoadTexture("resources/textures/plane_right.png", true, "player_right");
    ResourceManager::LoadTexture("resources/textures/plane_left.png", true, "player_left");
    //return;
    ResourceManager::LoadTexture("resources/textures/ship.png", true, "ship");
    ResourceManager::LoadTexture("resources/textures/ship.png", true, "ship");
    for (int i = 0; i != EXPLOSION_SPRITES.size(); ++i)
    ResourceManager::LoadTexture(std::string("resources/textures/" 
        + EXPLOSION_SPRITES[i]
        + ".png").c_str(), true, EXPLOSION_SPRITES[i]);
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

void Game::InitSounds()
{
    // SoundDevice::Get();
    // m_pSoundDevice = std::make_unique<SoundDevice>(SoundDevice::Get());
    // m_pSoundEffectsPlayer = std::make_unique<SoundEffectsPlayer>();
    // m_pSoundEffectsPlayer = std::make_unique<SoundEffectsPlayer>();
    // m_pMusicBuffer = std::make_unique<MusicBuffer>("resources/sounds/music_game_end.mp3");
    m_pSoundEffectsPlayer = std::make_unique<SoundEffectsPlayer>();
    ResourceManager::InitSounds();
}

void Game::LoadSounds()
{
    // ALuint soundFire = SoundEffectsLibrary::Get()->Load("resources/sounds/effect_fire.mp3");
    ResourceManager::LoadSound("resources/sounds/effect_fire.mp3", "fire");
    ResourceManager::LoadSound("resources/sounds/effect_hit.mp3", "hit");
    ResourceManager::LoadMusic("resources/sounds/music_game_end.mp3", "game_end", false);
    ResourceManager::LoadMusic("resources/sounds/music_space.mp3", "space", true);
    // ResourceManager::LoadSound("resources/sounds/music_game_end.mp3", "game_end");
    //ALuint soundFire2 = SoundEffectsLibrary::Get()->Load("resources/sounds/effect_fire.mp3");
    
}


void Game::Init()
{
    this->InitSpriteRenderer();
    this->InitColorRenderer();
    this->InitTextRenderer();
    this->LoadTextures();
    this->LoadFreeType();
    this->InitSounds();
    this->LoadSounds();
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
        m_pPlayer->Move(dt, *this);

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
    if (m_pPlayer->Shoot(projectilePos))
    {
         m_vecProjectiles.push_back(ProjectileObject(projectilePos, PROJECTILE_SIZE, PROJECTILE_VELOCITY));
    }
}

void Game::Update(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        if (m_pPlayer)
            m_pPlayer->Update(dt);
        if (m_vecChunks.size() == 1)
            this->GenerateChunks();
        for (auto& chunk : m_vecChunks)
        {
            chunk.Update(dt, m_pPlayer->Velocity.y);
        }
        for (auto& projectile : m_vecProjectiles)
        {
            projectile.Update(dt, m_pPlayer->Position.x);
        }
        this->DoCollisions();       
    }

    //Play Music
    if (this->State == GAME_END)
    {
        ALint musicState;
        alGetSourcei(ResourceManager::Musics["game_end"]->getSource(), AL_SOURCE_STATE, &musicState);
        if (musicState == AL_PLAYING && alGetError() == AL_NO_ERROR)
        {
            ResourceManager::Musics["game_end"]->UpdateBufferStream();
        }
    }
    ALint musicState;
    alGetSourcei(ResourceManager::Musics["space"]->getSource(), AL_SOURCE_STATE, &musicState);
    if (musicState == AL_PLAYING && alGetError() == AL_NO_ERROR)
    {
        ResourceManager::Musics["space"]->UpdateBufferStream();
    }
}

void Game::DoCollisions()
{
    for (auto& chunk : m_vecChunks)
    {
        if (chunk._offset + Height * 2 < 0)
            break;
        for (auto& border : chunk.Borders)
        {
            for (auto& projectile : m_vecProjectiles)
            {
                if (CollisionManager::DoCollisions(&border, &projectile, false, false))
                {
                    projectile.IsDestroyed = true;
                    continue;
                }
            }
            if (!m_pPlayer->IsDestroyed)
            {
                if (CollisionManager::DoCollisions(&border, m_pPlayer.get(), false, true))
                {
                    m_pPlayer->IsDestroyed = true;
                    this->EndGame();
                    return;
                }
            }
        }
        for (auto& enemy : chunk.Enemies)
        {
            for (auto& projectile : m_vecProjectiles)
            {
                if (CollisionManager::DoCollisions(&enemy, &projectile, true, false))
                {
                    AddScore(ENEMY_SCORE);
                    CreateEffect(chunk, enemy.Position);
                    projectile.IsDestroyed = true;
                    enemy.IsDestroyed = true; 
                    continue;
                }
            }
            if (m_pPlayer != nullptr)
            {
                if (CollisionManager::DoCollisions(&enemy, m_pPlayer.get(), true, true))
                {
                    m_pPlayer->IsDestroyed = true;
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
        for (auto& projectile : m_vecProjectiles)
        {
            projectile.Draw(m_pColorRenderer);
        }
        for (auto& chunk : m_vecChunks)
        {
            //chunk->Draw(*spriteRenderer, *colorRenderer);
            chunk.Draw(m_pSpriteRenderer);
            chunk.Draw(m_pColorRenderer);
        }
        m_pPlayer->Draw(m_pSpriteRenderer);
        // std::string strScore = std::to_string(m_score);
        m_pTextRenderer->DrawText(std::to_string(m_score), glm::vec2(50.0f, 50.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), PIVOT::LEFT);
        m_pTextRenderer->DrawText(std::to_string(m_pPlayer->GetDistance()), glm::vec2(Width - 50.0f, 50.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), PIVOT::RIGHT);
    }
    else if (this->State == GAME_MENU)
    {
        m_pTextRenderer->DrawText("AIR DESTROYER", glm::vec2(this->Width / 2.0f, this->Height / 2.0f + 70.0f), 1.1f, glm::vec3(0.0f, 0.0f, 0.0f), PIVOT::MID);
        m_pTextRenderer->DrawText("AIR DESTROYER", glm::vec2(this->Width / 2.0f, this->Height / 2.0f + 90.0f), 1.2f, glm::vec3(1.0f, 0.0f, 0.0f), PIVOT::MID);
        m_pTextRenderer->DrawText("PRESS SPACE", glm::vec2(this->Width / 2.0f, this->Height / 2.0f - 100.0f), 0.9f, glm::vec3(1.0f, 1.0f, 1.0f), PIVOT::MID);
    }
    else if (this->State == GAME_END)
    {
        m_pTextRenderer->DrawText("GAME OVER", glm::vec2(this->Width / 2.0f, this->Height / 2.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), PIVOT::MID);
        m_pTextRenderer->DrawText(std::to_string(m_score), glm::vec2(this->Width / 2.0f, this->Height / 3.2f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), PIVOT::MID);
    }
}

void Game::Dispose()
{
    for (auto it = m_vecProjectiles.begin(); it != m_vecProjectiles.end(); ) {
        if (it->IsDestroyed) {
            it = m_vecProjectiles.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = m_vecChunks.begin(); it != m_vecChunks.end(); ) {
        if (it->Dispose()) {
            it = m_vecChunks.erase(it);
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

void Game::CreateEffect(ChunkObject& chunk, const glm::vec2 pos)
{
    chunk.CreateEffect(pos);
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    m_pPlayer->Size = PLAYER_SIZE;
    m_pPlayer->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    m_pPlayer->Velocity.y = PLAYER_VELOCITY_Y_BASE;
    //Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
    // also disable all active powerups
    //Effects->Chaos = Effects->Confuse = false;
    //Ball->PassThrough = Ball->Sticky = false;
    m_pPlayer->Color = glm::vec3(1.0f);
    //Ball->Color = glm::vec3(1.0f);
}

void Game::PlaySound(ALuint buffer)
{
    m_pSoundEffectsPlayer->Play(buffer);
}
