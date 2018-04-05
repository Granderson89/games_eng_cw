#include "cmp_player_state.h"



PlayerStateComponent::PlayerStateComponent(Entity* p) :Component(p)
{
	health = maxHealth;
	energy = maxEnergy;
}


void PlayerStateComponent::update(double dt)
{
	// Energy regeneration
	if (energy < maxEnergy)
		energy += energyRegen * dt;

	if (health <= 0.0f)
	{
		// Death resolution here ///////////////////////////////////////////////////////

	}
}

void PlayerStateComponent::render()
{
}

void PlayerStateComponent::takeDamage(float damage) {
	health -= damage;
}