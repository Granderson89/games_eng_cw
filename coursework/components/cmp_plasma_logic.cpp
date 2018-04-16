#include "cmp_plasma_logic.h"
#include "cmp_player_physics.h"
#include "cmp_player_state.h"
#include "../game.h"

#include <Box2D/Dynamics/Contacts/b2Contact.h>


using namespace std;
using namespace sf;

// Lifespan of projectile
float PlasmaComponent::max_lifespan = 2.0f;
// Full strength of projectile
float PlasmaComponent::max_strength = 1.0f;
// Speed of projectile
float PlasmaComponent::speed = 1.0f;

// Sounds
sf::SoundBuffer PlasmaComponent::explosionBuffer;
sf::Sound PlasmaComponent::explosionSound;

// Update - count lifespan and reduce strength of projectile
void PlasmaComponent::update(double dt) {
	_current_lifespan += dt;
	reduceStrength();
	if (_current_lifespan >= max_lifespan) {
		_parent->setForDelete();
	}
	auto enemy = _target->GetCompatibleComponent<PlayerPhysicsComponent>().at(0);
	auto enemy_fix = enemy->getFixture();
	auto contacts = _parent->GetCompatibleComponent<PhysicsComponent>().at(0)->getTouching();
	for (int i = 0; i < contacts.size(); i++) {
		auto fixtureA = contacts[i]->GetFixtureA();
		auto fixtureB = contacts[i]->GetFixtureB();
		if (fixtureA == enemy_fix || fixtureB == enemy_fix) {
			explosionSound.play();
			_parent->setForDelete();
			auto enemyState = _target->GetCompatibleComponent<PlayerStateComponent>().at(0);
			enemyState->takeDamage(_current_strength);
		}
	}
}

void PlasmaComponent::render() {
	
}

void PlasmaComponent::loadSounds()
{
	explosionBuffer.loadFromFile("res/sounds/explosion.wav");
	explosionSound.setBuffer(explosionBuffer);
	explosionSound.setVolume(20.0f);
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

PlasmaComponent::PlasmaComponent(Entity* p, Entity* target, Vector2f direction)
	: Component(p), _target(target), _current_lifespan(0.0f) {
	// Attach a physics component and apply impulse
	vector<unsigned int> mask;
	shared_ptr<PhysicsComponent> physics;
	if (target == player1.get()) {
		mask.push_back(P1_BIT);
		mask.push_back(P1_TURRET_PROJ_BIT);
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(8.0f, 8.0f), P2_PROJECTILE_BIT, mask);
	}
	else {
		mask.push_back(P2_BIT);
		mask.push_back(P2_TURRET_PROJ_BIT);
		physics = _parent->addComponent<PhysicsComponent>(true, Vector2f(8.0f, 8.0f), P1_PROJECTILE_BIT, mask);
	}
	physics->setRestitution(0.4f);
	physics->setFriction(0.005f);
	physics->impulse(direction * speed);
	//physics->setVelocity(direction * speed * 200.0f);

}
