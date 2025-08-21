#include "Player.h"
#include "Rocket.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "GameData.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Componets/SpriteRenderer.h"
#include "Componets/CircleCollider2D.h"
#include "Componets/RigidBody.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Audio/AudioClip.h"
#include "Resources/Resources.h"
#include "Resources/ResourcesManager.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{
    viper::Particle particle;
    particle.position = owner->transform.position;
    particle.velocity = viper::vec2{ viper::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
    particle.color = viper::vec3{ 1, 1, 1 };
    particle.lifespan = 2;
    //viper::GetEngine().GetPS().AddParticle(particle);

    // rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    owner->transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation)) * thrust * speed;
    //velocity += force * dt;
    auto* rb = owner->GetComponet<viper::RigidBody>();
    if (rb) {
        rb->velocity = force;
    }

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    // check fire key pressed
    /*fireTimer -= dt;
	isFiring = false;
    if (fireEnergy > 5.0f) {
        if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
            fireTimer = fireTime;
			isFiring = true;

            //viper::GetEngine().GetAudio().PlaySound("laser_effect");
            auto sound = viper::Resourcess().Get<viper::AudioClip>("laser_effect.wav", viper::GetEngine().GetAudio()).get();
            if (sound) {
                viper::GetEngine().GetAudio().PlaySound(*sound);
            }

            // spawn rocket at player position and rotation
            viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
            auto rocket = std::make_unique<Rocket>(transform);// , viper::Resourcess().Get<viper::Texture>("Textures/projectile03-5.png", viper::GetEngine().GetRenderer()));
            rocket->speed = 1500.0f;
            rocket->lifespan = 1.5f;
            rocket->name = "rocket";
            rocket->tag = "player";

            // Add sprite renderer component to the rocket
            auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
            spriteRenderer->textureId = "Textures/projectile03-5.png";
            rocket->AddComponents(std::move(spriteRenderer));

            auto rb = std::make_unique<viper::RigidBody>();
            rocket->AddComponents(std::move(rb));

            auto collider = std::make_unique<viper::CircleCollider2D>();
            collider->radius = 10;
            rocket->AddComponents(std::move(collider));

            scene->AddActor(std::move(rocket));
			fireEnergy -= 5.0f;
            if (fireEnergy < 0) fireEnergy = 0;
        }
    }else{
		canFire = true;
    }

    if (!isFiring && fireEnergy < maxFireEnergy) {
        fireEnergy += fireRechargeRate * dt;
        if (fireEnergy > maxFireEnergy) {
            fireEnergy = maxFireEnergy;
       }
    }
    std::cout << "Fire Energy: " << fireEnergy << std::endl;*/
    Actor::Update(dt);
}

void Player::OnCollision(viper::Actor* other)
{
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        viper::GetEngine().GetAudio().PlaySound("explosion");
        dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
    }
}

