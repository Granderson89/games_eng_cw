#pragma once

#include "ecm.h"

class HudComponent : public Component {
private:
	std::shared_ptr<Entity> _player;
	std::shared_ptr<Entity> _camera;

public:
	explicit HudComponent(Entity* p, std::shared_ptr<Entity> player, std::shared_ptr<Entity> camera);
	HudComponent() = delete;

	void update(double dt) override;
	void render() override;
};