#pragma once
#include "ColliderComponent.h"


namespace viper {
	class CircleCollider2D :public ColliderComponent {
		// Inherited via ColliderComponent
	public:
		float radius{ 0 };
	public:
		void Update(float dt) override;
		bool CheckCollision(ColliderComponent& other) override;

		void Read(const json::value_t& value) override;
	};
}
