#include "cmp_missile_logic.h"
#include "cmp_physics.h"

using namespace std;
using namespace sf;

// Full strength of projectile
float MissileComponent::strength = 300.0f;
// Speed of projectile
float MissileComponent::speed = 100.0f;

// Update - count lifespan and reduce strength of projectile
void MissileComponent::update(double dt) {
	// Seek target
	SteeringOutput steering = seek();
	_parent->GetCompatibleComponent<PhysicsComponent>().at(0)->setVelocity(steering.direction * speed);
}

void MissileComponent::render() {

}

// Seek the target
SteeringOutput MissileComponent::seek() {
	SteeringOutput steering;
	Vector2f target_pos = _target->getPosition();
	Vector2f pos = _parent->getPosition();

	steering.direction = target_pos - pos;
	steering.direction = normalize(steering.direction);

	steering.direction.y *= -1.0f;

	return steering;
}

void MissileComponent::explode() {
	
}

MissileComponent::MissileComponent(Entity* p, shared_ptr<Entity> target) : Component(p), _target(target) {}