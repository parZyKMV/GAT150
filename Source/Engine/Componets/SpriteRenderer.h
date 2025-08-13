#pragma once
#include "RendererComponent.h"

namespace viper
{
	class SpriteRenderer : public Component
	{
	public:
		std::string textureId; // ID of the texture to render
	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer);
	};

}
