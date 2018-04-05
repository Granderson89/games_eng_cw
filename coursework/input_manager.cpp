#include "input_manager.h"

using namespace sf;

InputManager::inputs InputManager::playerInput[2];

InputManager::actions InputManager::Player[2];

// Sets default controls //////////////////////////////(or loads from file later)
void InputManager::initialize()
{
	playerInput[0].source = -1;
	playerInput[0].moveForward = Keyboard::W;
	playerInput[0].moveBackwards = Keyboard::S;
	playerInput[0].turnLeft = Keyboard::A;
	playerInput[0].turnRight = Keyboard::D;
	playerInput[0].fire = Keyboard::F;
	playerInput[0].changeWeapon = Keyboard::R;
	playerInput[0].turretClockwise = Keyboard::C;
	playerInput[0].turretCounterClockwise = Keyboard::Z;
	playerInput[0].fireTurret = Keyboard::X;
	playerInput[0].jumpCharging = Keyboard::V;
	playerInput[0].thrusterWheelUp = Keyboard::Q;
	// Thruster selecting
	playerInput[0].selectorAxis[0] = Keyboard::Num8;
	playerInput[0].selectorAxis[0] = Keyboard::Num9;
	playerInput[0].selectorAxis[0] = Keyboard::Num6;
	playerInput[0].selectorAxis[0] = Keyboard::Num3;
	playerInput[0].selectorAxis[0] = Keyboard::Num2;
	playerInput[0].selectorAxis[0] = Keyboard::Num1;
	playerInput[0].selectorAxis[0] = Keyboard::Num4;
	playerInput[0].selectorAxis[0] = Keyboard::Num7;

	playerInput[0].boostMovement = Keyboard::Num5;
	
	playerInput[1].source = -2;
	playerInput[1].fire = Keyboard::J;
	playerInput[1].changeWeapon = Keyboard::I;
	playerInput[1].fireTurret = Keyboard::M;

}

void InputManager::update()
{
	Joystick::update();

	for (int i = 0; i < 2; i++)
	{
		// Controller
		if (playerInput[i].source >= 0)
		{
			// Movement
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].moveForward))
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].moveBackwards))
				Player[i].moveBackwards = true;
			else
				Player[i].moveBackwards = false;
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].turnLeft))
				Player[i].turnLeft = true;
			else
				Player[i].turnLeft = false;
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].turnRight))
				Player[i].turnRight = true;
			else
				Player[i].turnRight = false;

			// Analog movement
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::X) > 30.0f)
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::X) < -30.0f)
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::Y) > 30.0f)
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::Y) < -30.0f)
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;

			// Fire
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].fire))
				Player[i].fire = true;
			else
				Player[i].fire = false;
			// Change weapon
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].changeWeapon))
				Player[i].changeWeapon = true;
			else
				Player[i].changeWeapon = false;

			// Turret stuff
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].turretClockwise))
				Player[i].turretClockwise = true;
			else
				Player[i].turretClockwise = false;
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].turretCounterClockwise))
				Player[i].turretCounterClockwise = true;
			else
				Player[i].turretCounterClockwise = false;
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].fireTurret))
				Player[i].fireTurret = true;
			else
				Player[i].fireTurret = false;

			// Jump
			if (Player[i].jumpExecute)
				Player[i].jumpExecute = false;
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].jumpCharging))
			{
				Player[i].jumpCharging = true;
				Player[i].jumpExecute = false;
			}
			if (!Joystick::isButtonPressed(playerInput[i].source, playerInput[i].jumpCharging) && Player[i].jumpCharging == true)
			{
				Player[i].jumpCharging = false;
				Player[i].jumpExecute = true;
			}

			// Thruster wheel
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].thrusterWheelUp))
			{
				if (Player[i].thrusterWheelUp == false)
					for (int j = 0; j < 6; j++)
						Player[i].thrusterOn[j] = false;
				Player[i].thrusterWheelUp = true;
			}
			else
				Player[i].thrusterWheelUp = false;

			if (Player[i].thrusterWheelUp) //////////////////////////// Needs testing to find good values ///////////////////////
			{
				if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::U) > 0)
				{
					if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::R) > 50)
						Player[i].thrusterOn[1] = true;
					else if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::R) < -50)
						Player[i].thrusterOn[5] = true;
					else if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::U) > 50)
						Player[i].thrusterOn[0] = true;
				}
				else if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::U) < 0)
				{
					if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::R) > 50)
						Player[i].thrusterOn[2] = true;
					else if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::R) < -50)
						Player[i].thrusterOn[4] = true;
					else if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::U) < -50)
						Player[i].thrusterOn[3] = true;
				}
			}

			// Boost
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].boostMovement))
			{
				if (Player[i].moveForward)
					Player[i].thrusterOn[3] = true;
				if (Player[i].moveBackwards)
					Player[i].thrusterOn[0] = true;
				if (Player[i].turnLeft)
				{
					Player[i].thrusterOn[1] = true;
					Player[i].thrusterOn[4] = true;
				}
				if (Player[i].turnRight)
				{
					Player[i].thrusterOn[5] = true;
					Player[i].thrusterOn[2] = true;
				}
			}
			else
				for (int j = 0; j < 6; j++)
					Player[i].thrusterOn[j] = false;
		}
		// Keyboard
		else
		{
			// Movement
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].moveForward))
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].moveBackwards))
				Player[i].moveBackwards = true;
			else
				Player[i].moveBackwards = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].turnLeft))
				Player[i].turnLeft = true;
			else
				Player[i].turnLeft = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].turnRight))
				Player[i].turnRight = true;
			else
				Player[i].turnRight = false;

			// Fire
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].fire))
				Player[i].fire = true;
			else
				Player[i].fire = false;

			// Change weapon
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].changeWeapon))
				Player[i].changeWeapon = true;
			else
				Player[i].changeWeapon = false;

			// Turret stuff
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].turretClockwise))
				Player[i].turretClockwise = true;
			else
				Player[i].turretClockwise = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].turretCounterClockwise))
				Player[i].turretCounterClockwise = true;
			else
				Player[i].turretCounterClockwise = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].fireTurret))
				Player[i].fireTurret = true;
			else
				Player[i].fireTurret = false;

			// Jump
			if (Player[i].jumpExecute)
				Player[i].jumpExecute = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].jumpCharging))
			{
				Player[i].jumpCharging = true;
				Player[i].jumpExecute = false;
			}
			if (!Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].jumpCharging) && Player[i].jumpCharging == true)
			{
				Player[i].jumpCharging = false;
				Player[i].jumpExecute = true;
			}

			// Thruster wheel
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].thrusterWheelUp))
			{
				if (Player[i].thrusterWheelUp == false)
					for (int j = 0; j < 6; j++)
						Player[i].thrusterOn[j] = false;
				Player[i].thrusterWheelUp = true;
			}
			else
				Player[i].thrusterWheelUp = false;

			if (Player[i].thrusterWheelUp)
			{
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[0]))
					Player[i].thrusterOn[0] = true;
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[1]))
					Player[i].thrusterOn[1] = true;
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[2]))
				{
					Player[i].thrusterOn[1] = true;
					Player[i].thrusterOn[2] = true;
				}
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[3]))
					Player[i].thrusterOn[2] = true;
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[4]))
					Player[i].thrusterOn[3] = true;
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[5]))
					Player[i].thrusterOn[4] = true;
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[6]))
				{
					Player[i].thrusterOn[4] = true;
					Player[i].thrusterOn[5] = true;
				}
				if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].selectorAxis[7]))
					Player[i].thrusterOn[5] = true;
			}

			// Boost
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].boostMovement))
			{
				if (Player[i].moveForward)
					Player[i].thrusterOn[3] = true;
				if (Player[i].moveBackwards)
					Player[i].thrusterOn[0] = true;
				if (Player[i].turnLeft)
				{
					Player[i].thrusterOn[1] = true;
					Player[i].thrusterOn[4] = true;
				}
				if (Player[i].turnRight)
				{
					Player[i].thrusterOn[5] = true;
					Player[i].thrusterOn[2] = true;
				}
			}
			else
				for (int j = 0; j < 6; j++)
					Player[i].thrusterOn[j] = false;
		}
	}
}
