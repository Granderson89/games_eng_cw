#include "cmp_turret_projectile.h"
#include "cmp_physics.h"
#include "cmp_ai_steering.h"
#include "../game.h"

#include <Box2D/Dynamics/Contacts/b2Contact.h>

using namespace std;
using namespace sf;

// Lifespan of projectile
float TurretProjComponent::max_lifespan = 3.0f;
// Full strength of projectile
float TurretProjComponent::strength = 10.0f;
// Speed of projectile
float TurretProjComponent::speed = 10.0f;

// Update - count lifespan and reduce strength of projectile
void TurretProjComponent::update(double dt) {
	_current_lifespan -= dt;
	if (_current_lifespan <= 0.0f) {
		_parent->setForDelete();
	}

	// Get list of enemy projectiles
	_enemy_projectiles.clear();
	if (_target == player1) {
		_enemy_projectiles = _parent->scene->ents.find("p1_projectiles");
	}
	else {
		_enemy_projectiles = _parent->scene->ents.find("p2_projectiles");
	}
	// Test for collisions
	for (int i = 0; i < _enemy_projectiles.size(); i++) {
		auto enemyProj = _enemy_projectiles.at(i);
		if (_parent->GetCompatibleComponent<PhysicsComponent>().at(0)->isTouching(*enemyProj->GetCompatibleComponent<PhysicsComponent>().at(0))) {
			// Delete both if true
			_parent->setForDelete();
			enemyProj->setForDelete();
		}
	}
}

void TurretProjComponent::render() {

}

TurretProjComponent::TurretProjComponent(Entity* p, shared_ptr<Entity> target, float ship_rotation)
	: Component(p), _target(target), _current_lifespan(max_lifespan) {
	// Attach a physics component and apply impulse
	vector<unsigned int> mask;
	shared_ptr<PhysicsComponent> physics;
	if (target == player1) {
		mask.push_back(P1_PROJECTILE_BIT);
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(0.5f, 0.5f), P2_TURRET_PROJ_BIT, mask);
	}
	else {
		mask.push_back(P2_PROJECTILE_BIT);
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(0.5f, 0.5f), P1_TURRET_PROJ_BIT, mask);
	}
	physics->setRestitution(0.4f);
	physics->setFriction(0.005f);
	ship_rotation = deg2rad(ship_rotation);
	Vector2f direction = Vector2f(-sinf(ship_rotation), cosf(ship_rotation));
	direction = normalize(direction);
	physics->impulse(direction * speed);
}
