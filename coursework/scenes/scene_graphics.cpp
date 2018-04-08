#include "scene_graphics.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"

using namespace std;
using namespace sf;

static InputManager im;

// List of UI buttons
vector<shared_ptr<Entity>> GraphicsScene::buttons;

// Timer stops highlighted from jumping to fast when user pushes up/down
float GraphicsScene::timer = 0;

void GraphicsScene::Load() {
	cout << "Graphics Screen Load \n";
	// Index of highlighted button
	highlighted = 0;
	// Clear buttons
	buttons.clear();
	im.Player[0].confirm = false;

	// Title
	{
		auto title = makeEntity();
		title->addComponent<TextComponent>("Graphics\n");
	}

	// Rectangle for button in spritesheet
	auto buttonRect = IntRect(0, 0, 410, 140);
	// Graphics button
	{
		shared_ptr<Entity> graphicsBtn = makeEntity();
		auto s = graphicsBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		graphicsBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height / 2.0f));
		auto t = graphicsBtn->addComponent<TextComponent>("\n   Graphics");
		buttons.push_back(graphicsBtn);
	}
	// Back button
	{
		shared_ptr<Entity> backBtn = makeEntity();
		auto s = backBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		backBtn->setPosition(Vector2f((Engine::getWindowSize().x - buttonRect.width) / 2.0f, buttonRect.height * 2.0f));
		auto t = backBtn->addComponent<TextComponent>("\n   Back");
		buttons.push_back(backBtn);
	}
	
	HighlightSelected();
	setLoaded(true);
}

void GraphicsScene::Update(const double& dt) {
	// Countdown timer
	timer -= dt;
	if (im.Player[0].confirm) {
		if (highlighted == 0) {
			Engine::ChangeScene(&options);
		}
		if (highlighted == 1) {
			Engine::ChangeScene(&options);
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
			if (highlighted > 1) {
				highlighted = 1;
			}
			HighlightSelected();
		}
	}
	Scene::Update(dt);
}

void GraphicsScene::HighlightSelected() {
	std::cout << "Graphics highlighted: " << highlighted << std::endl;
	for (int i = 0; i < buttons.size(); i++) {
		if (i == highlighted) {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->Highlight();
		}
		else {
			buttons.at(i)->GetCompatibleComponent<TextComponent>().at(0)->NoHighlight();
		}
	}
}
