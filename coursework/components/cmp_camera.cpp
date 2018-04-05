#include "cmp_camera.h"
#include "system_renderer.h"
#include <cmath>

using namespace sf;



CameraControllerComponent::CameraControllerComponent(Entity* p) : Component(p)
{
	view.reset(FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));	// hardcoded values ///////////////////////////////////////////////
	Renderer::getWindow().setView(view);
}


void CameraControllerComponent::addTarget(std::shared_ptr<Entity> p)
{
	targets.push_back(p);
}


void CameraControllerComponent::update(double dt)
{
	Vector2f midpoint = Vector2f(0.0f, 0.0f);
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
	view.setSize(width, width / aspectRatio);

	Renderer::getWindow().setView(view);
}