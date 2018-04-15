#include "resource_manager.h"

Texture ResourceManager::tex_test = Texture();
Texture ResourceManager::Tex_background = Texture();
Texture ResourceManager::Tex_player1 = Texture();
Texture ResourceManager::Tex_player2 = Texture();
Texture ResourceManager::Tex_warp_blue = Texture();
Texture ResourceManager::Tex_warp_blue_exit = Texture();
Texture ResourceManager::Tex_warp_red = Texture();
Texture ResourceManager::Tex_warp_red_exit = Texture();
Texture ResourceManager::Tex_thruster1_on = Texture();
Texture ResourceManager::Tex_thruster2_on = Texture();
Texture ResourceManager::Tex_thruster1_off = Texture();
Texture ResourceManager::Tex_thruster2_off = Texture();



bool ResourceManager::Load()
{
	bool good = true;
	bool test = true;
	if (!tex_test.loadFromFile("res/img/test.png"))
	{
		good = false;
		test = false;
	}
	if (!Tex_background.loadFromFile("res/img/background.jpeg"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_player1.loadFromFile("res/img/Player1.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_player2.loadFromFile("res/img/Player2.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_warp_blue.loadFromFile("res/img/Warp_jump_blue.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_warp_blue_exit.loadFromFile("res/img/Warp_jump_blue_exit.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_warp_red.loadFromFile("res/img/Warp_jump_red.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_warp_red_exit.loadFromFile("res/img/Warp_jump_red_exit.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_thruster1_on.loadFromFile("res/img/Thruster1_on.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_thruster2_on.loadFromFile("res/img/Thruster2_on.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_thruster1_off.loadFromFile("res/img/Thruster1_off.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_thruster2_off.loadFromFile("res/img/Thruster2_off.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	return good;
}