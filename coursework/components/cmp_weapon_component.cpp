#include "cmp_weapon_component.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include "../game.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

// Keeps track of which weapon to fire next
int WeaponComponent::next_weapon = 0;
// Stops all weapons firing at once when fire button is pushed
float WeaponComponent::firetime = 0.0f;
// Weapon type
type WeaponComponent::active_type = CANNONS;
// Base cooldown of weapons
float WeaponComponent::base_cooldown = 1.0f;

void WeaponComponent::update(double dt) {
	// Countdown timers
	firetime -= dt;
	_cooldown -= dt;
	// If fire button is pushed, this weapon is next,
	// weapon has cooled down and firetime delay has run down
	// fire, reset timers and increment next_weapon
	if (im.Player[0].fire &&
		_type == active_type && 
		next_weapon == _weapon_num &&
		_cooldown <= 0.0f && firetime <= 0.0f) {
		im.Player[0].fire = false;
		fire();
		_cooldown = base_cooldown;
		firetime = 0.7f;
		next_weapon++;
		switch (_type) {
		case CANNONS:
			if (next_weapon > 7)
				next_weapon = 0;
			break;
		case TORPEDOS:
			if (next_weapon > 5)
				next_weapon = 1;
			break;
		case MISSILES:
			if (next_weapon > 4)
				next_weapon = 3;
			break;
		default:
			if (next_weapon > 7)
				next_weapon = 0;
			break;
		}
	}
	if (im.Player[0].changeWeapon) {
		im.Player[0].changeWeapon = false;
		changeWeapon();
	}
}

void WeaponComponent::fire() const {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition(_parent->getPosition() + rotate(Vector2f(_offset), _parent->getRotation()));
	//bullet->addComponent<HurtComponent>();
	bullet->addComponent<BulletComponent>();
	auto s = bullet->addComponent<ShapeComponent>();

	if (_type == CANNONS) {
		s->setShape<sf::CircleShape>(8.0f);
		s->getShape().setFillColor(Color::Red);
		s->getShape().setOrigin(4.0f, 4.0f);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.0f, 8.0f));
		p->setRestitution(0.4f);
		p->setFriction(0.005f);
		p->impulse(Vector2f(0.0f, 15.0f));
	}
	if (_type == TORPEDOS) {
		s->setShape<sf::CircleShape>(4.0f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(2.0f, 2.0f);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(4.0f, 4.0f));
		p->setRestitution(0.4f);
		p->setFriction(0.005f);
		p->impulse(Vector2f(0.0f, 15.0f));
	}
	if (_type == MISSILES) {
		s->setShape<sf::CircleShape>(2.0f);
		s->getShape().setFillColor(Color::Cyan);
		s->getShape().setOrigin(1.0f, 1.0f);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(2.0f, 2.0f));
		p->setRestitution(0.4f);
		p->setFriction(0.005f);
		p->impulse(Vector2f(0.0f, 15.0f));
	}
}

void WeaponComponent::changeWeapon() {
	switch (active_type) {
	case CANNONS:
		active_type = TORPEDOS;
		base_cooldown = 2.0f;
		next_weapon = 1;
		break;
	case TORPEDOS:
		active_type = MISSILES;
		base_cooldown = 3.0f;
		next_weapon = 3;
		break;
	case MISSILES:
		active_type = CANNONS;
		base_cooldown = 1.0f;
		next_weapon = 0;
		break;
	default:
		active_type = CANNONS;
		base_cooldown = 1.0f;
		next_weapon = 0;
		break;
	}
}

WeaponComponent::WeaponComponent(Entity* p, Vector2f offset, const int weapon_num, type weapon_type)
	: Component(p), _cooldown(1.0f), _offset(offset), _weapon_num(weapon_num), _type(weapon_type) {}
