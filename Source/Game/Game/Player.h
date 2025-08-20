#pragma once
#include "Framework/Component.h"


class Player : public viper::Component {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;
	float fireEnergy = 100.0f;
	bool canFire = false;
	bool isFiring;
	const float maxFireEnergy = 100.0f;     
	const float fireRechargeRate = 2.5f;   

public:
	Player() = default;
	/*Player(const viper::Transform& transform) :
		Actor{ transform }
	{}*/
	float GetFireEnergy() const { return fireEnergy; }


	void Update(float dt) override;

	void OnCollision(class Actor* other);
};
