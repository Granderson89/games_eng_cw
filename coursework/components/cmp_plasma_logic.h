#pragma once

#include "ecm.h"

class PlasmaComponent : public Component {
protected:
	static float max_lifespan;
	static float max_strength;
	static float speed;

	float _current_strength;
	float _current_lifespan;

public:
	PlasmaComponent() = delete;
	explicit PlasmaComponent(Entity* p);

	void reduceStrength();

	void update(double dt) override;
	void render() override;
};
