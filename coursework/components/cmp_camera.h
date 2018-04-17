#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "ecm.h"


// This component is meant to be attached to a dummy Entity as it only needs to run once per frame after being properly initialized
class CameraControllerComponent : public Component
{
private:
	std::vector<std::shared_ptr<Entity>> targets;
	sf::View view;
	bool boundary_active = false;
	sf::Vector2f locked_midpoint;
	float locked_p1_dist;
	float locked_p2_dist;


public:
	explicit CameraControllerComponent(Entity* p);
	CameraControllerComponent() = delete;

	void update(const double &dt) override;
	void render() override {}

	// Adds an entity to the list of fallowed targets
	void addTarget(std::shared_ptr<Entity> p);

	sf::Vector2f getMidpoint();
	sf::View getView();
};