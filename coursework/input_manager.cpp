#include "input_manager.h"

using namespace sf;


// Sets default controls //////////////////////////////(or loads from file later)
void InputManager::initialize()
{
	player1Input.source = -1;
	player1Input.moveForward = Keyboard::W;
	player1Input.moveBackwards = Keyboard::S;
	player1Input.turnLeft = Keyboard::A;
	player1Input.turnRight = Keyboard::D;
	player1Input.fire = Keyboard::F;
	player1Input.changeWeapon = Keyboard::R;
	player1Input.turretClockwise = Keyboard::C;
	player1Input.turretCounterClockwise = Keyboard::Z;
	player1Input.fireTurret = Keyboard::X;
	player1Input.jumpCharging = Keyboard::V;
	player1Input.thrusterWheelUp = Keyboard::Q;
	// Thruster selecting
	player1Input.selectorAxis[0] = Keyboard::Num8;
	player1Input.selectorAxis[0] = Keyboard::Num9;
	player1Input.selectorAxis[0] = Keyboard::Num6;
	player1Input.selectorAxis[0] = Keyboard::Num3;
	player1Input.selectorAxis[0] = Keyboard::Num2;
	player1Input.selectorAxis[0] = Keyboard::Num1;
	player1Input.selectorAxis[0] = Keyboard::Num4;
	player1Input.selectorAxis[0] = Keyboard::Num7;

	player1Input.boostMovement = Keyboard::Num5;
}

void InputManager::update()
{
	Joystick::update();

	// Player 1 stuff

	// Controller
	if (player1Input.source >= 0)
	{
		// Movement
		if (Joystick::isButtonPressed(player1Input.source, player1Input.moveForward))
			Player1.moveForward = true;
		else
			Player1.moveForward = false;
		if (Joystick::isButtonPressed(player1Input.source, player1Input.moveBackwards))
			Player1.moveBackwards = true;
		else
			Player1.moveBackwards = false;
		if (Joystick::isButtonPressed(player1Input.source, player1Input.turnLeft))
			Player1.turnLeft = true;
		else
			Player1.turnLeft = false;
		if (Joystick::isButtonPressed(player1Input.source, player1Input.turnRight))
			Player1.turnRight = true;
		else
			Player1.turnRight = false;

		// Analog movement
		if (Joystick::Axis::X > 30.0f)
			Player1.moveForward = true;
		else
			Player1.moveForward = false;
		if (Joystick::Axis::X < -30.0f)
			Player1.moveForward = true;
		else
			Player1.moveForward = false;
		if (Joystick::Axis::Y > 30.0f)
			Player1.moveForward = true;
		else
			Player1.moveForward = false;
		if (Joystick::Axis::Y < -30.0f)
			Player1.moveForward = true;
		else
			Player1.moveForward = false;

		// Fire
		if (Joystick::isButtonPressed(player1Input.source, player1Input.fire))
			Player1.fire = true;
		else
			Player1.fire = false;
		// Change weapon
		if (Joystick::isButtonPressed(player1Input.source, player1Input.changeWeapon))
			Player1.changeWeapon = true;
		else
			Player1.changeWeapon = false;

		// Turret stuff
		if (Joystick::isButtonPressed(player1Input.source, player1Input.turretClockwise))
			Player1.turretClockwise = true;
		else
			Player1.turretClockwise = false;
		if (Joystick::isButtonPressed(player1Input.source, player1Input.turretCounterClockwise))
			Player1.turretCounterClockwise = true;
		else
			Player1.turretCounterClockwise = false;
		if (Joystick::isButtonPressed(player1Input.source, player1Input.fireTurret))
			Player1.fireTurret = true;
		else
			Player1.fireTurret = false;

		// Jump
		if (Joystick::isButtonPressed(player1Input.source, player1Input.jumpCharging))
		{
			Player1.jumpCharging = true;
			Player1.jumpExecute = false;
		}
		if (!Joystick::isButtonPressed(player1Input.source, player1Input.jumpCharging) && !Player1.jumpExecute)
		{
			Player1.jumpCharging = false;
			Player1.jumpExecute = false;
		}
		if (!Joystick::isButtonPressed(player1Input.source, player1Input.jumpCharging) && Player1.jumpCharging == true)
		{
			Player1.jumpCharging = false;
			Player1.jumpExecute = true;
		}

		// Thruster wheel
		if (Joystick::isButtonPressed(player1Input.source, player1Input.thrusterWheelUp))
			Player1.thrusterWheelUp = true;
		else
			Player1.thrusterWheelUp = false;
	}
}