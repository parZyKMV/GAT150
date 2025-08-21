#include "Enemy.h"
#include "Engine.h"
#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Actor.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourcesManager.h"
#include "Componets/CircleCollider2D.h"
#include "Componets/SpriteRenderer.h"
#include "Componets/RigidBody.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/Factory.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
 //   bool playerSeen = false;

 //   Actor* player = owner->scene->GetActorByName<Actor>("player");
 //   if (player) {
 //       viper::vec2 direction{ 0, 0 };
 //       direction = player->transform.position - owner->transform.position;

 //       direction = direction.Normalized();
 //       viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));

 //       float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
 //       playerSeen = angle <= 30;

 //       if (playerSeen) {
 //           float angle = viper::vec2::SignedAngleBetween(forward, direction);
 //           angle = viper::math::sign(angle);
 //           owner->transform.rotation += viper::math::radToDeg(angle * 5 * dt);
 //       }
 //   }

 //   viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
 //   //velocity += force * dt;
	////GetComponet<viper::RigidBody>()->velocity += force * dt;

	//auto* rb = owner->GetComponet<viper::RigidBody>();
 //   if (rb) {
 //       rb->velocity += force * dt;
 //   }

 //   owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
 //   owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

 //   // check fire
 //   fireTimer -= dt;
 //   if (fireTimer <= 0 && playerSeen) {
 //       fireTimer = fireTime;

 //       // spawn rocket at player position and rotation
 //       viper::Transform transform{owner->transform.position,owner->transform.rotation, 2.0f };
 //       auto rocket = std::make_unique<Actor>(transform);// , viper::Resourcess().Get<viper::Texture>("Textures/projectile03-5.png", viper::GetEngine().GetRenderer()));
 //       rocket->speed = 500.0f;
 //       rocket->owner->lifespan = 1.5f;
 //       rocket->name = "rocket";
 //       rocket->owner->tag = "enemy";
 //       
	//	// Add sprite renderer component to the rocket
 //       auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
 //       spriteRenderer->textureId = "Textures/projectile03-5.png";
	//	rocket->owner->AddComponents(std::move(spriteRenderer));

 //       auto collider = std::make_unique<viper::CircleCollider2D>();
 //       collider->radius = 10;
 //       rocket->owner->AddComponents(std::move(collider));

 //       auto rb = std::make_unique<viper::RigidBody>();
 //       rocket->owner->AddComponents(std::move(rb));

 //       owner->scene->AddActor(std::move(rocket));
 //   }

 //   Actor::Update(dt);
}

void Enemy::OnCollision(viper::Actor* other)
{
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        owner->scene->GetGame()->AddPoints(100);
        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = owner->transform.position;
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
