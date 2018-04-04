#pragma once

#include "../game.h"

using namespace sf;

class MissileComponent : public Component {
protected:
	static float strength;
	static float speed;
	
	shared_ptr<Entity> _target;

public:
	MissileComponent() = delete;
	explicit MissileComponent(Entity* p, shared_ptr<Entity> target);

	void explode();

	void update(double dt) override;
	void render() override;
};
