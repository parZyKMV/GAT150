#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/Resources.h"
#include "Resources/ResourcesManager.h"

namespace viper {

	bool Engine::Initialize() {
		m_renderer = std::make_unique<viper::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Viper Engine", 1280, 1024);

		m_input = std::make_unique<viper::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<viper::AudioSystem>();
		m_audio->Initialize();

		m_particleSystem = std::make_unique<viper::ParticleSystem>();
		m_particleSystem->Initialize(5000);

		m_physics = std::make_unique<Physics>();
		m_physics->Initialize();

		return true;
	}

	void Engine::Shutdown() {
		//release resources from resources manager
		Resourcess().Clear();

		//shutdown engine systems
		m_particleSystem->Shutdown();
		m_audio->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
		m_physics->Shutdown();
	}

	void Engine::Update() {
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
		m_physics->Update(m_time.GetDeltaTime());
	}

	void Engine::Draw()
	{
		//
	}



}