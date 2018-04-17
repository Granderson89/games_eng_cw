#pragma once
#include "ecm.h"
#include <random>

using namespace sf;

class TurretComponent : public Component {
private:
	mutable std::default_random_engine ran;
protected:
	// Player 1
	static int p1_next_weapon;
	static float p1_firetime;
	static float p1_base_cooldown;
	static float p1_turret_rotation;

	// Player 2
	static int p2_next_weapon;
	static float p2_firetime;
	static float p2_base_cooldown;
	static float p2_turret_rotation;
	
	void fire(int target) const;

	float _cooldown;
	int _weapon_num;

public:
	TurretComponent() = delete;
	explicit TurretComponent(Entity* p, const int weapon_num);

	void update(double dt) override;
	void render() override {};
};