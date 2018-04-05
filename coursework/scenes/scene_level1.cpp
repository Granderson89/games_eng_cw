#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon_component.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

shared_ptr<Entity> player1;
shared_ptr<Entity> player2;

unsigned int P1_BIT = 0;
unsigned int P1_PROJECTILE_BIT = 1;
unsigned int P2_BIT = 2;
unsigned int P2_PROJECTILE_BIT = 4;

static InputManager im;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;

  // Create player 1
  {
	float width = 50.0f;
	float length = 200.0f;
	Vector2f p1_start_position(100.0f, 250.0f);

	player1 = makeEntity();
	player1->addTag("p1");
	player1->setPosition(p1_start_position);
    auto s = player1->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(length, width));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(length / 2.0f, width / 2.0f);

    auto p = player1->addComponent<PlayerPhysicsComponent>(Vector2f(length, width), P1_BIT, P2_PROJECTILE_BIT);
	p->setMass(5.0f);

	// Add weapons
	float projectile_width = 4.0f;
	float projectile_height = 4.0f;
	int weapon_num = 0;
	// CANNONS
	for (int i = 0; i < 8; i++) {
		Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + i * 25.0f + 5.0f, width / 2.0f + projectile_width);
		player1->addComponent<WeaponComponent>(mount_position, weapon_num, CANNONS);
		weapon_num++;
	}
	// TORPEDOS
	for (int i = 1; i < 6; i++) {
		Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + i * 25.0f + 5.0f, width / 2.0f + projectile_width);
		player1->addComponent<WeaponComponent>(mount_position, weapon_num, TORPEDOS);
		weapon_num++;
	}
	// MISSILES
	for (int i = 3; i < 5; i++) {
		Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + i * 25.0f + 5.0f, width / 2.0f + projectile_width);
		player1->addComponent<WeaponComponent>(mount_position, weapon_num, MISSILES);
		weapon_num++;
	}
  }

  // Create player 2
  {
	  float width = 50.0f;
	  float length = 200.0f;
	  Vector2f p2_start_position(800.0f, 250.0f);

	  player2 = makeEntity();
	  player2->addTag("p2");
	  player2->setPosition(p2_start_position);
	  auto s = player2->addComponent<ShapeComponent>();
	  s->setShape<sf::RectangleShape>(Vector2f(length, width));
	  s->getShape().setFillColor(Color::White);
	  s->getShape().setOrigin(length / 2.0f, width / 2.0f);

	  auto p = player2->addComponent<PlayerPhysicsComponent>(Vector2f(length, width), P2_BIT, P1_PROJECTILE_BIT);
	  p->setMass(5.0f);

	  // Add weapons
	  float projectile_width = 4.0f;
	  float projectile_height = 4.0f;
	  int weapon_num = 15;
	  // CANNONS
	  for (int i = 0; i < 8; i++) {
		  Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + (15 - weapon_num) * 25.0f + 5.0f, width / 2.0f + projectile_width);
		  player2->addComponent<WeaponComponent>(mount_position, weapon_num, CANNONS);
		  weapon_num++;
	  }
	  // TORPEDOS
	  for (int i = 23; i < 28; i++) {
		  Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + (15 - weapon_num) * 25.0f + 5.0f, width / 2.0f + projectile_width);
		  player2->addComponent<WeaponComponent>(mount_position, weapon_num, TORPEDOS);
		  weapon_num++;
	  }
	  // MISSILES
	  for (int i = 28; i < 30; i++) {
		  Vector2f mount_position = Vector2f(-length / 2.0f + projectile_height + (15 - weapon_num) * 25.0f + 5.0f, width / 2.0f + projectile_width);
		  player2->addComponent<WeaponComponent>(mount_position, weapon_num, MISSILES);
		  weapon_num++;
	  }
  }

  im.initialize();

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player1.reset();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
  Scene::Update(dt);
}

void Level1Scene::Render() {
  Scene::Render();
}
