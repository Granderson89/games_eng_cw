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

// Pointers to players
shared_ptr<Entity> player1;
shared_ptr<Entity> player2;

// Box2d collision bits
unsigned int P1_BIT = 1;
unsigned int P1_PROJECTILE_BIT = 2;
unsigned int P2_BIT = 4;
unsigned int P2_PROJECTILE_BIT = 8;

// Input Manager
static InputManager im;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;

  // Ship dimensions
  float width = 50.0f;
  float length = 200.0f;
  // Weapon mount dimensions
  float mount_width = 4.0f;
  float mount_height = 4.0f;
  // Weapon mount positions relative to centre of ship
  vector<Vector2f> cannon_offsets;
  for (int i = 0; i < 8; i++) {
	  auto mount_pos = Vector2f(-length / 2.0f + mount_height + i * 25.0f + 5.0f, width / 2.0f + mount_width);
	  cannon_offsets.push_back(mount_pos);
  }
  vector<Vector2f> torpedo_offsets;
  for (int i = 1; i < 6; i++) {
	  auto mount_pos = Vector2f(-length / 2.0f + mount_height + i * 25.0f + 5.0f, width / 2.0f + mount_width);
	  torpedo_offsets.push_back(mount_pos);
  }
  vector<Vector2f> missile_offsets;
  for (int i = 3; i < 5; i++) {
	  auto mount_pos = Vector2f(-length / 2.0f + mount_height + i * 25.0f + 5.0f, width / 2.0f + mount_width);
	  missile_offsets.push_back(mount_pos);
  }

  // Create player 1
  {
	Vector2f p1_start_position(100.0f, 250.0f);
	player1 = makeEntity();
	player1->addTag("p1");
	player1->setPosition(p1_start_position);
	// Add Shape Component
    auto s = player1->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(length, width));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(length / 2.0f, width / 2.0f);
	// Add Player Physics Component and set mass
    auto p = player1->addComponent<PlayerPhysicsComponent>(Vector2f(length, width), P1_BIT, P2_PROJECTILE_BIT);
	p->setMass(5.0f);
	// Add weapons
	int weapon_num = 0;
	// CANNONS
	for (int i = 0; i < 8; i++) {
		player1->addComponent<WeaponComponent>(cannon_offsets.at(i), weapon_num, CANNONS);
		weapon_num++;
	}
	// TORPEDOS
	for (int i = 0; i < 5; i++) {
		player1->addComponent<WeaponComponent>(torpedo_offsets.at(i), weapon_num, TORPEDOS);
		weapon_num++;
	}
	// MISSILES
	for (int i = 0; i < 2; i++) {
		player1->addComponent<WeaponComponent>(missile_offsets.at(i), weapon_num, MISSILES);
		weapon_num++;
	}
  }
  // Create player 2
  {
	  Vector2f p2_start_position(800.0f, 250.0f);
	  player2 = makeEntity();
	  player2->addTag("p2");
	  player2->setPosition(p2_start_position);
	  // Add Shape Component
	  auto s = player2->addComponent<ShapeComponent>();
	  s->setShape<sf::RectangleShape>(Vector2f(length, width));
	  s->getShape().setFillColor(Color::White);
	  s->getShape().setOrigin(length / 2.0f, width / 2.0f);
	  // Add Player Physics Component and set mass
	  auto p = player2->addComponent<PlayerPhysicsComponent>(Vector2f(length, width), P2_BIT, P1_PROJECTILE_BIT);
	  p->setMass(5.0f);
	  // Add weapons
	  int weapon_num = 15;
	  // CANNONS
	  for (int i = 0; i < 8; i++) {
		  player2->addComponent<WeaponComponent>(cannon_offsets.at(i), weapon_num, CANNONS);
		  weapon_num++;
	  }
	  // TORPEDOS
	  for (int i = 0; i < 5; i++) {
		  player2->addComponent<WeaponComponent>(torpedo_offsets.at(i), weapon_num, TORPEDOS);
		  weapon_num++;
	  }
	  // MISSILES
	  for (int i = 0; i < 2; i++) {
		  player2->addComponent<WeaponComponent>(missile_offsets.at(i), weapon_num, MISSILES);
		  weapon_num++;
	  }
  }

  // Initialise input manager
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
