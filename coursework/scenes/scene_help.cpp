#include "scene_help.h"
#include "system_renderer.h"
#include "../resource_manager.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../engine/src/engine.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// List of UI buttons
vector<shared_ptr<Entity>> HelpScene::buttons;
// Index of highlighted button
int HelpScene::highlighted = 0;

void HelpScene::Load() {
	cout << "Help Load \n";
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
		auto t = title->addComponent<TextComponent>("Confirm button to return\n");
		t->SetScale(scale);
	}
	// Help
	{
		auto helpScreen = makeEntity();
		auto spr = helpScreen->addComponent<SpriteComponent>();
		spr->getSprite().setTexture(ResourceManager::Tex_help);
		spr->getSprite().setScale(resolution.x / (float)ResourceManager::Tex_help.getSize().x, resolution.y / (float)ResourceManager::Tex_help.getSize().y);
	}
	setLoaded(true);
	cout << "Help Load Done\n";
}

void HelpScene::Update(const double& dt) {
	if (InputManager::Player[0].confirm) {
			Engine::ChangeScene(&menu);
	}
	Scene::Update(dt);
}

