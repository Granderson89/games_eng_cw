#pragma once

#include "engine.h"
#include "ecm.h"
#include <vector>

using namespace std;

class GameOverScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> buttons;
	int highlighted;
public:
	GameOverScene() = default;
	~GameOverScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

	void HighlightSelected();
};
