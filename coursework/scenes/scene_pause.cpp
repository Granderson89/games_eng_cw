#include "scene_pause.h"
#include "system_renderer.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../engine/src/engine.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// List of UI buttons
vector<shared_ptr<Entity>> PauseScene::buttons;
// Index of highlighted button
int PauseScene::highlighted = 0;

void PauseScene::Load() {
	cout << "Pause Load \n";
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
	sf::View view;
	view.reset(FloatRect(0.0f, 0.0f, resolution.x, resolution.y));	// hardcoded values ///////////////////////////////////////////////
	Renderer::getWindow().setView(view);

	if (InputManager::Player[0].confirm) {
		if (highlighted == 0) {
			Engine::ResumeScene();
		}
		if (highlighted == 1) {
			Engine::ChangeScene(&menu);
			level1.UnLoad();
		}
	}
	if (InputManager::Player[0].menuUp) {
		highlighted--;
		if (highlighted < 0) {
			highlighted = buttons.size() - 1;
		}
		HighlightSelected();
	}
	else if (InputManager::Player[0].menuDown) {
		highlighted++;
		if (highlighted > buttons.size() - 1) {
			highlighted = 0;
		}
		HighlightSelected();
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
