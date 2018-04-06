#include "scene_game_over.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

using namespace std;
using namespace sf;

static InputManager im;

// List of UI buttons
vector<shared_ptr<Entity>> GameOverScene::buttons;

// Timer stops highlighted from jumping to fast when user pushes up/down
float GameOverScene::timer = 0;

void GameOverScene::Load() {
	cout << "Game Over Load \n";
	// Index of highlighted button
	highlighted = 0;
	// Clear buttons
	buttons.clear();
	im.initialize();

	// Title
	{
		auto title = makeEntity();
		string win = "Game Over\nPlayer " + std::to_string(winner) + " wins!";
		auto t = title->addComponent<TextComponent>(win);
	}

	// Rectangle for button in spritesheet
	auto buttonRect = IntRect(0, 0, 410, 140);
	// Play Again button
	{
		shared_ptr<Entity> playAgainBtn = makeEntity();
		auto s = playAgainBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		playAgainBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height / 2.0f));
		auto t = playAgainBtn->addComponent<TextComponent>("\n   Play Again");
		buttons.push_back(playAgainBtn);
	}
	// Return To Main Menu Button
	{
		shared_ptr<Entity> mainMenuBtn = makeEntity();
		auto s = mainMenuBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		mainMenuBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height * 2.0f));
		auto t = mainMenuBtn->addComponent<TextComponent>("\n   Return To Main Menu");
		buttons.push_back(mainMenuBtn);
	}
	// Quit button
	{
		shared_ptr<Entity> quitBtn = makeEntity();
		auto s = quitBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		quitBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height * 3.5f));
		auto t = quitBtn->addComponent<TextComponent>("\n   Quit");
		buttons.push_back(quitBtn);
	}

	HighlightSelected();
	setLoaded(true);
}

void GameOverScene::Update(const double& dt) {
	// Countdown timer
	timer -= dt;
	if (im.Player[0].confirm) {
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
	// Only change selected if timer has run out
	if (timer <= 0.0f) {
		timer = 0.0f;
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
