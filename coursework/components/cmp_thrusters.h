#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "cmp_animator.h"
#include "cmp_physics.h"


class ThrustersComponent : public Component
{
private:
	sf::Vector2f _startingOffsets[6];
	sf::Vector2f _startingNormals[6];
	sf::Vector2f _offsets[6];
	sf::Vector2f _normals[6];
	bool _firing[6];	// Whether the thruster is firing or not
	float _power;
	Entity* _parent;

	std::shared_ptr<PhysicsComponent> phc;
	std::vector<std::shared_ptr<AnimatorComponent>> anims;
	int pl = 1;

public:
	// Assumes the spaceship is pointing north
	explicit ThrustersComponent(Entity* p, const sf::Vector2f& dim, const float& power);
	ThrustersComponent() = delete;
	~ThrustersComponent() override;

	void update(double dt) override;
	void render() override {}
};