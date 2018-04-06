#pragma once

#include "engine.h"

using namespace std;

class MenuScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> buttons;
	static int highlighted;
	static float timer;
public:
  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;

  void HighlightSelected();
};
