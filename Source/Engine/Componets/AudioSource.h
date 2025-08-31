#pragma once
#include "Framework/Actor.h"

namespace viper {
	class AudioSource : public Component {
	public:
		std::string audioClipName;
	public:
		CLASS_PROTOTYPE(AudioSource)

		void Update(float dt) override;
		void Play();
	};
}
