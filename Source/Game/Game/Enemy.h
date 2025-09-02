#pragma once
#include "Framework/Component.h"
#include "Componets/RigidBody.h"


class Enemy : public viper::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;
	float rotationRate = 90;

	viper::RigidBody* m_rigidBody{nullptr};

public:
	Enemy() = default;

	CLASS_PROTOTYPE(Enemy)

	void Start() override;
	void Update(float dt) override;
	void OnCollision(class viper::Actor* other);

	void Read(const viper::json::value_t& value) override;
};
