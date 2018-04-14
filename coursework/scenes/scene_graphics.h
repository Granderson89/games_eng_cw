#pragma once

#include "engine.h"
#include "ecm.h"
#include <vector>

using namespace std;

class GraphicsScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> buttons;
	int highlighted;
public:
	GraphicsScene() = default;
	~GraphicsScene() override = default;

	void Load() override;
	void UnLoad() override;

	void Update(const double& dt) override;

	void HighlightSelected();
	void readPrefs();
};
