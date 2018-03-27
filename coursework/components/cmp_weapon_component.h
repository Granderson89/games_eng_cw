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
	static type active_type;

	void fire() const;

	float _cooldown;
	Vector2f _offset;
	int _weapon_num;
	type _type;


public:
	WeaponComponent() = delete;
	explicit WeaponComponent(Entity* p, Vector2f offset, const int weapon_num, type weapon_type);
	
	static void changeWeapon();

	void update(double dt) override;
	void render() override {};
};