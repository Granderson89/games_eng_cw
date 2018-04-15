#include "resource_manager.h"

Texture ResourceManager::tex_test = Texture();
Texture ResourceManager::Tex_background = Texture();
Texture ResourceManager::Tex_player1 = Texture();
Texture ResourceManager::Tex_player2 = Texture();
Texture ResourceManager::Tex_cannon_mount = Texture();
Texture ResourceManager::Tex_torpedo_mount = Texture();
Texture ResourceManager::Tex_missile_mount = Texture();
Texture ResourceManager::Tex_turret = Texture();
Texture ResourceManager::Tex_plasma = Texture();
Texture ResourceManager::Tex_torpedo = Texture();
Texture ResourceManager::Tex_missile = Texture();

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
	if (!Tex_cannon_mount.loadFromFile("res/img/cannonGun.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_torpedo_mount.loadFromFile("res/img/torpedoGun.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_missile_mount.loadFromFile("res/img/missileGun.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_turret.loadFromFile("res/img/turret.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_plasma.loadFromFile("res/img/plasma.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_torpedo.loadFromFile("res/img/torpedo.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	if (!Tex_missile.loadFromFile("res/img/missile.png"))
	{
		good = false;
		if (test)
			Tex_background = tex_test;
	}
	return good;
}