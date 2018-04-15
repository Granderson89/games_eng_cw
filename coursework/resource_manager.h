#pragma once

#include <SFML\Graphics.hpp>
#include "game.h"		//////////////////////////////////////////////// Included this to have Texture class ////////////////////////////////

class ResourceManager
{
private:
public:
	ResourceManager() = delete;

	// Returns false if any resources did not load
	static bool Load();

	static Texture tex_test;
	static Texture Tex_background;
	static Texture Tex_player1;
	static Texture Tex_player2;
	static Texture Tex_cannon_mount;
	static Texture Tex_torpedo_mount;
	static Texture Tex_missile_mount;
	static Texture Tex_turret;

};