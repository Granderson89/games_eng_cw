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
		cout << "Test image file not found!" << endl;
		good = false;
		test = false;
	}
	if (!Tex_background.loadFromFile("res/img/test.png"))
	{
		cout << "Background image file not found!" << endl;
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_player1.loadFromFile("res/img/player1.png"))
	{
		cout << "Background image file not found!" << endl;
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_player2.loadFromFile("res/img/player2.png"))
	{
		cout << "Background image file not found!" << endl;
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	return good;
}