#pragma once
#include <ecm.h>
#include "../steering.h"

class SteeringComponent : public Component {
protected:
	Seek _seek;
	shared_ptr<Entity> _target;
public:
	void update(double) override;
	void move(const sf::Vector2f&);
	void move(float x, float y);
	void render() override {}
	explicit SteeringComponent(Entity *p, shared_ptr<Entity> target, float speed);
	SteeringComponent() = delete;
};