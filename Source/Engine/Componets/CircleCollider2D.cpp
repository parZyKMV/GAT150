#include "CircleCollider2D.h"
#include "Framework/Actor.h"
#include "Core/Factory.h"


namespace viper {
	FACTORY_REGISTER(CircleCollider2D)
	void  CircleCollider2D::Update(float dt)
	{
		// CircleCollider specific update logic can be added here
	}

	bool CircleCollider2D::CheckCollision(ColliderComponent& other){
		float distance = (owner->transform.position - other.owner->transform.position).Length();

		//check circle to circle collision
		auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
		if (circleCollider) {
			float radii = radius + circleCollider->radius;
			if (distance <= radii) return true; // Collision detected
		}
		return false;
	}
}