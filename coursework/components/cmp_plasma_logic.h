#pragma once

#include "ecm.h"
#include "../game.h"


class PlasmaComponent : public Component {
protected:
	static float max_lifespan;
	static float max_strength;
	static float speed;

	shared_ptr<Entity> _target;
	float _current_strength;
	float _current_lifespan;

public:
	PlasmaComponent() = delete;
	explicit PlasmaComponent(Entity* p, shared_ptr<Entity> target, float ship_rotation);

	void reduceStrength();

	void update(double dt) override;
	void render() override;
};
