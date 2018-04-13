#include "cmp_player_state.h"
#include "../game.h"


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
		_parent->setForDelete();
		if (_parent == player1.get()) {
			winner = 2;
		}
		else {
			winner = 1;
		}
		Engine::ChangeScene(&gameOver);
	}
}

void PlayerStateComponent::render()
{
}

void PlayerStateComponent::takeDamage(float damage) {
	health -= damage;
}