#include "Texture.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include "../Engine.h"
#include "../Math/Vector2.h"
#include "../Renderer/Renderer.h"

namespace viper {
    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (m_texture != nullptr) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load image onto surface

        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    viper::vec2 Texture::getSize()
    {
        if(!m_texture)
        {
            std::cerr << "Texture not loaded, cannot get size." << std::endl;
            return viper::vec2{ 0, 0 };
		}

		float w, h;
        SDL_GetTextureSize(m_texture, &w, &h);
        return viper::vec2{ w, h };
    }
}