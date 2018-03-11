#pragma once
#include "cmp_physics.h"
#include "ecm.h"

using namespace sf;


class WeaponComponent : public Component {
protected:
	float _cooldown;
	int _type;
	Vector2f _offset;
	void fire() const;

public:
	WeaponComponent() = delete;
	explicit WeaponComponent(Entity* p, Vector2f offset);

	void update(double dt) override;
	void render() override {};
};