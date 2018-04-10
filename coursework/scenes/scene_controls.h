#pragma once

#include "engine.h"
#include "ecm.h"
#include <vector>

using namespace std;
using namespace sf;

enum selection {
	P1_SOURCE,
	P1_FIRE,
	P1_CHANGE_WEAPON,
	P1_FIRE_TURRET,
	P1_CHARGE_JUMP,
	P2_SOURCE,
	P2_FIRE,
	P2_CHANGE_WEAPON,
	P2_FIRE_TURRET,
	P2_CHARGE_JUMP,
	BACK,
	NONE
};

class ControlsScene : public Scene {
private:
	// List of UI buttons
	static vector<shared_ptr<Entity>> controllerNames;
	static vector<shared_ptr<Entity>> buttons;
	static vector<shared_ptr<Entity>> controls;
	static selection highlighted;
	static selection changeControl;
	static float timer;
public:
	ControlsScene() = default;
	~ControlsScene() override = default;

	void Load() override;
	void UnLoad() override;

	void Update(const double& dt) override;

	void HighlightSelected();
	void MakeButton(Vector2f, float, IntRect, string);
	void MakeControllerName(Vector2f, float, string);
	void MakeControlBox(Vector2f, float, const char*);
	void SwapSource(int);
	void UpdateControls(int player, const char* fire, const char* changeWeapon, const char* fireTurret, const char* jumpCharging);

	void createPlayerButtons(int player, float scale, IntRect buttonRect);
	void readPrefs();
};
