#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

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

		// Menu actions
		bool menuUp;
		bool menuDown;
		bool confirm;

		bool pause;
	};
	struct inputs
	{
		// 0 to 7 for respective joystick, <0 for keyboard
		int source;
		// Assigned buttons
		char moveForward;
		int moveBackwards;
		int turnLeft;
		int turnRight;
		int fire;
		int changeWeapon;
		int turretClockwise;
		int turretCounterClockwise;
		int fireTurret;
		int jumpCharging;
		//unsigned int jumpExecute;
		int thrusterWheelUp;
		int selectorAxis[8];	// For selecting thruster using keys, starts North goes clockwise
		//unsigned int thrusterOn[6];
		int boostMovement;

		// Menu inputs
		int menuUp;
		int menuDown;
		int confirm;

		int pause;
	};

	
public:
	static actions Player[2];
	//static actions Player2;
	static inputs playerInput[2];
	//static inputs player2Input;

	// Last key pressed
	static Keyboard::Key _lastKeyPressed;
	// String names of the keys
	static const char* keyNames[];

	// Last button pressed
	static std::map<int, int> _lastButtonPressed;
	// String names of the buttons
	static std::map<int, const char*> buttonNames;

	static void initialize();
	static void initializeKeyboard(int player);
	static void initializeController(int player);
	static void update(Keyboard::Key);
	static void update(int, int);
	static void update();

	static Keyboard::Key getLastKeyPressed();
	static void clearLastPressed();
	static int getLastButtonPressed(int);
};