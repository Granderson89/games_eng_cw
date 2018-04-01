#pragma once

#include "ecm.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon_component.h"
#include "../engine/src/system_physics.h"

#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace sf;

struct SteeringOutput {
	// Direction of travel
	Vector2f direction;
	// Rotation of travel
	float rotation;
};


class MissileComponent : public Component {
protected:
	static float strength;
	static float speed;
	
	shared_ptr<Entity> _target;


public:
	MissileComponent() = delete;
	explicit MissileComponent(Entity* p, shared_ptr<Entity> target);

	SteeringOutput seek();
	void explode();

	void update(double dt) override;
	void render() override;
};
