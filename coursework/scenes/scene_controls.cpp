#include "scene_controls.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

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
	im.Player[0].confirm = false;
	im.Player[1].confirm = false;
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

void ControlsScene::Update(const double& dt) {
	// Countdown timer
	timer -= dt;
	if (changeControl == NONE) {
		// Only change selected if timer has run out
		if (timer <= 0.0f) {
			timer = 0.0f;
			// Move selection up
			if (im.Player[0].menuUp ||
				im.Player[1].menuUp) {
				timer += 0.5f;
				highlighted = (selection)((int)highlighted - 1);
				if (highlighted < 0) {
					highlighted = (selection)(buttons.size() - 1);
				}
				HighlightSelected();
			}
			// Move selection down
			else if (im.Player[0].menuDown ||
				im.Player[1].menuDown) {
				timer += 0.5f;
				highlighted = (selection)((int)highlighted + 1);
				if (highlighted > buttons.size() - 1) {
					highlighted = (selection)0;
				}
				HighlightSelected();
			}
			// Confirm selection
			else if (im.Player[0].confirm ||
				im.Player[1].confirm) {
				im.Player[0].confirm = false;
				im.Player[1].confirm = false;
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
				if (im.playerInput[0].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[0].confirm) {
						im.playerInput[0].fire = im.getLastKeyPressed();
						controls.at(0)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[0].fire]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[0].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[0].source) != im.playerInput[0].confirm) {
						im.playerInput[0].fire = im.getLastButtonPressed(im.playerInput[0].source);
						controls.at(0)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[0].fire));
						changeControl = NONE;
					}
				}
				break;
			case P1_CHANGE_WEAPON:
				if (im.playerInput[0].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[0].confirm) {
						im.playerInput[0].changeWeapon = im.getLastKeyPressed();
						controls.at(1)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[0].changeWeapon]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[0].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[0].source) != im.playerInput[0].confirm) {
						im.playerInput[0].changeWeapon = im.getLastButtonPressed(im.playerInput[0].source);
						controls.at(1)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[0].changeWeapon));
						changeControl = NONE;
					}
				}
				break;
			case P1_FIRE_TURRET:
				if (im.playerInput[0].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[0].confirm) {
						im.playerInput[0].fireTurret = im.getLastKeyPressed();
						controls.at(2)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[0].fireTurret]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[0].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[0].source) != im.playerInput[0].confirm) {
						im.playerInput[0].fireTurret = im.getLastButtonPressed(im.playerInput[0].source);
						controls.at(2)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[0].fireTurret));
						changeControl = NONE;
					}
				}
				break;
			case P1_CHARGE_JUMP:
				if (im.playerInput[0].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[0].confirm) {
						im.playerInput[0].jumpCharging = im.getLastKeyPressed();
						controls.at(3)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[0].jumpCharging]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[0].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[0].source) != im.playerInput[0].confirm) {
						im.playerInput[0].jumpCharging = im.getLastButtonPressed(im.playerInput[0].source);
						controls.at(3)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[0].jumpCharging));
						changeControl = NONE;
					}
				}
				break;
				// Player 2
			case P2_FIRE:
				if (im.playerInput[1].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[1].confirm) {
						im.playerInput[1].fire = im.getLastKeyPressed();
						controls.at(4)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[1].fire]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[1].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[1].source) != im.playerInput[1].confirm) {
						im.playerInput[1].fire = im.getLastButtonPressed(im.playerInput[1].source);
						controls.at(4)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[1].fire));
						changeControl = NONE;
					}
				}
				break;
			case P2_CHANGE_WEAPON:
				if (im.playerInput[1].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[1].confirm) {
						im.playerInput[1].changeWeapon = im.getLastKeyPressed();
						controls.at(5)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[1].changeWeapon]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[1].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[1].source) != im.playerInput[1].confirm) {
						im.playerInput[1].changeWeapon = im.getLastButtonPressed(im.playerInput[1].source);
						controls.at(5)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[1].changeWeapon));
						changeControl = NONE;
					}
				}
				break;
			case P2_FIRE_TURRET:
				if (im.playerInput[1].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[1].confirm) {
						im.playerInput[1].fireTurret = im.getLastKeyPressed();
						controls.at(6)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[1].fireTurret]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[1].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[1].source) != im.playerInput[1].confirm) {
						im.playerInput[1].fireTurret = im.getLastButtonPressed(im.playerInput[1].source);
						controls.at(6)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[1].fireTurret));
						changeControl = NONE;
					}
				}
				break;
			case P2_CHARGE_JUMP:
				if (im.playerInput[1].source == -1) {
					if (im.getLastKeyPressed() != -1 &&
						im.getLastKeyPressed() != im.playerInput[1].confirm) {
						im.playerInput[1].jumpCharging = im.getLastKeyPressed();
						controls.at(7)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.keyNames[im.playerInput[1].jumpCharging]);
						changeControl = NONE;
					}
				}
				else {
					if (im.getLastButtonPressed(im.playerInput[1].source) != -1 &&
						im.getLastButtonPressed(im.playerInput[1].source) != im.playerInput[1].confirm) {
						im.playerInput[1].jumpCharging = im.getLastButtonPressed(im.playerInput[1].source);
						controls.at(7)->GetCompatibleComponent<TextComponent>().at(0)->SetText(im.buttonNames.at(im.playerInput[1].jumpCharging));
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
	bool c1Free = im.playerInput[opponent].source != 0;
	std::cout << "C1 Free: " << c1Free << std::endl;
	bool c2Available = MenuScene::ControllerConnected(1);
	std::cout << "C2 Available: " << c2Available << std::endl;
	bool c2Free = im.playerInput[opponent].source != 1;
	std::cout << "C2 Free: " << c2Free << std::endl;
	// Check if keyboard is free
	bool kFree = im.playerInput[opponent].source >= 0;
	std::cout << "K Free: " << kFree << std::endl;

	// If currently set to keyboard
	if (im.playerInput[player].source < 0) {
		// If controller 1 is available and free
		if (c1Available && c1Free) {
			// Set player's source to controller 1
			im.playerInput[player].source = 0;
			im.initializeController(player);
			std::cout << im.buttonNames.at(im.playerInput[player].fire) << std::endl;
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + " - Controller " + to_string(im.playerInput[player].source) + "\n");
			UpdateControls(player, im.buttonNames.at(im.playerInput[player].fire), im.buttonNames.at(im.playerInput[player].changeWeapon),
				im.buttonNames.at(im.playerInput[player].fireTurret), im.buttonNames.at(im.playerInput[player].jumpCharging));
			std::cout << im.buttonNames.at(im.playerInput[player].fire) << std::endl;

		}
		// Else if controller 2 is available and free
		else if (c2Available && c2Free) {
			// Set player's source to controller 2
			im.playerInput[player].source = 1;
			im.initializeController(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + "  - Controller " + to_string(im.playerInput[player].source) + "\n");
		}
	}
	// If currently set to controller 0
	else if (im.playerInput[player].source == 0) {
		// If controller 2 is available and free
		if (c2Available && c2Free) {
			// Set player's source to controller 2
			im.playerInput[player].source = 1;
			im.initializeController(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + "  - Controller " + to_string(im.playerInput[player].source) + "\n");
		}
		// Else if keyboard is free
		else if (kFree) {
			// Set player's source to keyboard
			im.playerInput[player].source = -1;
			im.initializeKeyboard(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + " - Keyboard " + to_string(im.playerInput[player].source) + "\n");
			UpdateControls(player, im.keyNames[im.playerInput[player].fire], im.keyNames[im.playerInput[player].changeWeapon],
				im.keyNames[im.playerInput[player].fireTurret], im.keyNames[im.playerInput[player].jumpCharging]);
		}
	}
	// If currently set to controller 1
	else if (im.playerInput[player].source == 1) {
		// If controller 1 is available and free
		if (c1Available && c1Free) {
			// Set player's source to controller 1
			im.playerInput[player].source = 0;
			im.initializeController(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + "  - Controller " + to_string(im.playerInput[player].source) + "\n");
		}
		// Else if keyboard is free
		else if (kFree) {
			// Set player's source to keyboard
			im.playerInput[player].source = -1;
			im.initializeKeyboard(player);
			controllerNames.at(player)->GetCompatibleComponent<TextComponent>().at(0)->
				SetText("Player " + to_string(player + 1) + " - Keyboard " + to_string(im.playerInput[player].source) + "\n");
			UpdateControls(player, im.keyNames[im.playerInput[player].fire], im.keyNames[im.playerInput[player].changeWeapon],
				im.keyNames[im.playerInput[player].fireTurret], im.keyNames[im.playerInput[player].jumpCharging]);
		}
	}
}

// Update the GUI with players controls
void ControlsScene::UpdateControls(int player, const char* fire, const char* changeWeapon, const char* fireTurret, const char* jumpCharging) {
	if (im.playerInput[player].source == -1) {
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
	if (im.playerInput[player].source == -1) {
		playerSource = "Player " + to_string(player + 1) + " - Keyboard\n";
		// Fire control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 2.0f), scale, im.keyNames[im.playerInput[player].fire]);
		// Change weapon control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 3.5f), scale, im.keyNames[im.playerInput[player].changeWeapon]);
		// Fire turret control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 5.0f), scale, im.keyNames[im.playerInput[player].fireTurret]);
		// Charge jump control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f +
			buttonRect.width * scale, buttonRect.height * scale * 6.5f), scale, im.keyNames[im.playerInput[player].jumpCharging]);
	}
	else {
		playerSource = "Player " + to_string(player + 1) + " - Controller " + to_string(im.playerInput[player].source) + "\n";
		// Fire control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 2.0f), scale, im.buttonNames.at(im.playerInput[player].fire));
		// Change weapon control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 3.5f), scale, im.buttonNames.at(im.playerInput[player].changeWeapon));
		// Fire turret control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f + buttonRect.width * scale,
			buttonRect.height * scale * 5.0f), scale, im.buttonNames.at(im.playerInput[player].fireTurret));
		// Charge jump control
		MakeControlBox(Vector2f(player * Engine::getWindowSize().x / 2.0f +
			buttonRect.width * scale, buttonRect.height * scale * 6.5f), scale, im.buttonNames.at(im.playerInput[player].jumpCharging));
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