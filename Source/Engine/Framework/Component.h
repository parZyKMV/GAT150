#pragma once
#include "Object.h"

namespace viper {
	class Component : public Object {
	public:
		class Actor* owner{ nullptr }; // Pointer to the actor that owns this component
	public:
		Component() = default;
		virtual void Update(float dt) = 0;

	};
}
