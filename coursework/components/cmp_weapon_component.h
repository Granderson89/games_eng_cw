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
	// Player 1
	static int p1_next_weapon;
	static float p1_firetime;
	static float p1_base_cooldown;
	static type p1_active_type;

	// Player 2
	static int p2_next_weapon;
	static float p2_firetime;
	static float p2_base_cooldown;
	static type p2_active_type;

	void fire(int target) const;

	float _cooldown;
	Vector2f _offset;
	int _weapon_num;
	type _type;


public:
	WeaponComponent() = delete;
	explicit WeaponComponent(Entity* p, Vector2f offset, const int weapon_num, type weapon_type);
	
	static void changeP1Weapon();
	static void changeP2Weapon();


	void update(double dt) override;
	void render() override {};
};