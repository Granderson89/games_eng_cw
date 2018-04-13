#pragma once

#include "ecm.h"
#include "../game.h"


class TorpedoComponent : public Component {
protected:
	static float max_lifespan;
	static float strength;
	static float damage_range;
	static float speed;

	shared_ptr<Entity> _target;
	float _current_lifespan;

public:
	TorpedoComponent() = delete;
	explicit TorpedoComponent(Entity* p, shared_ptr<Entity> target, Vector2f direction);

	void explode();

	void update(double dt) override;
	void render() override;
};
