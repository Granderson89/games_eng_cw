#pragma once

#include <ecm.h>
#include "..\components\cmp_camera.h"
#include "..\components\cmp_sprite.h"
#include <memory>

class BackgroundBuilderComponent : public Component
{
private:
	const float _max_zoom = 1000;	///////////////////////////////////// maybe should be in game.h
	std::shared_ptr<CameraControllerComponent> _cam;
	std::vector<std::shared_ptr<SpriteComponent>> _sprites;
public:
	explicit BackgroundBuilderComponent(Entity* p);
	~BackgroundBuilderComponent();

	void update(double dt) override;
	void render() override {}
};