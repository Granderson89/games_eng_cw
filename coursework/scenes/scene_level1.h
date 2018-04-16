#pragma once

#include "engine.h"
#include <SFML/Audio.hpp>

class Level1Scene : public Scene {
private:
	static sf::SoundBuffer bgBuffer;
	static sf::Sound bgSound;
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	void createPlayer(Entity* player, Entity* opponent, sf::Texture& ship_tex, float width, float length);
	void createHud(std::shared_ptr<Entity> player);

  static void loadSounds();
};
