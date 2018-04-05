#include "cmp_defensive_turret.h"
#include "cmp_turret_projectile.h"
#include "cmp_sprite.h"
#include "../game.h"

using namespace std;
using namespace sf;


// Keeps track of which weapon to fire next
int TurretComponent::p1_next_weapon = 0;
// Stops all weapons firing at once when fire button is pushed
float TurretComponent::p1_firetime = 0.0f;
// Base cooldown of weapons
float TurretComponent::p1_base_cooldown = 0.1f;

// Keeps track of which weapon to fire next
int TurretComponent::p2_next_weapon = 1;
// Stops all weapons firing at once when fire button is pushed
float TurretComponent::p2_firetime = 0.0f;
// Base cooldown of weapons
float TurretComponent::p2_base_cooldown = 0.1f;

void TurretComponent::update(double dt) {
	// Countdown timers
	p1_firetime -= dt;
	p2_firetime -= dt;
	_cooldown -= dt;
	// If fire button is pushed, this weapon is next,
	// weapon has cooled down and firetime delay has run down
	// fire, reset timers and increment next_weapon
	if (im.Player[0].fireTurret) {
		if (p1_next_weapon == _weapon_num)
			if (_cooldown <= 0.0f)
				if (p1_firetime <= 0.0f) {
					im.Player[0].fire = false;
					fire(1);
					_cooldown = p1_base_cooldown;
					p1_firetime = 0.1f;
				}
	}

	if (im.Player[1].fireTurret) {
		if (p2_next_weapon == _weapon_num &&
			_cooldown <= 0.0f && p2_firetime <= 0.0f) {
			im.Player[1].fire = false;
			fire(0);
			_cooldown = p2_base_cooldown;
			p2_firetime = 0.1f;
		}
	}
}

void TurretComponent::fire(int target) const {
	auto projectile = _parent->scene->makeEntity();
	projectile->setPosition(_parent->getPosition());
	auto s = projectile->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(4.0f);
	s->getShape().setFillColor(Color::Green);
	s->getShape().setOrigin(2.0f, 2.0f);
	if (target == 0) {
		auto l = projectile->addComponent<TurretProjComponent>(player1, _parent->getRotation());
	}
	if (target == 1) {
		auto l = projectile->addComponent<TurretProjComponent>(player2, _parent->getRotation());
	}
}

TurretComponent::TurretComponent(Entity* p, const int weapon_num)
	: Component(p), _cooldown(0.1f), _weapon_num(weapon_num) {}