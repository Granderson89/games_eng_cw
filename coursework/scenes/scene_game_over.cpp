#include "scene_game_over.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

using namespace std;
using namespace sf;

// List of UI buttons
vector<shared_ptr<Entity>> GameOverScene::buttons;

void GameOverScene::Load() {
	cout << "Game Over Load \n";
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
		string win = "Game Over\nPlayer " + std::to_string(winner) + " wins!";
		auto t = title->addComponent<TextComponent>(win);
		t->SetScale(scale);
	}

	// Rectangle for button in spritesheet
	auto buttonRect = IntRect(0, 0, 410, 140);
	// Play Again button
	{
		shared_ptr<Entity> playAgainBtn = makeEntity();
		auto s = playAgainBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		playAgainBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale / 2.0f));
		auto t = playAgainBtn->addComponent<TextComponent>("\n   Play Again");
		t->SetScale(scale);
		buttons.push_back(playAgainBtn);
	}
	// Return To Main Menu Button
	{
		shared_ptr<Entity> mainMenuBtn = makeEntity();
		auto s = mainMenuBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		mainMenuBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale * 2.0f));
		auto t = mainMenuBtn->addComponent<TextComponent>("\n   Return To Main Menu");
		t->SetScale(scale);
		buttons.push_back(mainMenuBtn);
	}
	// Quit button
	{
		shared_ptr<Entity> quitBtn = makeEntity();
		auto s = quitBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		quitBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width * scale) / 2.0f, buttonRect.height * scale * 3.5f));
		auto t = quitBtn->addComponent<TextComponent>("\n   Quit");
		t->SetScale(scale);
		buttons.push_back(quitBtn);
	}

	HighlightSelected();
	setLoaded(true);
}

void GameOverScene::Update(const double& dt) {
	if (InputManager::Player[0].confirm) {
		if (highlighted == 0) {
			Engine::ChangeScene(&level1);
		}
		if (highlighted == 1) {
			Engine::ChangeScene(&menu);
		}
		if (highlighted == 2) {
			Engine::GetWindow().close();
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

void GameOverScene::HighlightSelected() {
	std::cout << "GameOver highlighted: " << highlighted << std::endl;
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}
