#pragma once
#include "Resources/Resources.h"
#include <fmod.hpp>
#include <string>
#include <map>

namespace viper {
	class AudioClip : public Resources {
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& audioSystem);

	private:
		friend class AudioSystem;
		FMOD::Sound* m_sound{nullptr};
	};
}
