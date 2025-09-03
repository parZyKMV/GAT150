#include "TilemapRenderer.h"
#include "Resources/ResourcesManager.h"
#include "Tilemap.h"
#include "Core/Factory.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(TilemapRenderer)

	TilemapRenderer::TilemapRenderer(const TilemapRenderer& other) {
	}

	void TilemapRenderer::Start() {
		// Load the tilemap resource
		m_tilemap = Resourcess().Get<Tilemap>(m_tilemapName, GetEngine().GetRenderer());
		if (!m_tilemap) {
			Logger::Error("Could not load tilemap: {}", m_tilemapName);
			return;
		}
		
		// create physics bodies
		Transform transform;
		transform.scale = owner->transform.scale;
		transform.rotation = owner->transform.rotation;

		//PhysicsBody::PhysicsBodyDef bodyDef;

		// iterate through layers
		for (auto layer : m_tilemap->GetLayers()) {

			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = m_tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->transform.position + (m_tilemap->GetPosition(layer, i) * owner->transform.scale);

				transform.position = position;
				vec2 size = vec2{ source.w, source.h };
			}
		}
	}

	void TilemapRenderer::Update(float dt) {
		//
	}

	void TilemapRenderer::Draw(Renderer& renderer) {
		// iterate through layers
		for (auto layer : m_tilemap->GetLayers()) {
			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source;
				vec2 position;

				renderer.DrawTexture(*layer.texture, source, position.x, position.y, owner->transform.rotation, owner->transform.scale);
			}
		}
	}

	void TilemapRenderer::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ_NAME(value, "tilemap_name", m_tilemapName);
	}
}