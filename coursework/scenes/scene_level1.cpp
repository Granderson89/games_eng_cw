#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon_component.h"
#include "../components/cmp_thrusters.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static InputManager im;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  //ls::loadLevelFile("res/level_1.txt", 40.0f);

  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  //ls::setOffset(Vector2f(0, ho));

  // Create player
  {
	float width = 50.0f;
	float length = 200.0f;
	Vector2f start_position(100.0f, 250.0f);

	player = makeEntity();
    //player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->setPosition(start_position);
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(length, width));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(length / 2.0f, width / 2.0f);

    player->addComponent<PlayerPhysicsComponent>(Vector2f(width, length));

	player->addComponent<ThrustersComponent>(Vector2f(width, length), 0.01f);

	// Add weapons
	float projectile_width = 4.0f;
	float projectile_height = 4.0f;
	// CANNONS
	for (int i = 0; i < 8; i++) {
		Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + i * 25.0f + 5.0f, width / 2.0f + projectile_width);
		player->addComponent<WeaponComponent>(mount_position, i, CANNONS);
	}
	// TORPEDOS
	for (int i = 1; i < 6; i++) {
		Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + i * 25.0f + 5.0f, width / 2.0f + projectile_width);
		player->addComponent<WeaponComponent>(mount_position, i, TORPEDOS);
	}
	// MISSILES
	for (int i = 3; i < 5; i++) {
		Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + i * 25.0f + 5.0f, width / 2.0f + projectile_width);
		player->addComponent<WeaponComponent>(mount_position, i, MISSILES);
	}
  }

  im.initialize();


  // Add physics colliders to level tiles.
  //{
  //  auto walls = ls::findTiles(ls::WALL);
  //  for (auto w : walls) {
  //    auto pos = ls::getTilePosition(w);
  //    pos += Vector2f(20.f, 20.f); //offset to center
  //    auto e = makeEntity();
  //    e->setPosition(pos);
  //    e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
  //  }
  //}

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  //ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

  //if (ls::getTileAt(player->getPosition()) == ls::END) {
  //  //Engine::ChangeScene((Scene*)&level2);
  //}
  Scene::Update(dt);
}

void Level1Scene::Render() {
  //ls::render(Engine::GetWindow());
  Scene::Render();
}
