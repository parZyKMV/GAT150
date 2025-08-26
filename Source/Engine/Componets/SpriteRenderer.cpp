#include "RendererComponent.h"
#include "Resources/ResourcesManager.h"
#include "Core/Factory.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace viper {
	FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::Update(float dt){
		// Update logic for the sprite renderer can be added here if needed
	}

	void SpriteRenderer::Draw(Renderer& renderer){
		auto texture = Resourcess().Get<Texture>(textureId, renderer).get();
		if (texture) {
			renderer.DrawTexture(*texture,
				owner->transform.position.x,
				owner->transform.position.y, 
				owner->transform.rotation, 
				owner->transform.scale);
		}
	}

	void SpriteRenderer::Read(const json::value_t& value){
		Object::Read(value);

		JSON_READ_NAME(value,"texturId", textureId);
	}
}