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


Texture ResourceManager::Tex_cannon_mount = Texture();
Texture ResourceManager::Tex_torpedo_mount = Texture();
Texture ResourceManager::Tex_missile_mount = Texture();
Texture ResourceManager::Tex_turret = Texture();
Texture ResourceManager::Tex_plasma = Texture();
Texture ResourceManager::Tex_torpedo = Texture();
Texture ResourceManager::Tex_missile = Texture();
Texture ResourceManager::Tex_help = Texture();


bool ResourceManager::done = false;

bool ResourceManager::Load()
{
	if (done)
		return true;
	done = true;
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
			Tex_player1 = tex_test;
	}
	if (!Tex_player2.loadFromFile("res/img/Player2.png"))
	{
		good = false;
		if (test)
			Tex_player2 = tex_test;
	}
	if (!Tex_warp_blue.loadFromFile("res/img/Warp_jump_blue.png"))
	{
		good = false;
		if (test)
			Tex_warp_blue = tex_test;
	}
	if (!Tex_cannon_mount.loadFromFile("res/img/cannonGun.png"))
	{
		good = false;
		if (test)
			Tex_cannon_mount = tex_test;
	}
	if (!Tex_warp_blue_exit.loadFromFile("res/img/Warp_jump_blue_exit.png"))
	{
		good = false;
		if (test)
			Tex_warp_blue_exit = tex_test;
	}
	if (!Tex_torpedo_mount.loadFromFile("res/img/torpedoGun.png"))
	{
		good = false;
		if (test)
			Tex_torpedo_mount = tex_test;
	}
	if (!Tex_warp_red.loadFromFile("res/img/Warp_jump_red.png"))
	{
		good = false;
		if (test)
			Tex_warp_red = tex_test;
	}
	if (!Tex_missile_mount.loadFromFile("res/img/missileGun.png"))
	{
		good = false;
		if (test)
			Tex_missile_mount = tex_test;
	}
	if (!Tex_warp_red_exit.loadFromFile("res/img/Warp_jump_red_exit.png"))
	{
		good = false;
		if (test)
			Tex_warp_red_exit = tex_test;
	}
	if (!Tex_turret.loadFromFile("res/img/turret.png"))
	{
		good = false;
		if (test)
			Tex_turret = tex_test;
	}
	if (!Tex_thruster1_on.loadFromFile("res/img/Thruster1_on.png"))
	{
		good = false;
		if (test)
			Tex_thruster1_on = tex_test;
	}
	if (!Tex_plasma.loadFromFile("res/img/plasma.png"))
	{
		good = false;
		if (test)
			Tex_plasma = tex_test;
	}
	if (!Tex_thruster2_on.loadFromFile("res/img/Thruster2_on.png"))
	{
		good = false;
		if (test)
			Tex_thruster2_on = tex_test;
	}
	if (!Tex_torpedo.loadFromFile("res/img/torpedo.png"))
	{
		good = false;
		if (test)
			Tex_torpedo = tex_test;
	}
	if (!Tex_thruster1_off.loadFromFile("res/img/Thruster1_off.png"))
	{
		good = false;
		if (test)
			Tex_thruster1_off = tex_test;
	}
	if (!Tex_thruster2_off.loadFromFile("res/img/Thruster2_off.png"))
	{
		good = false;
		if (test)
			Tex_thruster2_off = tex_test;
	}
	if (!Tex_missile.loadFromFile("res/img/missile.png"))
	{
		good = false;
		if (test)
			Tex_missile = tex_test;
	}
	if (!Tex_help.loadFromFile("res/img/help.png"))
	{
		good = false;
		if (test)
			Tex_help = tex_test;
	}
	return good;
}