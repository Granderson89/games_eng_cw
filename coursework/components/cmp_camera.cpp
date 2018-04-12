#define _USE_MATH_DEFINES

#include "cmp_camera.h"
#include "system_renderer.h"
#include "../game.h"
#include "cmp_physics.h"
#include <cmath>
#include <math.h>
using namespace sf;

Vector2f midpoint;

CameraControllerComponent::CameraControllerComponent(Entity* p) : Component(p)
{
	view.reset(FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));	// hardcoded values ///////////////////////////////////////////////
	Renderer::getWindow().setView(view);
}


void CameraControllerComponent::addTarget(std::shared_ptr<Entity> p)
{
	targets.push_back(p);
}

Vector2f CameraControllerComponent::getMidpoint()
{
	return midpoint;
}

sf::View CameraControllerComponent::getView()
{
	return view;
}


void CameraControllerComponent::update(double dt)
{
	midpoint = Vector2f(0.0f, 0.0f);
	float aspectRatio = (float)Renderer::getWindow().getSize().x / (float)Renderer::getWindow().getSize().y;

	for (auto t : targets)
		midpoint += t->getPosition();
	midpoint /= (float)targets.size();

	view.setCenter(midpoint);

	// Find the correct size for the camera view
	float width = 0.0f;
	float margin = 500.0f;
	for (int i = 0; i < targets.size() - 1; i++)
	{
		for (int j = 1; j < targets.size(); j++)
		{
			if (abs(targets[i]->getPosition().x - targets[j]->getPosition().x) > width)
				width = abs(targets[i]->getPosition().x - targets[j]->getPosition().x);
			if (abs(targets[i]->getPosition().y - targets[j]->getPosition().y) * aspectRatio > width)
				width = abs(targets[i]->getPosition().y - targets[j]->getPosition().y) * aspectRatio;
		}
	}
	width += margin;
	
	if (width > 50.0f) {
		if (!boundary_active) {
			locked_midpoint = midpoint;
			locked_p1_dist = length(player1->getPosition() - locked_midpoint);
			locked_p2_dist = length(player2->getPosition() - locked_midpoint);

		}
		boundary_active = true;
		{
			// Get vector from midpoint to player 1
			auto m2p1 = player1->getPosition() - locked_midpoint;
			// Normalize
			auto direction = normalize(m2p1);
			// Calculate position of boundary
			auto position = locked_midpoint + direction * locked_p1_dist * 2.0f;
			// Calculate rotation of boundary
			float rotation = atan2(direction.y, direction.x) * 180.0f / M_PI;
			// Make boundary
			auto boundary = level1.makeEntity();
			boundary->setPosition(position);
			boundary->addTag("boundary1");
			// Add Shape Component
			auto s = boundary->addComponent<ShapeComponent>();
			s->setShape<sf::RectangleShape>(Vector2f(5.0f, 80.0f));
			s->getShape().setFillColor(Color::Yellow);
			s->getShape().setOrigin(2.5f, 10.0f);
			vector<unsigned int> mask;
			mask.push_back(P1_BIT);
			mask.push_back(P2_BIT);
			boundary->addComponent<PhysicsComponent>(false, Vector2f(5.0f, 80.0f), BOUNDARY_BIT, mask);
			boundary->setRotation(rotation);
		}
		{
			// Get vector from midpoint to player 2
			auto m2p2 = player2->getPosition() - locked_midpoint;
			// Normalize
			auto direction = normalize(m2p2);
			// Calculate position of boundary
			auto position = locked_midpoint + direction * locked_p2_dist * 2.0f;
			// Calculate rotation of boundary
			float rotation = atan2(direction.y, direction.x) * 180.0f / M_PI;
			// Make boundary
			auto boundary = level1.makeEntity();
			boundary->setPosition(position);
			boundary->addTag("boundary2");
			// Add Shape Component
			auto s = boundary->addComponent<ShapeComponent>();
			s->setShape<sf::RectangleShape>(Vector2f(5.0f, 80.0f));
			s->getShape().setFillColor(Color::Yellow);
			s->getShape().setOrigin(2.5f, 10.0f);
			vector<unsigned int> mask;
			mask.push_back(P1_BIT);
			mask.push_back(P2_BIT);
			boundary->addComponent<PhysicsComponent>(false, Vector2f(5.0f, 80.0f), BOUNDARY_BIT, mask);
			boundary->setRotation(rotation);
		}
		auto old1 = level1.ents.find("boundary1");
		for (int i = 0; i < old1.size() - 1; i++) {
			old1.at(i)->setForDelete();
		}
		auto old2 = level1.ents.find("boundary2");
		for (int i = 0; i < old2.size() - 1; i++) {
			old2.at(i)->setForDelete();
		}
	}
	else if (width < 25.0f) {
		boundary_active = false;
		auto old1 = level1.ents.find("boundary1");
		for (int i = 0; i < old1.size(); i++) {
			old1.at(i)->setForDelete();
		}
		auto old2 = level1.ents.find("boundary2");
		for (int i = 0; i < old2.size(); i++) {
			old2.at(i)->setForDelete();
		}
	}
	view.setSize(width, width / aspectRatio);

	Renderer::getWindow().setView(view);
}