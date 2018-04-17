#pragma once
#include "cmp_physics.h"
#include "ecm.h"
#include <SFML/Audio.hpp>

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

	// Weapon sounds
	static sf::SoundBuffer plasmaBuffer;
	static sf::SoundBuffer torpedoBuffer;
	static sf::SoundBuffer missileBuffer;
	static sf::Sound plasmaSound;
	static sf::Sound torpedoSound;
	static sf::Sound missileSound;

	void fire(int target) const;

	Entity* _target;
	float _cooldown;
	Vector2f _offset;
	int _weapon_num;
	type _type;


public:
	WeaponComponent() = delete;
	explicit WeaponComponent(Entity* p, Entity* target, Vector2f offset, const int weapon_num, type weapon_type);
	
	static void changeP1Weapon();
	static void changeP2Weapon();
	static string getP1ActiveType();
	static string getP2ActiveType();
	static void loadSounds();

	float getCooldown();
	string getType();

	void update(const double &dt) override;
	void render() override {};
};