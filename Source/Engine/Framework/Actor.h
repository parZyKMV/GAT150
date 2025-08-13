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
		
		template<typename T>
		T* GetComponet();

		template<typename T>
		std::vector<T*> GetComponets();

	protected:
		//std::shared_ptr<Model> m_model;
		std::vector<std::shared_ptr<Component>> m_components;
	};
	template<typename T>
	inline T* Actor::GetComponet(){

		for (auto& componet : m_components) {
			auto result = dynamic_cast<T*>(componet.get());
			if (result) return result;
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Actor::GetComponets() {
		std::vector<T*> results;
		for (auto& componet : m_components) {
			auto result = dynamic_cast<T*>(componet.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}