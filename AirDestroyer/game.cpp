#include "game.h"
#include "projectile_object.h"
#include "player_object.h"
#include "utilities/resource_manager.h"
#include "utilities/sprite_renderer.h"
#include "utilities/color_renderer.h"


//Instantiate static variables
float Game::firstFrame;

// Game-related State data
SpriteRenderer* Renderer;
ColorRenderer* colorRenderer;
//ProjectileObject* Projectile;
std::vector<ProjectileObject*> Projectiles;
PlayerObject* Player;

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

Game::Game(unsigned int width, unsigned int height) : Keys(), KeysProcessed(), Width(width), Height(height)
{
	
}

Game::~Game()
{
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("shaders/color.vert", "shaders/color.frag", nullptr, "color");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::LoadTexture("resources/textures/airplane.png", true, "player");

    ResourceManager::GetShader("color").SetMatrix4("projection", projection);

    Shader shader = ResourceManager::GetShader("sprite");

    ResourceManager::GetShader("color").Use();
    ResourceManager::GetShader("color").SetMatrix4("projection", projection);
    Shader colorShader = ResourceManager::GetShader("color");

    Renderer = new SpriteRenderer(shader);
    colorRenderer = new ColorRenderer(colorShader, 1.0f, 0.0f, 0.0f);

    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y);
    Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"), glm::vec3(1.0f), PLAYER_VELOCITY);
    // glm::vec2 projectilePos = glm::vec2(this->Width / 2.0f - PROJECTILE_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - PLAYER_OFFSET_Y - PROJECTILE_SIZE.y);
    // Projectile = new ProjectileObject(projectilePos, PROJECTILE_SIZE);
    // this->ResetPlayer();
}

void Game::ProcessInput(float dt)
{
    // float velocity = PLAYER_VELOCITY * dt;
    // move playerboard
    if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_D])
    {
        Player->Move(dt, this);
    }
    if (this->Keys[GLFW_KEY_SPACE] && !this->KeysProcessed[GLFW_KEY_SPACE])
    {
        this->Fire();
        this->KeysProcessed[GLFW_KEY_SPACE] = true;
    }
}

void Game::Fire()
{
    glm::vec2 projectilePos;
    if (Player->Shoot(this, &projectilePos))
    {
         Projectiles.push_back(new ProjectileObject(projectilePos, PROJECTILE_SIZE));
    }
}

void Game::Update(float dt)
{
    for (ProjectileObject* projectile : Projectiles)
    {
        projectile->Move(dt);
    }
}

void Game::Render()
{
    // draw player
    Player->Draw(*Renderer);
    //if (Projectile != NULL)
    //    Projectile->Draw(*colorRenderer);
    for (ProjectileObject* projectile : Projectiles)
    {
        projectile->Draw(*colorRenderer);
    }
}

void Game::Dispose()
{
    for (auto it = Projectiles.begin(); it != Projectiles.end(); ) {
        if ((*it)->isDisposable) {
            delete* it;
            it = Projectiles.erase(it);
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
