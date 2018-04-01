#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_menu.h"
#include "input_manager.h"

using namespace std;
using namespace sf;

extern MenuScene menu;
extern Level1Scene level1;
extern InputManager im;
extern shared_ptr<Entity> player1;
extern shared_ptr<Entity> player2;