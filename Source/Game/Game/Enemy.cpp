#include "Enemy.h"
#include "Engine.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourcesManager.h"
#include "Componets/SpriteRenderer.h"
#include "Componets/RigidBody.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;

    Player* player = scene->GetActorByName<Player>("player");
    if (player) {
        viper::vec2 direction{ 0, 0 };
        direction = player->transform.position - transform.position;

        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation));

        float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = viper::vec2::SignedAngleBetween(forward, direction);
            angle = viper::math::sign(angle);
            transform.rotation += viper::math::radToDeg(angle * 5 * dt);
        }
    }

    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
    //velocity += force * dt;
	//GetComponet<viper::RigidBody>()->velocity += force * dt;

	auto* rb = GetComponet<viper::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

    transform.position.x = viper::math::wrap(transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    transform.position.y = viper::math::wrap(transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        // spawn rocket at player position and rotation
        viper::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform);// , viper::Resourcess().Get<viper::Texture>("Textures/projectile03-5.png", viper::GetEngine().GetRenderer()));
        rocket->speed = 500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "enemy";
        
		// Add sprite renderer component to the rocket
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureId = "Textures/projectile03-5.png";
		rocket->AddComponents(std::move(spriteRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rocket->AddComponents(std::move(rb));

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (tag != other->tag) {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = transform.position;
            particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            if (i < 50) {
                particle.color = viper::vec3{ 1.0f, 0.5f, 0.0f };
            }
            else {
                particle.color = viper::vec3{ 1.0f, 1.0f, 0.0f };
            }
            particle.lifespan = 2;

            viper::GetEngine().GetAudio().PlaySound("explosion");
            viper::GetEngine().GetPS().AddParticle(particle);
        }
    }
}
