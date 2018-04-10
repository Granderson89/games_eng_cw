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

  static void loadSounds();
};
