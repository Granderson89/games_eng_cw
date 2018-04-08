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
vector<shared_ptr<Entity>> MenuScene::buttons;
// Index of highlighted button
int MenuScene::highlighted = 0;
// Timer stops highlighted from jumping to fast when user pushes up/down
float MenuScene::timer = 0;

void MenuScene::Load() {
  cout << "Menu Load \n";
  im.initialize();
  buttons.clear();
  im.Player[0].confirm = false;
  timer += 0.5f;
  if (!spritesheet.loadFromFile("res/img/futureui1.png")) {
	  cerr << "Failed to load spritesheet!" << endl;
  }
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
	  shared_ptr<Entity> onePlayBtn = makeEntity();
	  auto s = onePlayBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  s->getSprite().setScale(Vector2f(scale, scale));
	  onePlayBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale / 2.0f));
	  auto t = onePlayBtn->addComponent<TextComponent>("\n   One Player");
	  t->SetScale(scale);
	  buttons.push_back(onePlayBtn);
  }
  // Two Player button
  {
	  shared_ptr<Entity> twoPlayBtn = makeEntity();
	  auto s = twoPlayBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  s->getSprite().setScale(Vector2f(scale, scale));
	  twoPlayBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width* scale) / 2.0f, buttonRect.height * scale* 2.0f));
	  auto t = twoPlayBtn->addComponent<TextComponent>("\n   Two Player");
	  t->SetScale(scale);
	  buttons.push_back(twoPlayBtn);
  }
  // Two Player button
  {
	  shared_ptr<Entity> optionsBtn = makeEntity();
	  auto s = optionsBtn->addComponent<SpriteComponent>();
	  s->getSprite().setTexture(spritesheet);
	  s->getSprite().setTextureRect(buttonRect);
	  s->getSprite().setScale(Vector2f(scale, scale));
	  optionsBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale* 3.5f));
	  auto t = optionsBtn->addComponent<TextComponent>("\n   Options");
	  t->SetScale(scale);
	  buttons.push_back(optionsBtn);
  }

  HighlightSelected();
  setLoaded(true);
  cout << "Menu Load Done\n";

}

void MenuScene::Update(const double& dt) {
  // Countdown timer
  timer -= dt;
  
  // Only change selected if timer has run out
  if (timer <= 0.0f) {
	  timer = 0.0f;
	  if (im.Player[0].confirm) {
		  if (highlighted == 0) {
			  timer += 0.5f;
			  Engine::ChangeScene(&level1);
		  }
		  if (highlighted == 2) {
			  timer += 0.5f;
			  Engine::ChangeScene(&options);
		  }
	  }
	  if (im.Player[0].menuUp) {
		  timer += 0.5f;
		  highlighted--;
		  if (highlighted < 0) {
			  highlighted = 0;
		  }
		  HighlightSelected();
	  }
	  else if (im.Player[0].menuDown) {
		  timer += 0.5f;
		  highlighted++;
		  if (highlighted > 2) {
			  highlighted = 2;
		  }
		  HighlightSelected();
	  }
  }
  Scene::Update(dt);
}

void MenuScene::HighlightSelected() {
	std::cout << "Menu highlighted: " << highlighted << std::endl;
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}
