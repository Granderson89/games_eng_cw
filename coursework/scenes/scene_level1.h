#pragma once

#include "engine.h"

class Level1Scene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	void createPlayer(Entity* player, Entity* opponent, sf::Texture& ship_tex, float width, float length);
	void createHud(std::shared_ptr<Entity> player);
};
