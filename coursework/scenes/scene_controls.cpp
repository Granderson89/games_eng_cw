#include "scene_controls.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

// List of UI buttons
vector<shared_ptr<Entity>> ControlsScene::controllerNames;
vector<shared_ptr<Entity>> ControlsScene::buttons;
vector<shared_ptr<Entity>> ControlsScene::controls;

selection ControlsScene::highlighted = P1_SOURCE;
selection ControlsScene::changeControl = NONE;

// Timer stops highlighted from jumping to fast when user pushes up/down
float ControlsScene::timer = 0;

void ControlsScene::Load() {
	cout << "Controls Screen Load \n";
	// Index of highlighted button
	highlighted = P1_SOURCE;
	// Clear buttons
	buttons.clear();
	InputManager::Player[0].confirm = false;
	InputManager::Player[1].confirm = false;
	timer += 1.0f;
	// Work out scale
	float scale = 1.0f;
	switch (resolution.x)
	{
	case 1920:
		scale = 1.0f;
		break;
	case 1280:
		scale = 0.667f;
		break;
	case 640:
		scale = 0.333f;
		break;
	default:
		scale = 1.0f;
		break;
	}

	// Rectangle for button in spritesheet
	auto buttonRect = IntRect(0, 0, 410, 140);

	// Player 1
	createPlayerButtons(0, scale, buttonRect);

	// Player 2
	createPlayerButtons(1, scale, buttonRect);

	// Back button
	MakeButton(Vector2f(Engine::getWindowSize().x - buttonRect.width* scale, Engine::getWindowSize().y - buttonRect.height), scale, buttonRect, "\n   Back");
	HighlightSelected();

	setLoaded(true);
}

void ControlsScene::UnLoad() {
	ofstream saveFile;
	saveFile.open("controlsPrefs.txt");
	saveFile << InputManager::playerInput[0].source << "\n";
	saveFile << InputManager::playerInput[0].fire << "\n";
	saveFile << InputManager::playerInput[0].changeWeapon << "\n";
	saveFile << InputManager::playerInput[0].fireTurret << "\n";
	saveFile << InputManager::playerInput[0].jumpCharging << "\n";
	saveFile << InputManager::playerInput[0].confirm << "\n";

	saveFile << InputManager::playerInput[1].source << "\n";
	saveFile << InputManager::playerInput[1].fire << "\n";
	saveFile << InputManager::playerInput[1].changeWeapon << "\n";
	saveFile << InputManager::playerInput[1].fireTurret << "\n";
	saveFile << InputManager::playerInput[1].jumpCharging << "\n";
	saveFile << InputManager::playerInput[1].confirm << "\n";

	saveFile.close();
	Scene::UnLoad();
}

void ControlsScene::Update(const double& dt) {
	// Countdown timer
	timer -= dt;
	if (changeControl == NONE) {
		// Only change selected if timer has run out
		if (timer <= 0.0f) {
			timer = 0.0f;
			// Move selection up
			if (InputManager::Player[0].menuUp ||
				InputManager::Player[1].menuUp) {
				timer += 0.5f;
				highlighted = (selection)((int)highlighted - 1);
				if (highlighted < 0) {
					highlighted = (selection)(buttons.size() - 1);
				}
				HighlightSelected();
			}
			// Move selection down
			else if (InputManager::Player[0].menuDown ||
				InputManager::Player[1].menuDown) {
				timer += 0.5f;
				highlighted = (selection)((int)highlighted + 1);
				if (highlighted > buttons.size() - 1) {
					highlighted = (selection)0;
				}
				HighlightSelected();
			}
			// Confirm selection
			else if (InputManager::Player[0].confirm ||
				InputManager::Player[1].confirm) {
				InputManager::Player[0].confirm = false;
				InputManager::Player[1].confirm = false;
				timer += 0.5f;
				// Perform functions
				switch (highlighted) {
					// Player 1
				case P1_SOURCE:
					SwapSource(0);
					break;
				case P1_FIRE:
					changeControl = highlighted;
					break;
				case P1_CHANGE_WEAPON:
					changeControl = highlighted;
					break;
				case P1_FIRE_TURRET:
					changeControl = highlighted;
					break;
				case P1_CHARGE_JUMP:
					changeControl = highlighted;
					break;
					// Player 2
				case P2_SOURCE:
					SwapSource(1);
					break;
				case P2_FIRE:
					changeControl = highlighted;
					break;
				case P2_CHANGE_WEAPON:
					changeControl = highlighted;
					break;
				case P2_FIRE_TURRET:
					changeControl = highlighted;
					break;
				case P2_CHARGE_JUMP:
					changeControl = highlighted;
					break;
				case BACK:
					Engine::ChangeScene(&options);
					break;
				default:
					break;
				}
			}
		}
	}
	else {
		if (timer <= 0.0f) {
			timer = 0.0f;
			switch (changeControl) {
				// Player 1
			case P1_FIRE:
				if (InputManager::playerInput[0].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].fire = InputManager::getLastKeyPressed();
						controls.at(0)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[0].fire]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].fire = InputManager::getLastButtonPressed(InputManager::playerInput[0].source);
						controls.at(0)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[0].fire));
						changeControl = NONE;
					}
				}
				break;
			case P1_CHANGE_WEAPON:
				if (InputManager::playerInput[0].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].changeWeapon = InputManager::getLastKeyPressed();
						controls.at(1)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[0].changeWeapon]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].changeWeapon = InputManager::getLastButtonPressed(InputManager::playerInput[0].source);
						controls.at(1)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[0].changeWeapon));
						changeControl = NONE;
					}
				}
				break;
			case P1_FIRE_TURRET:
				if (InputManager::playerInput[0].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].fireTurret = InputManager::getLastKeyPressed();
						controls.at(2)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[0].fireTurret]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].fireTurret = InputManager::getLastButtonPressed(InputManager::playerInput[0].source);
						controls.at(2)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[0].fireTurret));
						changeControl = NONE;
					}
				}
				break;
			case P1_CHARGE_JUMP:
				if (InputManager::playerInput[0].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].jumpCharging = InputManager::getLastKeyPressed();
						controls.at(3)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[0].jumpCharging]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[0].source) != InputManager::playerInput[0].confirm) {
						InputManager::playerInput[0].jumpCharging = InputManager::getLastButtonPressed(InputManager::playerInput[0].source);
						controls.at(3)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[0].jumpCharging));
						changeControl = NONE;
					}
				}
				break;
				// Player 2
			case P2_FIRE:
				if (InputManager::playerInput[1].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].fire = InputManager::getLastKeyPressed();
						controls.at(4)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[1].fire]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].fire = InputManager::getLastButtonPressed(InputManager::playerInput[1].source);
						controls.at(4)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[1].fire));
						changeControl = NONE;
					}
				}
				break;
			case P2_CHANGE_WEAPON:
				if (InputManager::playerInput[1].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].changeWeapon = InputManager::getLastKeyPressed();
						controls.at(5)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[1].changeWeapon]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].changeWeapon = InputManager::getLastButtonPressed(InputManager::playerInput[1].source);
						controls.at(5)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[1].changeWeapon));
						changeControl = NONE;
					}
				}
				break;
			case P2_FIRE_TURRET:
				if (InputManager::playerInput[1].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].fireTurret = InputManager::getLastKeyPressed();
						controls.at(6)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[1].fireTurret]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].fireTurret = InputManager::getLastButtonPressed(InputManager::playerInput[1].source);
						controls.at(6)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[1].fireTurret));
						changeControl = NONE;
					}
				}
				break;
			case P2_CHARGE_JUMP:
				if (InputManager::playerInput[1].source == -1) {
					if (InputManager::getLastKeyPressed() != -1 &&
						InputManager::getLastKeyPressed() != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].jumpCharging = InputManager::getLastKeyPressed();
						controls.at(7)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::keyNames[InputManager::playerInput[1].jumpCharging]);
						changeControl = NONE;
					}
				}
				else {
					if (InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != -1 &&
						InputManager::getLastButtonPressed(InputManager::playerInput[1].source) != InputManager::playerInput[1].confirm) {
						InputManager::playerInput[1].jumpCharging = InputManager::getLastButtonPressed(InputManager::playerInput[1].source);
						controls.at(7)->GetCompatibleComponent<TextComponent>().at(0)->SetText(InputManager::buttonNames.at(InputManager::playerInput[1].jumpCharging));
						changeControl = NONE;
					}
				}
				break;
			default:
				break;
			}

		}
	}
	Scene::Update(dt);
}

void ControlsScene::HighlightSelected() {
	std::cout << "Controls highlighted: " << highlighted << std::endl;
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}

void ControlsScene::MakeButton(Vector2f position, float scale, IntRect buttonRect, string text) {
	shared_ptr<Entity> button = makeEntity();
	auto s = button->addComponent<SpriteComponent>();
	s->getSprite().setTexture(spritesheet);
	s->getSprite().setTextureRect(buttonRect);
	s->getSprite().setScale(Vector2f(scale, scale));
	button->setPosition(position);
	auto t = button->addComponent<TextComponent>(text);
	t->SetScale(scale);
	buttons.push_back(button);
}

void ControlsScene::MakeControllerName(Vector2f position, float scale, string text) {
	auto name = makeEntity();
	auto t = name->addComponent<TextComponent>(text);
	t->SetPosition(position);
	t->SetScale(scale);
	controllerNames.push_back(name);
}

void ControlsScene::MakeControlBox(Vector2f position, float scale, const char* button) {
	auto control = makeEntity();
	auto t = control->addComponent<TextComponent>(button);
	t->SetPosition(position);
	t->SetScale(scale);
	controls.push_back(control);
}

void ControlsScene::SwapSource(int player) {
	// Get opponent
	int opponent;
	if (player == 0)
		opponent = 1;
	else
		opponent = 0;

	// Check availability of controllers and keyboard
	bool c1Available = MenuScene::ControllerConnected(0);
	std::cout << "C1 Available: " << c1Available << std::endl;
	bool c1Free = InputManager::playerInput[opponent].source != 0;
	std::cout << "C1 Free: " << c1Free << std::endl;
	bool c2Available = MenuScene::ControllerConnected(1);
	std::cout << "C2 Available: " << c2Available << std::endl;
	bool c2Free = InputManager::playerInput[opponent].source != 1;
	std::cout << "C2 Free: " << c2Free << std::endl;
	// Check if keyboard is free
	bool kFree = InputManager::playerInput[opponent].source >= 0;
	std::cout << "K Free: " << kFree << std::endl;

	// If currently set to keyboard
	if (InputManager::playerInput[player].source < 0) {
		// If controller 1 is available and free
		if (c1Available && c1Free) {
			// Set player's source to controller 1
			InputManager::playerInput[player].source = 0;
			InputManager::initializeController(player);
			std::cout << InputManager::buttonNames.at(InputManager::playerInput[player].fire) << std::endl;
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + " - Controller " + to_string(InputManager::playerInput[player].source) + "\n");
			UpdateControls(player, InputManager::buttonNames.at(InputManager::playerInput[player].fire), InputManager::buttonNames.at(InputManager::playerInput[player].changeWeapon),
				InputManager::buttonNames.at(InputManager::playerInput[player].fireTurret), InputManager::buttonNames.at(InputManager::playerInput[player].jumpCharging));
			std::cout << InputManager::buttonNames.at(InputManager::playerInput[player].fire) << std::endl;

		}
		// Else if controller 2 is available and free
		else if (c2Available && c2Free) {
			// Set player's source to controller 2
			InputManager::playerInput[player].source = 1;
			InputManager::initializeController(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + "  - Controller " + to_string(InputManager::playerInput[player].source) + "\n");
		}
	}
	// If currently set to controller 0
	else if (InputManager::playerInput[player].source == 0) {
		// If controller 2 is available and free
		if (c2Available && c2Free) {
			// Set player's source to controller 2
			InputManager::playerInput[player].source = 1;
			InputManager::initializeController(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + "  - Controller " + to_string(InputManager::playerInput[player].source) + "\n");
		}
		// Else if keyboard is free
		else if (kFree) {
			// Set player's source to keyboard
			InputManager::playerInput[player].source = -1;
			InputManager::initializeKeyboard(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + " - Keyboard " + to_string(InputManager::playerInput[player].source) + "\n");
			UpdateControls(player, InputManager::keyNames[InputManager::playerInput[player].fire], InputManager::keyNames[InputManager::playerInput[player].changeWeapon],
				InputManager::keyNames[InputManager::playerInput[player].fireTurret], InputManager::keyNames[InputManager::playerInput[player].jumpCharging]);
		}
	}
	// If currently set to controller 1
	else if (InputManager::playerInput[player].source == 1) {
		// If controller 1 is available and free
		if (c1Available && c1Free) {
			// Set player's source to controller 1
			InputManager::playerInput[player].source = 0;
			InputManager::initializeController(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + "  - Controller " + to_string(InputManager::playerInput[player].source) + "\n");
		}
		// Else if keyboard is free
		else if (kFree) {
			// Set player's source to keyboard
			InputManager::playerInput[player].source = -1;
			InputManager::initializeKeyboard(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + " - Keyboard " + to_string(InputManager::playerInput[player].source) + "\n");
			UpdateControls(player, InputManager::keyNames[InputManager::playerInput[player].fire], InputManager::keyNames[InputManager::playerInput[player].changeWeapon],
				InputManager::keyNames[InputManager::playerInput[player].fireTurret], InputManager::keyNames[InputManager::playerInput[player].jumpCharging]);
		}
	}
}

// Update the GUI with players controls
void ControlsScene::UpdateControls(int player, const char* fire, const char* changeWeapon, const char* fireTurret, const char* jumpCharging) {
	if (InputManager::playerInput[player].source == -1) {
		controls.at(0 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(fire);
		controls.at(1 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(changeWeapon);
		controls.at(2 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(fireTurret);
		controls.at(3 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(jumpCharging);
	}
	else {
		controls.at(0 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(fire);
		controls.at(1 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(changeWeapon);
		controls.at(2 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(fireTurret);
		controls.at(3 + (4 * player))->GetCompatibleComponent<TextComponent>().at(0)->
			SetText(jumpCharging);
	}
}

// Create control buttons for a player
void ControlsScene::createPlayerButtons(int player, float scale, IntRect buttonRect)
{
	string playerSource;
	if (InputManager::playerInput[player].source == -1) {
		playerSource = "Player " + to_string(player + 1) + " - Keyboard\n";
		// Fire control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 2.0f), scale, InputManager::keyNames[InputManager::playerInput[player].fire]);
		// Change weapon control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 3.5f), scale, InputManager::keyNames[InputManager::playerInput[player].changeWeapon]);
		// Fire turret control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 5.0f), scale, InputManager::keyNames[InputManager::playerInput[player].fireTurret]);
		// Charge jump control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f +
			buttonRect.width * scale, buttonRect.height * scale * 6.5f), scale, InputManager::keyNames[InputManager::playerInput[player].jumpCharging]);
	}
	else {
		playerSource = "Player " + to_string(player + 1) + " - Controller " + to_string(InputManager::playerInput[player].source) + "\n";
		// Fire control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 2.0f), scale, InputManager::buttonNames.at(InputManager::playerInput[player].fire));
		// Change weapon control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 3.5f), scale, InputManager::buttonNames.at(InputManager::playerInput[player].changeWeapon));
		// Fire turret control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 5.0f), scale, InputManager::buttonNames.at(InputManager::playerInput[player].fireTurret));
		// Charge jump control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f +
			buttonRect.width * scale, buttonRect.height * scale * 6.5f), scale, InputManager::buttonNames.at(InputManager::playerInput[player].jumpCharging));
	}
	// Source button
	MakeButton(Vector2f(player * Engine::getWindowSize().x / 2.0f, buttonRect.height * scale / 2.0f),
		scale, buttonRect, "\n   Swap");
	MakeControllerName(Vector2f(player * Engine::getWindowSize().x / 2.0f, 0.0f),
		scale, playerSource);
	// Fire button
	MakeButton(Vector2f(player * Engine::getWindowSize().x / 2.0f,
		buttonRect.height * scale * 2.0f), scale, buttonRect, "\n   Fire");
	// Change weapon button
	MakeButton(Vector2f(player * Engine::getWindowSize().x / 2.0f,
		buttonRect.height * scale * 3.5f), scale, buttonRect, "\n   Change Weapon");
	// Fire turret button
	MakeButton(Vector2f(player * Engine::getWindowSize().x / 2.0f,
		buttonRect.height * scale * 5.0f), scale, buttonRect, "\n   Fire Turret");
	// Charge jump button
	MakeButton(Vector2f(player * Engine::getWindowSize().x / 2.0f,
		buttonRect.height * scale * 6.5f), scale, buttonRect, "\n   Charge Jump");
}

void ControlsScene::readPrefs() {
	string line;
	ifstream prefs("controlsPrefs.txt");
	if (prefs.is_open()) {
		// Player 1
		{
			// Source
			getline(prefs, line);
			int source = stoi(line);
			InputManager::playerInput[0].source = source;
			if (source < 0)
				InputManager::initializeKeyboard(source);
			else
				InputManager::initializeController(source);
			// Fire
			getline(prefs, line);
			int fire = stoi(line);
			InputManager::playerInput[0].fire = fire;
			// Change weapon
			getline(prefs, line);
			int changeWeapon = stoi(line);
			InputManager::playerInput[0].changeWeapon = changeWeapon;
			// Fire turret
			getline(prefs, line);
			int fireTurret = stoi(line);
			InputManager::playerInput[0].fireTurret = fireTurret;
			// Jump charging
			getline(prefs, line);
			int jumpCharging = stoi(line);
			InputManager::playerInput[0].jumpCharging = jumpCharging;
			// Confirm
			getline(prefs, line);
			int confirm = stoi(line);
			InputManager::playerInput[0].confirm = confirm;
		}

		// Player 2
		{
			// Source
			getline(prefs, line);
			int source = stoi(line);
			InputManager::playerInput[1].source = source;
			if (source < 0)
				InputManager::initializeKeyboard(source);
			else
				InputManager::initializeController(source);
			// Fire
			getline(prefs, line);
			int fire = stoi(line);
			InputManager::playerInput[1].fire = fire;
			// Change weapon
			getline(prefs, line);
			int changeWeapon = stoi(line);
			InputManager::playerInput[1].changeWeapon = changeWeapon;
			// Fire turret
			getline(prefs, line);
			int fireTurret = stoi(line);
			InputManager::playerInput[1].fireTurret = fireTurret;
			// Jump charging
			getline(prefs, line);
			int jumpCharging = stoi(line);
			InputManager::playerInput[1].jumpCharging = jumpCharging;
			// Confirm
			getline(prefs, line);
			int confirm = stoi(line);
			InputManager::playerInput[1].confirm = confirm;
		}
		prefs.close();
	}
	else 
		cout << "Unable to open file\n";
}
