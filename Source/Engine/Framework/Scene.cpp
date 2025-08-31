#include "Scene.h"
#include "Actor.h"
#include "Core/StringHelper.h"
#include "Renderer/Renderer.h"
#include "Componets/ColliderComponent.h"
#include "Core/Factory.h"

namespace viper {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		// update all actors
		for (auto& actor : m_actors) {
			if (actor->isActive) {
				actor->Update(dt);
			}
		}

		// remove destroyed actors
		for (auto iter = m_actors.begin(); iter != m_actors.end(); ) {
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		// check for collisions
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponet<ColliderComponent>();
				auto colliderB = actorB->GetComponet<ColliderComponent>();

				//make sure both actors have colliders
				if (!colliderA || !colliderB) continue;

				if(colliderA->CheckCollision(*colliderB)) {
					// Collision detected, call OnCollision for both actors
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}

	}

	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->isActive) {
				actor->Draw(renderer);
			}
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start){
		actor->scene = this;
		if(start) actor->Start();
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force)
	{
		for (auto iter = m_actors.begin(); iter != m_actors.end(); ) {
			if (!(*iter)->persistent || force) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	bool Scene::Load(const std::string& sceneName) {
		viper::json::document_t document;
		if (!viper::json::Load(sceneName, document)) {
			Logger::Error("Could not load scene {}", sceneName);
			return false;
		}
		//create scene
		Read(document);

		//start actors
		for (auto& actor : m_actors) {
			actor->Start();
		}
		return true;
	}

	void Scene::Read(const json::value_t& value){
		//read prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {

				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		//read actors
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}
}