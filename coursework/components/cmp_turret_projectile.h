#pragma once

#include "ecm.h"
#include "../game.h"

class TurretProjComponent : public Component {
protected:
	static float max_lifespan;
	static float strength;
	static float speed;

	float _current_lifespan;

	shared_ptr<Entity> _target;
	vector<shared_ptr<Entity>> _enemy_projectiles;

public:
	TurretProjComponent() = delete;
	explicit TurretProjComponent(Entity* p, shared_ptr<Entity> target, float turret_rotation);

	void update(const double &dt) override;
	void render() override;
};
