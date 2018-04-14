#include "resource_manager.h"

Texture ResourceManager::tex_test = Texture();
Texture ResourceManager::Tex_background = Texture();
Texture ResourceManager::Tex_player1 = Texture();
Texture ResourceManager::Tex_player2 = Texture();



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
	if (!Tex_player1.loadFromFile("res/img/player1.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_player2.loadFromFile("res/img/player2.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	return good;
}