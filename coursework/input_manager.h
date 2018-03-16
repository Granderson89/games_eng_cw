#pragma once

#include <SFML\Graphics.hpp>

class InputManager
{
private:
	struct actions
	{
		bool moveForward;
		bool moveBackwards;
		bool turnLeft;
		bool turnRight;
		bool fire;
		bool changeWeapon;
		bool turretClockwise;
		bool turretCounterClockwise;
		bool fireTurret;
		bool jumpCharging;
		bool jumpExecute;
		bool thrusterWheelUp;
		bool thrusterOn[6];
		bool boostMovement;
	};
	struct inputs
	{
		// 0 to 7 for respective joystick, <0 for keyboard
		int source;
		// Assigned buttons
		unsigned int moveForward;
		unsigned int moveBackwards;
		unsigned int turnLeft;
		unsigned int turnRight;
		unsigned int fire;
		unsigned int changeWeapon;
		unsigned int turretClockwise;
		unsigned int turretCounterClockwise;
		unsigned int fireTurret;
		unsigned int jumpCharging;
		//unsigned int jumpExecute;
		unsigned int thrusterWheelUp;
		unsigned int selectorAxis[8];	// For selecting thruster using keys, starts North goes clockwise
		//unsigned int thrusterOn[6];
		unsigned int boostMovement;
	};

	static inputs player1Input;
	static inputs player2Input;
public:
	static actions Player1;
	static actions Player2;

	static void initialize();
	static void update();
};