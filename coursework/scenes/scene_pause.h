#pragma once

#include "engine.h"

using namespace std;

class PauseScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> buttons;
	static int highlighted;
public:
  PauseScene() = default;
  ~PauseScene() override = default;

  void Load() override;

  void Update(const double& dt) override;

  void HighlightSelected();
};
