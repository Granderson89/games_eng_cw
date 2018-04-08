#include "scene_graphics.h"
#include "system_renderer.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_camera.h"
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
		auto t = title->addComponent<TextComponent>("Graphics\n");
		t->SetScale(scale);
	}

	// Rectangle for button in spritesheet
	auto buttonRect = IntRect(0, 0, 410, 140);
	
	// Low button
	{
		shared_ptr<Entity> lowBtn = makeEntity();
		auto s = lowBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		lowBtn->setPosition(Vector2f((Engine::getWindowSize().x - 2.0f * buttonRect.width * scale) / 2.0f, buttonRect.height * scale / 2.0f));
		auto t = lowBtn->addComponent<TextComponent>("\n   640 x 360");
		t->SetScale(scale);
		buttons.push_back(lowBtn);
	}
	// HDR button
	{
		shared_ptr<Entity> hdrBtn = makeEntity();
		auto s = hdrBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		hdrBtn->setPosition(Vector2f((Engine::getWindowSize().x - 2.0f * buttonRect.width* scale) / 2.0f, buttonRect.height * scale* 2.0f));
		auto t = hdrBtn->addComponent<TextComponent>("\n   1280 x 720");
		t->SetScale(scale);
		buttons.push_back(hdrBtn);
	}
	// Full HD button
	{
		shared_ptr<Entity> fhdBtn = makeEntity();
		auto s = fhdBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		fhdBtn->setPosition(Vector2f((Engine::getWindowSize().x - 2.0f * buttonRect.width * scale) / 2.0f, buttonRect.height * scale* 3.5f));
		auto t = fhdBtn->addComponent<TextComponent>("\n   1920 x 1080");
		t->SetScale(scale);
		buttons.push_back(fhdBtn);
	}
	// Fullscreen button
	{
		shared_ptr<Entity> fullScreenBtn = makeEntity();
		auto s = fullScreenBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		fullScreenBtn->setPosition(Vector2f((Engine::getWindowSize().x + buttonRect.width * scale) / 2.0f, buttonRect.height * scale / 2.0f));
		auto t = fullScreenBtn->addComponent<TextComponent>("\n   Fullscreen");
		t->SetScale(scale);
		buttons.push_back(fullScreenBtn);
	}
	// Exit fullscreen button
	{
		shared_ptr<Entity> exitFullScreenBtn = makeEntity();
		auto s = exitFullScreenBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		exitFullScreenBtn->setPosition(Vector2f((Engine::getWindowSize().x + buttonRect.width * scale) / 2.0f, buttonRect.height * scale * 2.0f));
		auto t = exitFullScreenBtn->addComponent<TextComponent>("\n   Exit fullscreen");
		t->SetScale(scale);
		buttons.push_back(exitFullScreenBtn);
	}
	// Back button
	{
		shared_ptr<Entity> backBtn = makeEntity();
		auto s = backBtn->addComponent<SpriteComponent>();
		s->getSprite().setTexture(spritesheet);
		s->getSprite().setTextureRect(buttonRect);
		s->getSprite().setScale(Vector2f(scale, scale));
		backBtn->setPosition(Vector2f((Engine::getWindowSize().x + buttonRect.width * scale) / 2.0f, buttonRect.height * scale * 3.5f));
		auto t = backBtn->addComponent<TextComponent>("\n   Back");
		t->SetScale(scale);
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
			resolution = Vector2i(640, 360);
			window_style = sf::Style::Default;
			Engine::GetWindow().close();
			Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &graphics);
		}
		else if (highlighted == 1) {
			resolution = Vector2i(1280, 720);
			Engine::GetWindow().close();
			Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &graphics);
		}
		else if (highlighted == 2) {
			resolution = Vector2i(1920, 1080);
			Engine::GetWindow().close();
			Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &graphics);
		}
		else if (highlighted == 3) {
			window_style = sf::Style::Fullscreen;
			Engine::GetWindow().close();
			Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &graphics);
		}
		else if (highlighted == 4) {
			window_style = sf::Style::Default;
			Engine::GetWindow().close();
			Engine::Start(resolution.x, resolution.y, "Some Spaceship Game", window_style, &graphics);
		}
		else {
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
			if (highlighted > 5) {
				highlighted = 5;
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
