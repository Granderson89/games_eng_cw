#pragma once
#include "cmp_physics.h"
#include "ecm.h"

using namespace sf;

enum type {
	CANNONS = 0,
	TORPEDOS = 1,
	MISSILES = 2
};

class WeaponComponent : public Component {
protected:
	static int next_weapon;
	static float firetime;
	static float base_cooldown;
	static type type;

	float _cooldown;
	Vector2f _offset;
	void fire() const;
	int _weapon_num;


public:
	WeaponComponent() = delete;
	explicit WeaponComponent(Entity* p, Vector2f offset, const int weapon_num);
	
	static void switchWeapon();

	void update(double dt) override;
	void render() override {};
};