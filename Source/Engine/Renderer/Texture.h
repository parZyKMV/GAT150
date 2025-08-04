#pragma once
#include <string>
#include "../Math/Vector2.h"
#include <vector>

namespace viper {
	class Texture {
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		viper::vec2 getSize();

		friend class Renderer;

	private:
		struct SDL_Texture* m_texture{ nullptr };
	};
}