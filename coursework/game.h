#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_game_over.h"
#include "input_manager.h"

using namespace std;
using namespace sf;

extern Texture spritesheet;
extern MenuScene menu;
extern Level1Scene level1;
extern GameOverScene gameOver;
extern InputManager im;
extern shared_ptr<Entity> player1;
extern shared_ptr<Entity> player2;
extern unsigned int P1_BIT;
extern unsigned int P1_PROJECTILE_BIT;
extern unsigned int P1_TURRET_PROJ_BIT;
extern unsigned int P2_BIT;
extern unsigned int P2_PROJECTILE_BIT;
extern unsigned int P2_TURRET_PROJ_BIT;

extern int winner;