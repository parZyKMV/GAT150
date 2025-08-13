#include "RigidBody.h"

namespace viper {
	void RigidBody::Update(float dt)
	{
		if (owner->destroyed) return;
		if (damping > 0) {
			velocity *= (1.0f / (1.0f + damping * dt));
		}
		owner->transform.position += velocity * dt;
	}
}
