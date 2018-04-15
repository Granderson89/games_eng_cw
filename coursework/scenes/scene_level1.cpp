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
#include "../components/cmp_state_machine.h"
#include "../game.h"
#include "../steering_states.h"
#include "../resource_manager.h"
#include "../components/cmp_background.h"
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
unsigned int P1_BIT = 64;
unsigned int P1_PROJECTILE_BIT = 128;
unsigned int P1_TURRET_PROJ_BIT = 256;
unsigned int P2_BIT = 8;
unsigned int P2_PROJECTILE_BIT = 16;
unsigned int P2_TURRET_PROJ_BIT = 32;

unsigned int BOUNDARY_BIT = 512;

void Level1Scene::Load() {
	std::cout << "Player 1 fire: " << InputManager::playerInput[0].fire << std::endl;

	cout << " Scene 1 Load" << endl;

	// Create a container entity for the camera script (ce - camera entity, cc - camera component)
	ce = makeEntity();
	auto cc = ce->addComponent<CameraControllerComponent>();
	ce->addComponent<BackgroundBuilderComponent>();


	// Ship dimensions
	float width = 50.0f;
	float length = 200.0f;
	// Weapon mount dimensions
	float mount_width = 4.0f;
	float mount_height = 4.0f;
	// Weapon mount positions relative to centre of ship
	vector<Vector2f> cannon_offsets;
	for (int i = 0; i < 8; i++) {
		auto mount_pos = Vector2f(width / 2.0f, -length / 2.0f + mount_height + i * 25.0f + 5.0f);
		cannon_offsets.push_back(mount_pos);
	}
	vector<Vector2f> torpedo_offsets;
	for (int i = 1; i < 6; i++) {
		auto mount_pos = Vector2f(width / 2.0f, -length / 2.0f + mount_height + i * 25.0f + 5.0f);
		torpedo_offsets.push_back(mount_pos);
	}
	vector<Vector2f> missile_offsets;
	for (int i = 3; i < 5; i++) {
		auto mount_pos = Vector2f(0.0f, -length / 2.0f + mount_height + i * 25.0f + 5.0f);
		missile_offsets.push_back(mount_pos);
	}
	Vector2f p2_start_position(800.0f, 250.0f);
	player2 = makeEntity();
	player2->addTag("p2");
	player2->setPosition(p2_start_position);

	// Create player 1
	{
		Vector2f p1_start_position(100.0f, 250.0f);
		player1 = makeEntity();
		player1->addTag("p1");
		player1->setPosition(p1_start_position);

		// Add Sprite Component
		auto spr = player1->addComponent<SpriteComponent>();
		spr->getSprite().setTexture(ResourceManager::Tex_player1);
		spr->getSprite().setOrigin(ResourceManager::Tex_player1.getSize().x / 2, ResourceManager::Tex_player1.getSize().y / 2);
		spr->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x, length / (float)ResourceManager::Tex_player1.getSize().y);
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
			auto cannonSpr = player1->addComponent<SpriteComponent>(90.0f);
			cannonSpr->setOffset(cannon_offsets.at(i));
			player1->addComponent<WeaponComponent>(player2.get(), cannon_offsets.at(i), weapon_num, CANNONS);
			weapon_num++;
		}
		// TORPEDOS
		for (int i = 0; i < 5; i++) {
			auto cannonSpr = player1->addComponent<SpriteComponent>(90.0f);
			cannonSpr->setOffset(torpedo_offsets.at(i));
			player1->addComponent<WeaponComponent>(player2.get(), torpedo_offsets.at(i), weapon_num, TORPEDOS);
			weapon_num++;
		}
		// MISSILES
		for (int i = 0; i < 2; i++) {
			auto cannonSpr = player1->addComponent<SpriteComponent>(90.0f);
			cannonSpr->setOffset(missile_offsets.at(i));
			player1->addComponent<WeaponComponent>(player2.get(), missile_offsets.at(i), weapon_num, MISSILES);
			weapon_num++;
		}
		// Defensive turret
		auto turret = player1->addComponent<SpriteComponent>(0.0f, true);
		turret->getSprite().setTexture(ResourceManager::Tex_turret);
		turret->getSprite().setOrigin(ResourceManager::Tex_turret.getSize().x / 2, ResourceManager::Tex_turret.getSize().y / 2);
		turret->getSprite().setScale(Vector2f(0.25f, 0.25f));
		player1->addComponent<TurretComponent>(0);
		player1->addComponent<ThrustersComponent>(Vector2f(width, length), 3.0f);
		player1->addComponent<PlayerStateComponent>();

	}
	// Create player 2
	{
		// Add Sprite Component
		auto spr = player2->addComponent<SpriteComponent>();
		spr->getSprite().setTexture(ResourceManager::Tex_player2);
		spr->getSprite().setOrigin(ResourceManager::Tex_player2.getSize().x / 2, ResourceManager::Tex_player2.getSize().y / 2);
		spr->getSprite().setScale(width / (float)ResourceManager::Tex_player2.getSize().x, length / (float)ResourceManager::Tex_player2.getSize().y);
		if (players == 1) {
			auto sm = player2->addComponent<StateMachineComponent>();
			sm->addState("seek", make_shared<SeekState>(player2, player1));
			sm->addState("flee", make_shared<FleeState>(player2, player1));
			sm->addState("face", make_shared<FaceState>(player2, player1));
			sm->changeState("face");
		}
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
			auto cannonSpr = player2->addComponent<SpriteComponent>(0.0f);
			cannonSpr->setOffset(cannon_offsets.at(i));
			player2->addComponent<WeaponComponent>(player1.get(), cannon_offsets.at(i), weapon_num, CANNONS);
			weapon_num++;
		}
		// TORPEDOS
		for (int i = 0; i < 5; i++) {
			auto cannonSpr = player2->addComponent<SpriteComponent>(20.0f);
			cannonSpr->setOffset(torpedo_offsets.at(i));
			player2->addComponent<WeaponComponent>(player1.get(), torpedo_offsets.at(i), weapon_num, TORPEDOS);
			weapon_num++;
		}
		// MISSILES
		for (int i = 0; i < 2; i++) {
			auto cannonSpr = player2->addComponent<SpriteComponent>(90.0f);
			cannonSpr->setOffset(missile_offsets.at(i));
			player2->addComponent<WeaponComponent>(player1.get(), missile_offsets.at(i), weapon_num, MISSILES);
			weapon_num++;
		}
		player2->addComponent<TurretComponent>(1);
		player2->addComponent<PlayerStateComponent>();
		// Defensive turret
		auto turret = player2->addComponent<SpriteComponent>(0.0f, true);
		turret->getSprite().setTexture(ResourceManager::Tex_turret);
		turret->getSprite().setOrigin(ResourceManager::Tex_turret.getSize().x / 2, ResourceManager::Tex_turret.getSize().y / 2);
		turret->getSprite().setScale(Vector2f(0.25f, 0.25f));
	}

	ce->addTag("camera");
	ce->addTag("background");
	cc->addTarget(player1);
	cc->addTarget(player2);

	{
		// Create a container entity for player 1's hud
		shared_ptr<Entity> p1he;
		p1he = makeEntity();
		// Create a container entity for player 1's weapon type
		shared_ptr<Entity> p1wt;
		p1wt = makeEntity();
		// Create container entites for player 1's cooldowns
		vector <shared_ptr<Entity>> p1cds;
		for (int i = 0; i < 8; i++) {
			shared_ptr<Entity> cool;
			cool = makeEntity();
			p1cds.push_back(cool);
		}
		// Add the hud component
		p1he->addComponent<HudComponent>(player1, p1wt, p1cds, ce);
		// Health bar
		auto healthBarBg = p1he->addComponent<ShapeComponent>();
		healthBarBg->setShape<sf::RectangleShape>(Vector2f(1.0f, 30.0f));
		healthBarBg->getShape().setFillColor(Color::Red);
		healthBarBg->getShape().setScale(Vector2f(100.0f, 1.0f));
		auto healthBar = p1he->addComponent<ShapeComponent>();
		healthBar->setShape<sf::RectangleShape>(Vector2f(1.0f, 30.0f));
		auto healthText = p1he->addComponent<TextComponent>();
		healthText->SetText("Health");
		healthText->SetColor(sf::Color::Blue);
		healthText->SetScale(0.5f);
		// Selected weapon type
		auto weaponType = p1wt->addComponent<SpriteComponent>();
		// Cooldowns
		for (int i = 0; i < 8; i++) {
			auto cooldown = p1cds.at(i)->addComponent<SpriteComponent>();
			cooldown->getSprite().setTexture(ResourceManager::tex_test);
			cooldown->getSprite().setOrigin(ResourceManager::tex_test.getSize().x / 2, ResourceManager::tex_test.getSize().y / 2);
			auto timer = p1cds.at(i)->addComponent<ShapeComponent>();
			timer->setShape<sf::RectangleShape>(Vector2f(ResourceManager::tex_test.getSize().x, ResourceManager::tex_test.getSize().y));
			timer->getShape().setOrigin(ResourceManager::tex_test.getSize().x / 2, ResourceManager::tex_test.getSize().y / 2);
			sf::Color timerColor = sf::Color::Black;
			timerColor.a = 128.0f;
			timer->getShape().setFillColor(timerColor);
		}
	}
	{
		// Create a container entity for player 2's hud
		shared_ptr<Entity> p2he;
		p2he = makeEntity();
		// Create a container entity for player 2's weapon type
		shared_ptr<Entity> p2wt;
		p2wt = makeEntity();
		// Create container entites for player 2's cooldowns
		vector <shared_ptr<Entity>> p2cds;
		for (int i = 0; i < 8; i++) {
			shared_ptr<Entity> cool;
			cool = makeEntity();
			p2cds.push_back(cool);
		}
		// Add the hud component
		p2he->addComponent<HudComponent>(player2, p2wt, p2cds, ce);
		// Health bar
		auto healthBarBg = p2he->addComponent<ShapeComponent>();
		healthBarBg->setShape<sf::RectangleShape>(Vector2f(1.0f, 30.0f));
		healthBarBg->getShape().setFillColor(Color::Blue);
		auto healthBar = p2he->addComponent<ShapeComponent>();
		healthBar->setShape<sf::RectangleShape>(Vector2f(1.0f, 30.0f));
		auto healthText = p2he->addComponent<TextComponent>();
		healthText->SetText("Health");
		healthText->SetColor(sf::Color::Red);
		healthText->SetScale(0.5f);
		// Selected weapon type
		auto weaponType = p2wt->addComponent<SpriteComponent>();
		// Cooldowns
		for (int i = 0; i < 8; i++) {
			auto cooldown = p2cds.at(i)->addComponent<SpriteComponent>();
			cooldown->getSprite().setTexture(ResourceManager::tex_test);
			cooldown->getSprite().setOrigin(ResourceManager::tex_test.getSize().x / 2, ResourceManager::tex_test.getSize().y / 2);
			auto timer = p2cds.at(i)->addComponent<ShapeComponent>();
			timer->setShape<sf::RectangleShape>(Vector2f(ResourceManager::tex_test.getSize().x, ResourceManager::tex_test.getSize().y));
			timer->getShape().setOrigin(ResourceManager::tex_test.getSize().x / 2, ResourceManager::tex_test.getSize().y / 2);
			sf::Color timerColor = sf::Color::Black;
			timerColor.a = 128.0f;
			timer->getShape().setFillColor(timerColor);
		}
	}
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
	view.reset(FloatRect(0.0f, 0.0f, resolution.x, resolution.y));
	Renderer::getWindow().setView(view);
	ce.reset();
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
	if (InputManager::Player[0].pause || InputManager::Player[1].pause) {
		Engine::PauseScene(&pause);
	}
	Scene::Update(dt);
}

void Level1Scene::Render() {
	Scene::Render();
}
