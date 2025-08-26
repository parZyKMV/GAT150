#pragma once
#include "RendererComponent.h"
#include "Core/Serializable.h"

namespace viper
{
	class SpriteRenderer : public RendererComponent{
	public:
		std::string textureId; // ID of the texture to render
	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};

}
