#include "cmp_torpedo_logic.h"
#include "cmp_physics.h"
#include "cmp_player_physics.h"

using namespace std;
using namespace sf;

// Lifespan of projectile
float TorpedoComponent::max_lifespan = 5.0f;
// Full strength of projectile
float TorpedoComponent::strength = 200.0f;
// Speed of projectile
float TorpedoComponent::speed = 7.0f;
// Range of explosion
float TorpedoComponent::damage_range = 5.0f;

// Update - count lifespan
void TorpedoComponent::update(double dt) {
	_current_lifespan -= dt;
	if (_current_lifespan <= 0.0f) {
		explode();
	}

	auto enemy = _target->GetCompatibleComponent<PlayerPhysicsComponent>().at(0);
	if (_parent->GetCompatibleComponent<PhysicsComponent>().at(0)->isTouching(*enemy)) {
		explode();
	}
	
}

void TorpedoComponent::render() {

}

void TorpedoComponent::explode() {
	_parent->setForDelete();
}

TorpedoComponent::TorpedoComponent(Entity* p, shared_ptr<Entity> target, float ship_rotation)
	: Component(p), _target(target), _current_lifespan(max_lifespan) {
	// Attach a physics component and apply impulse
	auto physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(4.0f, 4.0f));
	physics->setRestitution(0.4f);
	physics->setFriction(0.005f);
	ship_rotation = deg2rad(ship_rotation);
	Vector2f direction = Vector2f(-sinf(ship_rotation), cosf(ship_rotation));
	direction = normalize(direction);
	physics->impulse(direction * speed);
}
