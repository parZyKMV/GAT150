#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Component.h"
#include "Renderer/Texture.h"
#include <string>
#include <memory>

namespace viper {
	class Actor : public Object{
	public:
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };

		bool destroyed{ false };
		float lifespan{ 0 };


		Transform transform;
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();
		
		// Add a component to the actor

		void AddComponents(std::unique_ptr<Component> componets);

	protected:
		//std::shared_ptr<Model> m_model;
		std::vector<std::shared_ptr<Component>> m_components;
	};
}