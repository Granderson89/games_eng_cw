#include "engine.h"
#include "game.h"
#include "components/cmp_weapon_component.h"
#include "components/cmp_plasma_logic.h"
#include "components/cmp_torpedo_logic.h"
#include "components/cmp_missile_logic.h"
#include "components/cmp_thrusters.h"

using namespace std;

MenuScene menu;
OptionsScene options;
ControlsScene controls;
GraphicsScene graphics;
PauseScene pause;
Level1Scene level1;
GameOverScene gameOver;

// Graphics defaults
Vector2i resolution(1920, 1080);
unsigned int window_style = sf::Style::Default;


int main() {
	InputManager::initialize();
	controls.readPrefs();
	graphics.readPrefs();
	WeaponComponent::loadSounds();
	PlasmaComponent::loadSounds();
	TorpedoComponent::loadSounds();
	MissileComponent::loadSounds();
	ThrustersComponent::loadSounds();
	Level1Scene::loadSounds();
	MenuScene::loadSounds();
	Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &menu);
}