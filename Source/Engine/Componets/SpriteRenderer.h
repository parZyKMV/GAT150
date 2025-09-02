#pragma once
#include "RendererComponent.h"
#include "Core/Serializable.h"
#include "Renderer/Texture.h"


namespace viper
{
	class SpriteRenderer : public RendererComponent{
	public:
		std::string textureId; // ID of the texture to render
		res_t<Texture> texture;
		rect textureRect;

	public:
		CLASS_PROTOTYPE(SpriteRenderer)

		void Start() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};

}
