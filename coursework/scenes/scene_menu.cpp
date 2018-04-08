#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

static InputManager im;

Texture spritesheet;
// List of UI buttons
vector<shared_ptr<Entity>> buttons;
// Index of highlighted button
int highlighted = 0;
// Timer stops highlighted from jumping to fast when user pushes up/down
float timer = 0;
// Controller found
bool controller = false;

void MenuScene::Load() {
  im.initialize();
  cout << "Menu Load \n";

  if (!spritesheet.loadFromFile("res/img/futureui1.png")) {
	  cerr << "Failed to load spritesheet!" << endl;
  }

  // Title
  {
	  auto title = makeEntity();
	  auto t = title->addComponent<TextComponent>("Some Spaceship Game\nSpacebar to select");
  }

  // Rectangle for button in spritesheet
  auto buttonRect = IntRect(0, 0, 410, 140);
  // Single Player button
  {
	  shared_ptr<Entity> onePlayBtn = makeEntity();
	  auto s = onePlayBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  onePlayBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height / 2.0f));
	  auto t = onePlayBtn->addComponent<TextComponent>("\n   One Player");
	  buttons.push_back(onePlayBtn);
  }
  // Two Player button
  {
	  shared_ptr<Entity> twoPlayBtn = makeEntity();
	  auto s = twoPlayBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  twoPlayBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height * 2.0f));
	  auto t = twoPlayBtn->addComponent<TextComponent>("\n   Two Player");
	  buttons.push_back(twoPlayBtn);
  }
  // Two Player button
  {
	  shared_ptr<Entity> optionsBtn = makeEntity();
	  auto s = optionsBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  optionsBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height * 3.5f));
	  auto t = optionsBtn->addComponent<TextComponent>("\n   Options");
	  buttons.push_back(optionsBtn);
  }

  // Check for a controller
  controller = ControllerConnected();

  HighlightSelected();
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // Check for a controller
	if (sf::Joystick::isConnected(0)) {
		controller = true;
	}
	else {
		controller = false;
	}

  // Countdown timer
  timer -= dt;
  if (im.Player[0].confirm) {
	  if (highlighted == 0) {
		  Engine::ChangeScene(&level1);
	  }
  }
  // Only change selected if timer has run out
  if (timer <= 0.0f) {
	  timer = 0.0f;
	  if (im.Player[0].menuUp) {
		  timer += 0.5f;
		  highlighted--;
		  if (highlighted < 0) {
			  highlighted = 0;
		  }
		  else if (highlighted == 1 && !controller) {
			  highlighted--;
		  }
		  HighlightSelected();
	  }
	  else if (im.Player[0].menuDown) {
		  timer += 0.5f;
		  highlighted++;
		  if (highlighted > 2) {
			  highlighted = 2;
		  }
		  else if (highlighted == 1 && !controller) {
			  highlighted++;
		  }
		  HighlightSelected();
	  }
  }
  Scene::Update(dt);
}

void MenuScene::HighlightSelected() {
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}

bool MenuScene::ControllerConnected()
{
	// Check controller is connected
	if (sf::Joystick::isConnected(0)) {
		std::cout << "Controller connected" << std::endl;
		// Check how many buttons it has
		unsigned int buttonCount = sf::Joystick::getButtonCount(0);
		std::cout << "Controller has " << buttonCount << " buttons" << std::endl;
		// Check if it has a z axis
		bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);
		std::cout << "Controller has a z axis" << std::endl;
		return true;
	}
	else {
		return false;
	}
}
