#include "cmp_plasma_logic.h"
#include "cmp_player_physics.h"
#include "../game.h"

#include <Box2D/Dynamics/Contacts/b2Contact.h>


using namespace std;
using namespace sf;

// Lifespan of projectile
float PlasmaComponent::max_lifespan = 3.0f;
// Full strength of projectile
float PlasmaComponent::max_strength = 100.0f;
// Speed of projectile
float PlasmaComponent::speed = 10.0f;

// Update - count lifespan and reduce strength of projectile
void PlasmaComponent::update(double dt) {
	_current_lifespan += dt;
	reduceStrength();
	if (_current_lifespan >= max_lifespan) {
		_parent->setForDelete();
	}
	auto enemy = _target->GetCompatibleComponent<PlayerPhysicsComponent>().at(0);
	if (_parent->GetCompatibleComponent<PhysicsComponent>().at(0)->isTouching(*enemy)) {
		_parent->setForDelete();
	}
}

void PlasmaComponent::render() {
	
}

void PlasmaComponent::reduceStrength() {
	// Calculate plasma dissipation
	float dissipate = _current_lifespan / max_lifespan * max_strength;
	// Reduce current strength
	_current_strength = max_strength - dissipate;
	if (_current_strength < 0.0f) {
		_current_strength = 0.0f;
	}
}

PlasmaComponent::PlasmaComponent(Entity* p, shared_ptr<Entity> target, float ship_rotation)
	: Component(p), _target(target), _current_lifespan(0.0f) {
	// Attach a physics component and apply impulse
	shared_ptr<PhysicsComponent> physics;
	if (target == player1) {
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(8.0f, 8.0f), P2_PROJECTILE_BIT, P1_BIT);
	}
	else {
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(8.0f, 8.0f), P1_PROJECTILE_BIT, P2_BIT);
	}
	physics->setRestitution(0.4f);
	physics->setFriction(0.005f);
	ship_rotation = deg2rad(ship_rotation);
	Vector2f direction = Vector2f(-sinf(ship_rotation), cosf(ship_rotation));
	std::cout << "Direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
	direction = normalize(direction);
	physics->impulse(direction * speed);
}
