#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>


class ThrustersComponent : public Component
{
private:
	sf::Vector2f _startingOffsets[6];
	sf::Vector2f _startingNormals[6];
	sf::Vector2f _offsets[6];
	sf::Vector2f _normals[6];
	float _power;
	Entity* _parent;

public:
	// Assumes the spaceship is pointing north
	explicit ThrustersComponent(Entity* p, const sf::Vector2f& dim, const float& power);
	ThrustersComponent() = delete;
	~ThrustersComponent() override;

	void update(double dt) override;
	void render() override {}

	// Fires a thruster (index start at 0 = N and continues clockwise)
	void fireThruster(const int& index);
};