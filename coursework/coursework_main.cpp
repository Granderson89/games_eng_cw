#include "engine.h"
#include "game.h"

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
	Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &menu);
}