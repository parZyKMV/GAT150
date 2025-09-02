#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourcesManager.h"
#include "Componets/SpriteRenderer.h"
#include "Componets/RigidBody.h"
#include "Componets/CircleCollider2D.h"
#include "Renderer/Animator.h"
#include "Renderer/TextureAnimation.h"
#include "Core/Factory.h"
#include "Core/Json.h"
#include "Input/InputSystem.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

#include <vector>


bool SpaceGame::Initialize()
{
    m_scene = std::make_unique<viper::Scene>(this);
    m_scene->Load("scene.json");

    m_titleText = std::make_unique<viper::Text>(viper::Resourcess().GetWIthId<viper::Font>("title_font", "arcadeclassic.ttf", 48));
    m_scoreText = std::make_unique<viper::Text>(viper::Resourcess().GetWIthId<viper::Font>("ui_font", "arcadeclassic.ttf", 48));
    m_livesText = std::make_unique<viper::Text>(viper::Resourcess().GetWIthId<viper::Font>("ui_font","arcadeclassic.ttf", 48));

    auto bat = std::make_unique<viper::Actor>();
    bat->name = "bat";
    bat->tag = "enemy";
    bat->transform.position = { 740, 500 };
    bat->transform.scale = 3;

    // SpriteRenderer
    auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
    bat->AddComponents(std::move(spriteRenderer));

    // Animator
    auto animator = std::make_unique<viper::Animator>();
    bat->AddComponents(std::move(animator));

    // O si tienes que cargar animación manual, no inventes json aquí,
    // mejor usa un archivo json de prototipo o llama animator->Read()
    // con el value_t real cargado desde archivo.

    m_scene->AddActor(std::move(bat), true); // usa AddActor, no Add

        
    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        //viper::GetEngine().GetAudio().PlaySound("menu");
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;

        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        viper::GetEngine().GetAudio().PlaySound("start-level");
        m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {
        m_scene->RemoveAllActors();
        viper::GetEngine().GetAudio().PlaySound("battle");

		auto player = viper::Factory::Instance().Create<viper::Actor>("player");
		m_scene->AddActor(std::move(player));

        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 2;
            SpawnEnemy();
        }

        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
                m_stateTimer = 3;
            }
            else {
                m_gameState = GameState::StartRound;
            }
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        viper::GetEngine().GetAudio().PlaySound("gameover");
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        viper::GetEngine().GetTime().SetTimeScale(0.15f);
    }
    else {
        viper::GetEngine().GetTime().SetTimeScale(1.0f);
    }

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {
	m_scene->Draw(renderer);


    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
        m_titleText->Create(renderer, "REMASTERED", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 430);
    }
    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }

    m_scoreText->Create(renderer, "SCORE  " + std::to_string(m_score), { 1, 1, 1 });
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES  " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, (float)(renderer.GetWidth() - 200), (float)20);

	//show player energy
    Player* player = m_scene->GetActorByName<Player>("player");
    if (player) {
        float energy = player->GetFireEnergy();  
        std::string energyText = "ENERGY " + std::to_string(static_cast<int>(energy));

        
        m_scoreText->Create(renderer, energyText, { 0, 1, 1 });  
        m_scoreText->Draw(renderer, 20, 70); 
    }


    viper::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {
    viper::Actor* player = m_scene->GetActorByName<viper::Actor>("player");
    if (player) {
        viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 2.0f };
        auto enemy = viper::Instantiate("enemy", viper::vec2{ 20,20 }, 45, 5);
        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::Shutdown() {
    //
}
