#include "cmp_missile_logic.h"
#include "cmp_player_physics.h"
#include "cmp_physics.h"
#include "cmp_ai_steering.h"
#include "cmp_player_state.h"


using namespace std;
using namespace sf;

// Full strength of projectile
float MissileComponent::strength = 30.0f;
// Speed of projectile
float MissileComponent::speed = 100.0f;

// Update - count lifespan and reduce strength of projectile
void MissileComponent::update(double dt) {
	auto enemy = _target->GetCompatibleComponent<PlayerPhysicsComponent>().at(0);
	if (_parent->GetCompatibleComponent<PhysicsComponent>().at(0)->isTouching(*enemy)) {
		explode();
		auto enemyState = _target->GetCompatibleComponent<PlayerStateComponent>().at(0);
		enemyState->takeDamage(strength);
	}
}

void MissileComponent::render() {

}

void MissileComponent::explode() {
	_parent->setForDelete();
}

float MissileComponent::getSpeed() {
	return speed;
}

MissileComponent::MissileComponent(Entity* p, shared_ptr<Entity> target) 
	: Component(p), _target(target) {
	// Attach a physics component
	shared_ptr<PhysicsComponent> physics;
	if (target == player1) {
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(2.0f, 2.0f), P2_PROJECTILE_BIT, P1_BIT);
	}
	else {
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(2.0f, 2.0f), P1_PROJECTILE_BIT, P2_BIT);
	}
	physics->setRestitution(0.4f);
	physics->setFriction(0.005f);
	physics->setMass(0.001f);
}