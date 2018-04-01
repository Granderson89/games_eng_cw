#pragma once

#include "ecm.h"

class TorpedoComponent : public Component {
protected:
	static float max_lifespan;
	static float strength;
	static float damage_range;
	static float speed;

	float _current_lifespan;

public:
	TorpedoComponent() = delete;
	explicit TorpedoComponent(Entity* p);

	void explode();

	void update(double dt) override;
	void render() override;
};
