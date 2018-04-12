#include "scene_level1.h"
#include "system_renderer.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon_component.h"
#include "../components/cmp_defensive_turret.h"
#include "../components/cmp_thrusters.h"
#include "../components/cmp_player_state.h"
#include "../components/cmp_camera.h"
#include "../components/cmp_hud.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

// Pointers to players
shared_ptr<Entity> player1;
shared_ptr<Entity> player2;
int winner;

shared_ptr<Entity> ce;

// Box2d collision bits
unsigned int P1_BIT = 1;
unsigned int P1_PROJECTILE_BIT = 2;
unsigned int P1_TURRET_PROJ_BIT = 4;
unsigned int P2_BIT = 8;
unsigned int P2_PROJECTILE_BIT = 16;
unsigned int P2_TURRET_PROJ_BIT = 32;

unsigned int BOUNDARY_BIT = 64;

void Level1Scene::Load() {
	std::cout << "Player 1 fire: " << InputManager::playerInput[0].fire << std::endl;

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
	  auto mount_pos = Vector2f(width / 2.0f + mount_width, -length / 2.0f + mount_height + i * 25.0f + 5.0f);
	  cannon_offsets.push_back(mount_pos);
  }
  vector<Vector2f> torpedo_offsets;
  for (int i = 1; i < 6; i++) {
	  auto mount_pos = Vector2f(width / 2.0f + mount_width, -length / 2.0f + mount_height + i * 25.0f + 5.0f);
	  torpedo_offsets.push_back(mount_pos);
  }
  vector<Vector2f> missile_offsets;
  for (int i = 3; i < 5; i++) {
	  auto mount_pos = Vector2f(width / 2.0f + mount_width, -length / 2.0f + mount_height + i * 25.0f + 5.0f);
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
    s->setShape<sf::RectangleShape>(Vector2f(width, length));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(width / 2.0f, length / 2.0f);
	// Add Player Physics Component and set mass
	vector<unsigned int> mask;
	mask.push_back(P2_PROJECTILE_BIT);
	mask.push_back(P2_BIT);
	mask.push_back(BOUNDARY_BIT);
    auto p = player1->addComponent<PlayerPhysicsComponent>(Vector2f(width, length), P1_BIT, mask);
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
	player1->addComponent<TurretComponent>(0);
	player1->addComponent<ThrustersComponent>(Vector2f(width, length), 3.0f);
	player1->addComponent<PlayerStateComponent>();
  }
  // Create player 2
  {
	  Vector2f p2_start_position(800.0f, 250.0f);
	  player2 = makeEntity();
	  player2->addTag("p2");
	  player2->setPosition(p2_start_position);
	  // Add Shape Component
	  auto s = player2->addComponent<ShapeComponent>();
	  s->setShape<sf::RectangleShape>(Vector2f(width, length));
	  s->getShape().setFillColor(Color::White);
	  s->getShape().setOrigin(width / 2.0f, length / 2.0f);
	  // Add Player Physics Component and set mass
	  vector<unsigned int> mask;
	  mask.push_back(P1_PROJECTILE_BIT);
	  mask.push_back(P1_BIT);
	  mask.push_back(BOUNDARY_BIT);
	  auto p = player2->addComponent<PlayerPhysicsComponent>(Vector2f(width, length), P2_BIT, mask);
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
	  player2->addComponent<TurretComponent>(1);
	  //player2->addComponent<ThrustersComponent>(Vector2f(width, length), 3.0f);
	  player2->addComponent<PlayerStateComponent>();

  }

  // Create a container entity for the camera script (ce - camera entity, cc - camera component)
  ce = makeEntity();
  auto cc = ce->addComponent<CameraControllerComponent>();
  ce->addTag("camera");
  cc->addTarget(player1);
  cc->addTarget(player2);

  // Create a container entity for player 1's hud
  shared_ptr<Entity> p1he;
  p1he = makeEntity();
  p1he->addComponent<HudComponent>(player1, ce);
  p1he->addComponent<TextComponent>();
  p1he->addComponent<TextComponent>();
  p1he->addComponent<TextComponent>();
  p1he->addComponent<TextComponent>();

  // Create a container entity for player 2's hud
  shared_ptr<Entity> p2he;
  p2he = makeEntity();
  p2he->addComponent<HudComponent>(player2, ce);
  p2he->addComponent<TextComponent>();
  p2he->addComponent<TextComponent>();
  p2he->addComponent<TextComponent>();
  p2he->addComponent<TextComponent>();

  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;
  std::cout << "Player 1 fire: " << InputManager::playerInput[0].fire << std::endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player1.reset();
  player2.reset();
  sf::View view;
  view.reset(FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));	// hardcoded values ///////////////////////////////////////////////
  Renderer::getWindow().setView(view);
  ce.reset();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
	if (InputManager::Player[0].pause || InputManager::Player[1].pause) {
		Engine::ChangeScene(&pause);
	}
  Scene::Update(dt);
}

void Level1Scene::Render() {
  Scene::Render();
}
