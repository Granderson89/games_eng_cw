#pragma once

#include "engine.h"
#include <SFML/Audio.hpp>

using namespace std;

class MenuScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> buttons;
	static int highlighted;
	static float timer;
	static sf::SoundBuffer menubgBuffer;
	static sf::Sound menubgSound;

public:
  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;

  void HighlightSelected();
  bool ControllerConnected();

  static void loadSounds();
};
