#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Core/Logger.h"
#include "Core/File.h"
#include "Resources/ResourcesManager.h"
#include "Engine.h"


#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>
#include <Renderer/Texture.h>

int main(int argc, char* argv[]) {
	viper::Logger::SetEnabledLevels(viper::LogLevel::Error);

    viper::file::SetCurrentDirectory("Assets");
    
    // initialize engine
    viper::GetEngine().Initialize();

    // initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    // initialize sounds
    viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");
	viper::GetEngine().GetAudio().AddSound("laser_effect.wav", "laser_effect");
	viper::GetEngine().GetAudio().AddSound("explosion.wav", "explosion");
	viper::GetEngine().GetAudio().AddSound("menu.wav", "menu");
	viper::GetEngine().GetAudio().AddSound("battle.wav", "battle");
	viper::GetEngine().GetAudio().AddSound("start-level.wav", "start-level");
	viper::GetEngine().GetAudio().AddSound("gameover.wav", "gameover");


	

    // create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280 , viper::random::getReal() * 1024 });
    }

    SDL_Event e;
    bool quit = false;

	/*std::shared_ptr<viper::Texture> texture = std::make_shared<viper::Texture>();
	texture->Load("Idle_player1_2.png", viper::GetEngine().GetRenderer());*/

	float rotate = 0.0f;
    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // draw
        viper::vec3 color{ 0, 0, 0 };
        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		rotate += 0.1f * viper::GetEngine().GetTime().GetDeltaTime();

        game->Draw(viper::GetEngine().GetRenderer());

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();

    return 0;
}


    
