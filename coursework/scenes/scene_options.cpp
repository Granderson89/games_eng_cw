#include "scene_options.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

using namespace std;
using namespace sf;

// List of UI buttons
vector<shared_ptr<Entity>> OptionsScene::buttons;

// Timer stops highlighted from jumping to fast when user pushes up/down
float OptionsScene::timer = 0;

void OptionsScene::Load() {
	cout << "Options Screen Load \n";
	// Index of highlighted button
	highlighted = 0;
	// Clear buttons
	buttons.clear();
	InputManager::Player[0].confirm = false;
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
		auto t = title->addComponent<TextComponent>("Options\n");
		t->SetScale(scale);

	}

	// Rectangle for button in spritesheet
	auto buttonRect = IntRect(0, 0, 410, 140);
	// Graphics button
	{
		shared_ptr<Entity> graphicsBtn = makeEntity();
		auto s = graphicsBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		graphicsBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale / 2.0f));
		auto t = graphicsBtn->addComponent<TextComponent>("\n   Graphics");
		t->SetScale(scale);
		buttons.push_back(graphicsBtn);
	}
	// Controls button
	{
		shared_ptr<Entity> controlsBtn = makeEntity();
		auto s = controlsBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		controlsBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale * 2.0f));
		auto t = controlsBtn->addComponent<TextComponent>("\n   Controls");
		t->SetScale(scale);
		buttons.push_back(controlsBtn);
	}
	// Return To Main Menu Button
	{
		shared_ptr<Entity> mainMenuBtn = makeEntity();
		auto s = mainMenuBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		mainMenuBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale * 3.5f));
		auto t = mainMenuBtn->addComponent<TextComponent>("\n   Return To Main Menu");
		t->SetScale(scale);
		buttons.push_back(mainMenuBtn);
	}
	

	HighlightSelected();
	setLoaded(true);
}

void OptionsScene::Update(const double& dt) {
	// Countdown timer
	timer -= dt;
	if (InputManager::Player[0].confirm) {
		if (highlighted == 0) {
			Engine::ChangeScene(&graphics);
		}
		if (highlighted == 1) {
			Engine::ChangeScene(&controls);
		}
		if (highlighted == 2) {
 			Engine::ChangeScene(&menu);
		}
	}
	// Only change selected if timer has run out
	if (timer <= 0.0f) {
		timer = 0.0f;
		if (InputManager::Player[0].menuUp) {
			timer += 0.5f;
			highlighted--;
			if (highlighted < 0) {
				highlighted = buttons.size() - 1;
			}
			HighlightSelected();
		}
		else if (InputManager::Player[0].menuDown) {
			timer += 0.5f;
			highlighted++;
			if (highlighted > buttons.size() - 1) {
				highlighted = 0;
			}
			HighlightSelected();
		}
	}
	Scene::Update(dt);
}

void OptionsScene::HighlightSelected() {
	std::cout << "Options highlighted: " << highlighted << std::endl;
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}
