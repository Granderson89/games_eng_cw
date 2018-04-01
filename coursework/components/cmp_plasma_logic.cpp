#include "cmp_plasma_logic.h"

using namespace std;
using namespace sf;

// Lifespan of projectile
float PlasmaComponent::max_lifespan = 1.0f;
// Full strength of projectile
float PlasmaComponent::max_strength = 100.0f;
// Speed of projectile
float PlasmaComponent::speed = 3.0f;

// Update - count lifespan and reduce strength of projectile
void PlasmaComponent::update(double dt) {
	_current_lifespan -= dt;
	reduceStrength();
	if (_current_lifespan <= 0.0f) {
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
}

PlasmaComponent::PlasmaComponent(Entity* p)
	: Component(p), _current_lifespan(max_lifespan) {}
