#pragma once

#include <SFML\Graphics.hpp>
#include "game.h"

class ResourceManager
{
private:
public:
	ResourceManager() = delete;

	// Returns false if any resources did not load
	static bool Load();
	static bool done;

	static Texture tex_test;
	static Texture Tex_background;
	static Texture Tex_player1;
	static Texture Tex_player2;
	static Texture Tex_warp_blue;
	static Texture Tex_warp_blue_exit;
	static Texture Tex_warp_red;
	static Texture Tex_warp_red_exit;
	static Texture Tex_thruster1_on;
	static Texture Tex_thruster2_on;
	static Texture Tex_thruster1_off;
	static Texture Tex_thruster2_off;
	static Texture Tex_cannon_mount;
	static Texture Tex_torpedo_mount;
	static Texture Tex_missile_mount;
	static Texture Tex_turret;
	static Texture Tex_plasma;
	static Texture Tex_torpedo;
	static Texture Tex_missile;
	static Texture Tex_help;

};