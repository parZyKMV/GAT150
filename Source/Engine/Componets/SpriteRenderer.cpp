#include "RendererComponent.h"
#include "Resources/ResourcesManager.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace viper {
	void SpriteRenderer::Update(float dt){
		// Update logic for the sprite renderer can be added here if needed
	}

	void SpriteRenderer::Draw(Renderer& renderer){
		renderer.DrawTexture(Resourcess().Get<Texture>(textureId, renderer).get(), owner->transform.position.x, owner->transform.position.y);
	}
}