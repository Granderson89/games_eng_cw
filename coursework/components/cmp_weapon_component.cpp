#include "cmp_weapon_component.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
using namespace std;
using namespace sf;

void WeaponComponent::update(double dt) {
	_cooldown -= dt;
	if (_cooldown <= 0.f) {
		fire();
		_cooldown = 1.0f;
	}
}

void WeaponComponent::fire() const {
	auto bullet = _parent->scene->makeEntity();
	bullet->setPosition(_parent->getPosition() + _offset);
	//bullet->addComponent<HurtComponent>();
	bullet->addComponent<BulletComponent>();
	auto s = bullet->addComponent<ShapeComponent>();

	s->setShape<sf::CircleShape>(8.f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(4.f, 4.f);
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f));
	p->setRestitution(.4f);
	p->setFriction(.005f);
	p->impulse(Vector2f(15.0f, 0.0f));
}


WeaponComponent::WeaponComponent(Entity* p, Vector2f offset)
	: Component(p), _cooldown(2.f), _offset(offset) {}
