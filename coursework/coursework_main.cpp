#include "engine.h"
#include "game.h"

using namespace std;

MenuScene menu;
OptionsScene options;
ControlsScene controls;
GraphicsScene graphics;
Level1Scene level1;
GameOverScene gameOver;

int main() {
	Engine::Start(1920, 1080, "Some Spaceship Game", &menu);
}