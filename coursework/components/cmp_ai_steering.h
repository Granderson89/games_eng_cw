#pragma once
#include <ecm.h>
#include "../steering.h"

class SteeringComponent : public Component {
protected:
	Seek _seek;
	Entity* _target;
public:
	void update(const double &dt) override;
	void move(const sf::Vector2f&);
	void move(float x, float y);
	void render() override {}
	explicit SteeringComponent(Entity *p, Entity* target, float speed);
	SteeringComponent() = delete;
};