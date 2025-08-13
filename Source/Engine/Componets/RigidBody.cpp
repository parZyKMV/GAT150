#include "RigidBody.h"
#include "Framework/Actor.h"

namespace viper {
	void RigidBody::Update(float dt){
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));

	}
}
