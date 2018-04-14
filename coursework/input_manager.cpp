#include "input_manager.h"
#define stringify( name ) # name

using namespace sf;

InputManager::inputs InputManager::playerInput[2];

InputManager::actions InputManager::Player[2];

Keyboard::Key InputManager::_lastKeyPressed;

const char* InputManager::keyNames[] = 
{
	stringify(A),        ///< The A key
	stringify(B),            ///< The B key
	stringify(C),            ///< The C key
	stringify(D),            ///< The D key
	stringify(E),            ///< The E key
	stringify(F),            ///< The F key
	stringify(G),            ///< The G key
	stringify(H),            ///< The H key
	stringify(I),            ///< The I key
	stringify(J),            ///< The J key
	stringify(K),            ///< The K key
	stringify(L),            ///< The L key
	stringify(M),            ///< The M key
	stringify(N),            ///< The N key
	stringify(O),            ///< The O key
	stringify(P),            ///< The P key
	stringify(Q),            ///< The Q key
	stringify(R),            ///< The R key
	stringify(S),            ///< The S key
	stringify(T),            ///< The T key
	stringify(U),            ///< The U key
	stringify(V),            ///< The V key
	stringify(W),            ///< The W key
	stringify(X),            ///< The X key
	stringify(Y),            ///< The Y key
	stringify(Z),            ///< The Z key
	stringify(Num0),         ///< The 0 key
	stringify(Num1),         ///< The 1 key
	stringify(Num2),         ///< The 2 key
	stringify(Num3),         ///< The 3 key
	stringify(Num4),         ///< The 4 key
	stringify(Num5),         ///< The 5 key
	stringify(Num6),         ///< The 6 key
	stringify(Num7),         ///< The 7 key
	stringify(Num8),         ///< The 8 key
	stringify(Num9),         ///< The 9 key
	stringify(Escape),       ///< The Escape key
	stringify(LControl),     ///< The left Control key
	stringify(LShift),       ///< The left Shift key
	stringify(LAlt),         ///< The left Alt key
	stringify(LSystem),      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
	stringify(RControl),     ///< The right Control key
	stringify(RShift),       ///< The right Shift key
	stringify(RAlt),         ///< The right Alt key
	stringify(RSystem),      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
	stringify(Menu),         ///< The Menu key
	stringify(LBracket),     ///< The [ key
	stringify(RBracket),     ///< The ] key
	stringify(SemiColon),    ///< The ; key
	stringify(Comma),        ///< The , key
	stringify(Period),       ///< The . key
	stringify(Quote),        ///< The ' key
	stringify(Slash),        ///< The / key
	stringify(BackSlash),    ///< The \ key
	stringify(Tilde),        ///< The ~ key
	stringify(Equal),        ///< The = key
	stringify(Dash),         ///< The - key
	stringify(Space),        ///< The Space key
	stringify(Return),       ///< The Return key
	stringify(BackSpace),    ///< The Backspace key
	stringify(Tab),          ///< The Tabulation key
	stringify(PageUp),       ///< The Page up key
	stringify(PageDown),     ///< The Page down key
	stringify(End),          ///< The End key
	stringify(Home),         ///< The Home key
	stringify(Insert),       ///< The Insert key
	stringify(Delete),       ///< The Delete key
	stringify(Add),          ///< The + key
	stringify(Subtract),     ///< The - key
	stringify(Multiply),     ///< The * key
	stringify(Divide),       ///< The / key
	stringify(Left),         ///< Left arrow
	stringify(Right),        ///< Right arrow
	stringify(Up),           ///< Up arrow
	stringify(Down),         ///< Down arrow
	stringify(Numpad0),      ///< The numpad 0 key
	stringify(Numpad1),      ///< The numpad 1 key
	stringify(Numpad2),      ///< The numpad 2 key
	stringify(Numpad3),      ///< The numpad 3 key
	stringify(Numpad4),      ///< The numpad 4 key
	stringify(Numpad5),      ///< The numpad 5 key
	stringify(Numpad6),      ///< The numpad 6 key
	stringify(Numpad7),      ///< The numpad 7 key
	stringify(Numpad8),      ///< The numpad 8 key
	stringify(Numpad9),      ///< The numpad 9 key
	stringify(F1),           ///< The F1 key
	stringify(F2),           ///< The F2 key
	stringify(F3),           ///< The F3 key
	stringify(F4),           ///< The F4 key
	stringify(F5),           ///< The F5 key
	stringify(F6),           ///< The F6 key
	stringify(F7),           ///< The F7 key
	stringify(F8),           ///< The F8 key
	stringify(F9),           ///< The F9 key
	stringify(F10),          ///< The F10 key
	stringify(F11),          ///< The F11 key
	stringify(F12),          ///< The F12 key
	stringify(F13),          ///< The F13 key
	stringify(F14),          ///< The F14 key
	stringify(F15),          ///< The F15 key
	stringify(Pause)
};

std::map<int, const char*> InputManager::buttonNames;

std::map<int, int> InputManager::_lastButtonPressed;


// Sets default controls //////////////////////////////(or loads from file later)
void InputManager::initialize()
{
	buttonNames.insert({ 0, "A" });
	buttonNames.insert({ 1, "B" });
	buttonNames.insert({ 2, "X" });
	buttonNames.insert({ 3, "Y" });
	buttonNames.insert({ 4, "LB" });
	buttonNames.insert({ 5, "RB" });
	buttonNames.insert({ 6, "SELECT" });
	buttonNames.insert({ 7, "START" });
	buttonNames.insert({ 8, "LPRESS" });
	buttonNames.insert({ 9, "RPRESS" });

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

	// Menu input
	playerInput[0].menuUp = Keyboard::Up;
	playerInput[0].menuDown = Keyboard::Down;
	playerInput[0].confirm = Keyboard::Space;
	playerInput[0].pause = Keyboard::P;

	
	
	playerInput[1].source = 0;
	playerInput[1].moveForward = Joystick::Y;
	playerInput[1].moveBackwards = Joystick::Y;
	playerInput[1].turnLeft = Joystick::X;
	playerInput[1].turnRight = Joystick::X;
	playerInput[1].fire = 0;
	playerInput[1].changeWeapon = 1;
	playerInput[1].turretClockwise = Keyboard::C;
	playerInput[1].turretCounterClockwise = Keyboard::Z;
	playerInput[1].fireTurret = 5;
	playerInput[1].jumpCharging = 3;
	playerInput[1].thrusterWheelUp = 4;
	// Thruster selecting
	playerInput[1].selectorAxis[0] = Joystick::U;
	playerInput[1].selectorAxis[0] = Joystick::V;

	playerInput[1].boostMovement = Keyboard::Num5;
	playerInput[1].pause = 7;
	// Menu input
	playerInput[1].menuUp = 3;
	playerInput[1].menuDown = 0;
	playerInput[1].confirm = 1;
	playerInput[1].pause = Keyboard::P;
}

void InputManager::initializeKeyboard(int player)
{
	playerInput[player].moveForward = Keyboard::W;
	playerInput[player].moveBackwards = Keyboard::S;
	playerInput[player].turnLeft = Keyboard::A;
	playerInput[player].turnRight = Keyboard::D;

	playerInput[player].fire = Keyboard::F;
	playerInput[player].changeWeapon = Keyboard::R;
	playerInput[player].turretClockwise = Keyboard::C;
	playerInput[player].turretCounterClockwise = Keyboard::Z;
	playerInput[player].fireTurret = Keyboard::X;
	playerInput[player].jumpCharging = Keyboard::V;
	playerInput[player].thrusterWheelUp = Keyboard::Q;

	// Thruster selecting
	playerInput[player].selectorAxis[0] = Keyboard::Num8;
	playerInput[player].selectorAxis[0] = Keyboard::Num9;
	playerInput[player].selectorAxis[0] = Keyboard::Num6;
	playerInput[player].selectorAxis[0] = Keyboard::Num3;
	playerInput[player].selectorAxis[0] = Keyboard::Num2;
	playerInput[player].selectorAxis[0] = Keyboard::Num1;
	playerInput[player].selectorAxis[0] = Keyboard::Num4;
	playerInput[player].selectorAxis[0] = Keyboard::Num7;

	playerInput[player].boostMovement = Keyboard::Num5;

	// Menu input
	playerInput[player].menuUp = Keyboard::Up;
	playerInput[player].menuDown = Keyboard::Down;
	playerInput[player].confirm = Keyboard::Space;
	playerInput[player].pause = Keyboard::P;
}

void InputManager::initializeController(int player)
{
	playerInput[player].moveForward = Joystick::Y;
	playerInput[player].moveBackwards = Joystick::Y;
	playerInput[player].turnLeft = Joystick::X;
	playerInput[player].turnRight = Joystick::X;
	playerInput[player].fire = 0;
	playerInput[player].changeWeapon = 1;
	playerInput[player].turretClockwise = Joystick::U;
	playerInput[player].turretCounterClockwise = Joystick::U;
	playerInput[player].fireTurret = 5;
	playerInput[player].jumpCharging = 3;
	playerInput[player].thrusterWheelUp = 4;
	// Thruster selecting
	//playerInput[player].selectorAxis[0] = Joystick::U;
	//playerInput[player].selectorAxis[0] = Joystick::V;
	playerInput[player].boostMovement = Keyboard::Num5;
	playerInput[player].pause = 7;
	// Menu input
	playerInput[player].menuUp = 3;
	playerInput[player].menuDown = 0;
	playerInput[player].confirm = 1;
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
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::Y) < -30.0f)
				Player[i].moveForward = true;
			else
				Player[i].moveForward = false;

			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::Y) > 30.0f)
				Player[i].moveBackwards = true;
			else
				Player[i].moveBackwards = false;

			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::X) > 30.0f)
				Player[i].turnRight = true;
			else
				Player[i].turnRight = false;

			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::X) < -30.0f)
				Player[i].turnLeft = true;
			else
				Player[i].turnLeft = false;

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
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::U) < -30.0f)
				Player[i].turretClockwise = true;
			else
				Player[i].turretClockwise = false;
			if (Joystick::getAxisPosition(playerInput[i].source, Joystick::Axis::U) > 30.0f)
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
			// Menu
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].menuUp)) {
				Player[i].menuUp = true;
			}
			else {
				Player[i].menuUp = false;
			}
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].menuDown)) {
				Player[i].menuDown = true;
			}
			else {
				Player[i].menuDown = false;
			}
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].confirm)) {
				Player[i].confirm = true;
			}
			else {
				Player[i].confirm = false;
			}
			// Pause
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].pause))
				Player[i].pause = true;
			else
				Player[i].pause = false;

			// Pause
			if (Joystick::isButtonPressed(playerInput[i].source, playerInput[i].pause))
				Player[i].pause = true;
			else
				Player[i].pause = false;
		}
		// Keyboard
		else if (playerInput[i].source == -1)
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
			
			// Menu
			static bool mup = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].menuUp))
			{
				if (!mup)
					Player[i].menuUp = true;
				else
					Player[i].menuUp = false;
				mup = true;
			}
			else
			{
				mup = false;
				Player[i].menuUp = false;
			}
			static bool mdown = false;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].menuDown))
			{
				if (!mdown)
					Player[i].menuDown = true;
				else
					Player[i].menuDown = false;
				mdown = true;
			}
			else
			{
				mdown = false;
				Player[i].menuDown = false;
			}
			static bool mconf;
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].confirm))
			{
				if (!mconf)
					Player[i].confirm = true;
				else
					Player[i].confirm = false;
				mconf = true;
			}
			else
			{
				mconf = false;
				Player[i].confirm = false;
			}
			// Pause
			if (Keyboard::isKeyPressed((Keyboard::Key)playerInput[i].pause))
				Player[i].pause = true;
			else
				Player[i].pause = false;
		}
	}
}

void InputManager::storeButton(int source, int button)
{
	_lastButtonPressed[source] = button;
}

void InputManager::storeKey(Keyboard::Key key) {
	_lastKeyPressed = key;
}

Keyboard::Key InputManager::getLastKeyPressed()
{
	return _lastKeyPressed;
}

void InputManager::clearLastPressed() {
	_lastKeyPressed = (Keyboard::Key)-1;
}

int InputManager::getLastButtonPressed(int source)
{
	return _lastButtonPressed[source];
}
