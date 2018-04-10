#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_options.h"
#include "scenes/scene_graphics.h"
#include "scenes/scene_controls.h"
#include "scenes/scene_pause.h"
#include "scenes/scene_game_over.h"
#include "input_manager.h"

using namespace std;
using namespace sf;

extern Texture spritesheet;
extern MenuScene menu;
extern OptionsScene options;
extern ControlsScene controls;
extern GraphicsScene graphics;
extern Level1Scene level1;
extern PauseScene pause;
extern GameOverScene gameOver;
extern Vector2i resolution;
extern unsigned int window_style;
extern shared_ptr<Entity> player1;
extern shared_ptr<Entity> player2;
extern shared_ptr<Entity> ce;
extern unsigned int P1_BIT;
extern unsigned int P1_PROJECTILE_BIT;
extern unsigned int P1_TURRET_PROJ_BIT;
extern unsigned int P2_BIT;
extern unsigned int P2_PROJECTILE_BIT;
extern unsigned int P2_TURRET_PROJ_BIT;

extern int winner;