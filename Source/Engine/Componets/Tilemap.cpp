#include "Tilemap.h"
#include "Core/Logger.h"
#include "Core/Json.h"
#include "Core/StringHelper.h"

namespace viper {
	bool Tilemap::Load(const std::string& filename, class Renderer& renderer) {
		// load json
		viper::json::document_t document;
		if (!viper::json::Load(filename, document)) {
			Logger::Error("Could not load Tilemap json {}", filename);
			return false;
		}

		// read tilemap data

		// read tilemap layers
		if (JSON_HAS(document, layers)) {
			for (auto& layerValue : JSON_GET(document, layers).GetArray()) {
				Layer layer;

				// load texture from properties
				if (JSON_HAS(layerValue, properties)) {
					for (auto& propertyValue : JSON_GET(layerValue, properties).GetArray()) {

						std::string name;
						JSON_READ(propertyValue, name);

						// check if property name is TextureName
						if (equalsIgnoreCase(name, "TextureName")) {
							// read texture name value (texture name)
						}
					}
				}

				m_layers.push_back(layer);
			}
		}

		return true;
	}

	rect Tilemap::GetTextureRect(const Layer& layer, int tileId) {
		if (tileId == 0) return {}; // empty tile

		// calculate tiles per row from texture size
		vec2 textureSize = layer.texture->getSize();
		int tilesPerRow = 0;

		int column = (tileId - 1) % tilesPerRow; // Tiled uses 1-based indexing
		int row = (tileId - 1) / tilesPerRow;

		return rect{};
	}

	vec2 Tilemap::GetPosition(const Layer& layer, int tileIndex) {
		return vec2{};
	}
}