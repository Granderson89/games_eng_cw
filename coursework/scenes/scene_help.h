#pragma once

#include "engine.h"

using namespace std;

class HelpScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> buttons;
	static int highlighted;
public:
	HelpScene() = default;
  ~HelpScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};
