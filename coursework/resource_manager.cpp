#include "resource_manager.h"

Texture ResourceManager::tex_test = Texture();
Texture ResourceManager::Tex_background = Texture();
Texture ResourceManager::Tex_player1 = Texture();
Texture ResourceManager::Tex_player2 = Texture();
Texture ResourceManager::Tex_warp_blue = Texture();



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
	return good;
}