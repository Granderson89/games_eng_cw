#include "scene_pause.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// List of UI buttons
vector<shared_ptr<Entity>> PauseScene::buttons;
// Index of highlighted button
int PauseScene::highlighted = 0;
// Timer stops highlighted from jumping to fast when user pushes up/down
float PauseScene::timer = 0;

void PauseScene::Load() {
  cout << "Pause Load \n";
  buttons.clear();
  InputManager::Player[0].confirm = false;
  timer += 0.5f;
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
  // Title
  {
	  auto title = makeEntity();
	  auto t = title->addComponent<TextComponent>("Some Spaceship Game\nSpacebar to select");
	  t->SetScale(scale);
  }

  // Rectangle for button in spritesheet
  auto buttonRect = IntRect(0, 0, 410, 140);
  // Single Player button
  {
	  shared_ptr<Entity> continueBtn = makeEntity();
	  auto s = continueBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  s->getSprite().setScale(Vector2f(scale, scale));
	  continueBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale / 2.0f));
	  auto t = continueBtn->addComponent<TextComponent>("\n   Continue");
	  t->SetScale(scale);
	  buttons.push_back(continueBtn);
  }
  // Two Player button
  {
	  shared_ptr<Entity> mainMenuBtn = makeEntity();
	  auto s = mainMenuBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  s->getSprite().setScale(Vector2f(scale, scale));
	  mainMenuBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width* scale) / 2.0f, buttonRect.height * scale* 2.0f));
	  auto t = mainMenuBtn->addComponent<TextComponent>("\n   Return to Main Menu");
	  t->SetScale(scale);
	  buttons.push_back(mainMenuBtn);
  }

  HighlightSelected();
  setLoaded(true);
  cout << "Pause Load Done\n";

}

void PauseScene::Update(const double& dt) {
  // Countdown timer
  timer -= dt;
  
  // Only change selected if timer has run out
  if (timer <= 0.0f) {
	  timer = 0.0f;
	  if (InputManager::Player[0].confirm) {
		  if (highlighted == 0) {
			  timer += 0.5f;
			  Engine::ChangeScene(&level1);
		  }
		  if (highlighted == 1) {
			  timer += 0.5f;
			  Engine::ChangeScene(&menu);
		  }
	  }
	  if (InputManager::Player[0].menuUp) {
		  timer += 0.5f;
		  highlighted--;
		  if (highlighted < 0) {
			  highlighted = 0;
		  }
		  HighlightSelected();
	  }
	  else if (InputManager::Player[0].menuDown) {
		  timer += 0.5f;
		  highlighted++;
		  if (highlighted > 1) {
			  highlighted = 1;
		  }
		  HighlightSelected();
	  }
  }
  Scene::Update(dt);
}

void PauseScene::HighlightSelected() {
	std::cout << "Pause highlighted: " << highlighted << std::endl;
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}
