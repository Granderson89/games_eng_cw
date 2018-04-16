#define _USE_MATH_DEFINES

#include "cmp_ai_steering.h"
#include "cmp_physics.h"
#include <math.h>

using namespace sf;
using namespace std;

void SteeringComponent::update(double dt) {
	auto output = _seek.getSteering();
	output.direction.y *= -1.0f;
	_parent->GetCompatibleComponent<PhysicsComponent>().at(0)->setVelocity(output.direction);
	_parent->setRotation(output.rotation * 180.0f / M_PI);

}

SteeringComponent::SteeringComponent(Entity* p, Entity* target, float speed)
	: _target(target), _seek(Seek(p, target, speed)), Component(p) {}

void SteeringComponent::move(const sf::Vector2f &p) {
	auto new_pos = _parent->getPosition() + p;
	_parent->setPosition(new_pos);
}

void SteeringComponent::move(float x, float y) {
	move(Vector2f(x, y));
}