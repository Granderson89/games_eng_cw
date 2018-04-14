#include "cmp_weapon_component.h"
#include "cmp_plasma_logic.h"
#include "cmp_torpedo_logic.h"
#include "cmp_missile_logic.h"
#include "cmp_ai_steering.h"
#include "engine.h"
#include "../game.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

// Keeps track of which weapon to fire next
int WeaponComponent::p1_next_weapon = 0;
// Stops all weapons firing at once when fire button is pushed
float WeaponComponent::p1_firetime = 0.0f;
// Weapon type
type WeaponComponent::p1_active_type = CANNONS;
// Base cooldown of weapons
float WeaponComponent::p1_base_cooldown = 1.0f;

// Keeps track of which weapon to fire next
int WeaponComponent::p2_next_weapon = 15;
// Stops all weapons firing at once when fire button is pushed
float WeaponComponent::p2_firetime = 0.0f;
// Weapon type
type WeaponComponent::p2_active_type = CANNONS;
// Base cooldown of weapons
float WeaponComponent::p2_base_cooldown = 1.0f;

float p1_change_timer = 0.0f;
float p2_change_timer = 0.0f;

void WeaponComponent::update(double dt) {
	// Countdown timers
	p1_firetime -= dt / 15.0;
	p2_firetime -= dt / 15.0;
	_cooldown -= dt;
	p1_change_timer -= dt / 15.0;
	p2_change_timer -= dt / 15.0;
	if (_cooldown <= 0.0f) {
		_cooldown = 0.0f;
	}
	// If fire button is pushed, this weapon is next,
	// weapon has cooled down and firetime delay has run down
	// fire, reset timers and increment next_weapon
	if (InputManager::Player[0].fire) {
		if (_type == p1_active_type) {
			if (p1_next_weapon == _weapon_num) {
				if (_cooldown <= 0.0f) {
					if (p1_firetime <= 0.0f) {
						InputManager::Player[0].fire = false;
						fire(1);
						_cooldown = p1_base_cooldown;
						p1_firetime = 0.7f;
						p1_next_weapon++;
						switch (_type) {
						case CANNONS:
							if (p1_next_weapon > 7)
								p1_next_weapon = 0;
							break;
						case TORPEDOS:
							if (p1_next_weapon < 8 || p1_next_weapon > 12)
								p1_next_weapon = 8;
							break;
						case MISSILES:
							if (p1_next_weapon < 13 || p1_next_weapon > 14)
								p1_next_weapon = 13;
							break;
						default:
							if (p1_next_weapon > 7)
								p1_next_weapon = 0;
							break;
						}
					}
				}
			}
		}
	}
	if (InputManager::Player[0].changeWeapon) {
		if (InputManager::playerInput[0].source >= 0) {
			if (p1_change_timer < 0.0f) {
				InputManager::Player[0].changeWeapon = false;
				p1_change_timer = 0.5f;
				changeP1Weapon();
			}
		}
		else {
			InputManager::Player[0].changeWeapon = false;
			changeP1Weapon();
		}
	}

	if (InputManager::Player[1].fire) {
		if (_type == p2_active_type &&
			p2_next_weapon == _weapon_num &&
			_cooldown <= 0.0f && p2_firetime <= 0.0f) {
			InputManager::Player[1].fire = false;
			fire(0);
			_cooldown = p2_base_cooldown;
			p2_firetime = 0.7f;
			p2_next_weapon++;
			switch (_type) {
			case CANNONS:
				if (p2_next_weapon > 22)
					p2_next_weapon = 15;
				break;
			case TORPEDOS:
				if (p2_next_weapon < 23 || p2_next_weapon > 27)
					p2_next_weapon = 23;
				break;
			case MISSILES:
				if (p2_next_weapon < 28 || p2_next_weapon > 29)
					p2_next_weapon = 28;
				break;
			default:
				if (p2_next_weapon > 22)
					p2_next_weapon = 15;
				break;
			}
		}
	}

	if (InputManager::Player[1].changeWeapon) {
		if (InputManager::playerInput[1].source >= 0) {
			if (p2_change_timer < 0.0f) {
				InputManager::Player[1].changeWeapon = false;
				p2_change_timer = 0.5f;
				changeP2Weapon();
			}
		}
		else {
			InputManager::Player[1].changeWeapon = false;
			changeP2Weapon();
		}
	}
}

void WeaponComponent::fire(int target) const {
	// Get rotation of ship and the port and starboard
	// vectors
	float ship_rotation = _parent->getRotation();
	Vector2f starboard = Vector2f(1.0f, 0.0f);
	starboard = rotate(starboard, ship_rotation);
	Vector2f port = Vector2f(-1.0f, 0.0f);
	port = rotate(port, ship_rotation);
	// Get the vector to the enemy and normalize
	Vector2f enemy = _target->getPosition() - _parent->getPosition();
	enemy = normalize(enemy);
	// Get the dot product
	Vector2f multiply = starboard * enemy;
	float dot = multiply.x + multiply.y;
	// If dot < 0, place mounts on the port side
	Vector2f position;
	Vector2f direction;
	if (dot < 0.0f) {
		position.x = _offset.x * -1.0f;
		position.y = _offset.y;
		direction = port;
	}
	// If dot >= 0, place mounts on the starboard side
	else {
		position.x = _offset.x;
		position.y = _offset.y;
		direction = starboard;
	}
	// Create a projectile and set it's position relative to ship
	auto projectile = _parent->scene->makeEntity();
	projectile->setPosition(_parent->getPosition() + rotate(Vector2f(position), _parent->getRotation()));
	auto s = projectile->addComponent<ShapeComponent>();
	if (_type == CANNONS) {
		s->setShape<sf::CircleShape>(8.0f);
		s->getShape().setFillColor(Color::Red);
		s->getShape().setOrigin(4.0f, 4.0f);
		if (target == 0) {
			auto l = projectile->addComponent<PlasmaComponent>(_target, direction);
			projectile->addTag("p2_projectiles");
		}
		if (target == 1) {
			auto l = projectile->addComponent<PlasmaComponent>(_target, direction);
			projectile->addTag("p1_projectiles");
		}
	}
	if (_type == TORPEDOS) {
		s->setShape<sf::CircleShape>(4.0f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(2.0f, 2.0f);
		if (target == 0) {
			auto l = projectile->addComponent<TorpedoComponent>(player1, direction);
			projectile->addTag("p2_projectiles");
		}
		if (target == 1) {
			auto l = projectile->addComponent<TorpedoComponent>(player2, direction);
			projectile->addTag("p1_projectiles");
		}
	}
	if (_type == MISSILES) {
		s->setShape<sf::CircleShape>(2.0f);
		s->getShape().setFillColor(Color::Cyan);
		s->getShape().setOrigin(1.0f, 1.0f);
		if (target == 0) {
			auto m = projectile->addComponent<MissileComponent>(player1);
			// Attach a steering component
			projectile->addComponent<SteeringComponent>(player1.get(), m->getSpeed());
			projectile->addTag("p2_projectiles");
		}
		if (target == 1) {
			auto m = projectile->addComponent<MissileComponent>(player2);
			// Attach a steering component
			projectile->addComponent<SteeringComponent>(player2.get(), m->getSpeed());
			projectile->addTag("p1_projectiles");
		}
	}
}

void WeaponComponent::changeP1Weapon() {
	switch (p1_active_type) {
	case CANNONS:
		p1_active_type = TORPEDOS;
		p1_base_cooldown = 2.0f;
		p1_next_weapon = 8;
		break;
	case TORPEDOS:
		p1_active_type = MISSILES;
		p1_base_cooldown = 3.0f;
		p1_next_weapon = 13;
		break;
	case MISSILES:
		p1_active_type = CANNONS;
		p1_base_cooldown = 1.0f;
		p1_next_weapon = 0;
		break;
	default:
		p1_active_type = CANNONS;
		p1_base_cooldown = 1.0f;
		p1_next_weapon = 0;
		break;
	}
}

void WeaponComponent::changeP2Weapon() {
	switch (p2_active_type) {
	case CANNONS:
		p2_active_type = TORPEDOS;
		p2_base_cooldown = 2.0f;
		p2_next_weapon = 23;
		break;
	case TORPEDOS:
		p2_active_type = MISSILES;
		p2_base_cooldown = 3.0f;
		p2_next_weapon = 28;
		break;
	case MISSILES:
		p2_active_type = CANNONS;
		p2_base_cooldown = 1.0f;
		p2_next_weapon = 15;
		break;
	default:
		p2_active_type = CANNONS;
		p2_base_cooldown = 1.0f;
		p2_next_weapon = 15;
		break;
	}
}
string WeaponComponent::getP1ActiveType() {
	switch (p1_active_type) {
	case CANNONS:
		return "CANNONS";
		break;
	case TORPEDOS:
		return "TORPEDOS";
		break;
	case MISSILES:
		return "MISSILES";
		break;
	default:
		return "CANNONS";
		break;
	}
}
string WeaponComponent::getP2ActiveType()
{
	switch (p2_active_type) {
	case CANNONS:
		return "CANNONS";
		break;
	case TORPEDOS:
		return "TORPEDOS";
		break;
	case MISSILES:
		return "MISSILES";
		break;
	default:
		return "CANNONS";
		break;
	}
}
float WeaponComponent::getCooldown()
{
	return _cooldown;
}
string WeaponComponent::getType()
{
	switch (_type) {
	case CANNONS:
		return "CANNONS";
		break;
	case TORPEDOS:
		return "TORPEDOS";
		break;
	case MISSILES:
		return "MISSILES";
		break;
	default:
		return "CANNONS";
		break;
	}
}
WeaponComponent::WeaponComponent(Entity* p, Entity* target, Vector2f offset, const int weapon_num, type weapon_type)
	: Component(p), _target(target), _cooldown(1.0f), _offset(offset), _weapon_num(weapon_num), _type(weapon_type) {}
