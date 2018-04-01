#include "cmp_torpedo_logic.h"

using namespace std;
using namespace sf;

// Lifespan of projectile
float TorpedoComponent::max_lifespan = 5.0f;
// Full strength of projectile
float TorpedoComponent::strength = 200.0f;
// Speed of projectile
float TorpedoComponent::speed = 2.0f;
// Range of explosion
float TorpedoComponent::damage_range = 5.0f;

// Update - count lifespan
void TorpedoComponent::update(double dt) {
	_current_lifespan -= dt;
	if (_current_lifespan <= 0.0f) {
		explode();
	}
}

void TorpedoComponent::render() {

}

void TorpedoComponent::explode() {

}

TorpedoComponent::TorpedoComponent(Entity* p)
	: Component(p), _current_lifespan(max_lifespan) {}
