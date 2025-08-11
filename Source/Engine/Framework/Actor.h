#pragma once
#include "Object.h"
#include "Math/Transform.h"
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
		Actor(const Transform& transform, viper::res_t<viper::Texture> texture) :
			transform{ transform },
			m_texture{ texture }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

	protected:
		//std::shared_ptr<Model> m_model;
		res_t<Texture> m_texture;
	};
}