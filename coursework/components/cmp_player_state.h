#pragma once
#include "ecm.h"

class PlayerStateComponent : Component
{
private:
	const float maxHealth = 100.0f;
	const float maxEnergy = 120.0f;
	const float energyRegen = 2.0f;	// Energy regeneration per second
	float speed;
	std::vector<Entity> players;
public:
	float health;
	float energy;


	explicit PlayerStateComponent(Entity* p);
	PlayerStateComponent() = delete;

	void update(double dt) override;
};