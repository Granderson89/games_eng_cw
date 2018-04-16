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
#include "../components/cmp_animator.h"
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

// Weapon mount positions
vector<Vector2f> cannon_offsets;
vector<Vector2f> torpedo_offsets;
vector<Vector2f> missile_offsets;
// Ship dimensions
float ship_width = 50.0f;
float ship_length = 200.0f;
// Weapon mount dimensions
float mount_height = 4.0f;

// Sounds
sf::SoundBuffer Level1Scene::bgBuffer;
sf::Sound Level1Scene::bgSound;

void Level1Scene::Load() {
	cout << " Scene 1 Load" << endl;

	// Create a container entity for the camera script (ce - camera entity, cc - camera component)
	ce = makeEntity();
	auto cc = ce->addComponent<CameraControllerComponent>();
	ce->addComponent<BackgroundBuilderComponent>();
	ce->addTag("camera");
	ce->addTag("background");

	// Weapon mount positions relative to centre of ship
	for (int i = 0; i < 8; i++) {
		auto mount_pos = Vector2f(ship_width / 2.0f, -ship_length / 2.0f + mount_height + i * 25.0f + 5.0f);
		cannon_offsets.push_back(mount_pos);
	}
	for (int i = 1; i < 6; i++) {
		auto mount_pos = Vector2f(ship_width / 2.0f, -ship_length / 2.0f + mount_height + i * 25.0f + 5.0f);
		torpedo_offsets.push_back(mount_pos);
	}
	auto mount_pos1 = Vector2f(0.0f, -ship_length / 2.0f + mount_height + 2 * 25.0f + 5.0f);
	missile_offsets.push_back(mount_pos1);
	auto mount_pos2 = Vector2f(0.0f, -ship_length / 2.0f + mount_height + 5 * 25.0f + 5.0f);
	missile_offsets.push_back(mount_pos2);

	// Create player entities
	Vector2f p1_start_position(100.0f, 250.0f);
	player1 = makeEntity();
	player1->addTag("p1");
	player1->setPosition(p1_start_position);

	Vector2f p2_start_position(800.0f, 250.0f);
	player2 = makeEntity();
	player2->addTag("p2");
	player2->setPosition(p2_start_position);

	createPlayer(player1.get(), player2.get(), ResourceManager::Tex_player1, ship_width, ship_length);
	createPlayer(player2.get(), player1.get(), ResourceManager::Tex_player2, ship_width, ship_length);

	// Add the thrusters component
	player1->addComponent<ThrustersComponent>(Vector2f(ship_width, ship_length), 8.0f);
	player2->addComponent<ThrustersComponent>(Vector2f(ship_width, ship_length), 8.0f);

	// Add the players as targets to the camera
	cc->addTarget(player1);
	cc->addTarget(player2);

	// Create huds
	createHud(player1);
	createHud(player2);
	
	//Simulate long loading times
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	bgSound.setLoop(true);
	bgSound.play();
	cout << " Scene 1 Load Done" << endl;
	setLoaded(true);
}

void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player1.reset();
	player2.reset();
	bgSound.stop();
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

void Level1Scene::createPlayer(Entity* player, Entity* opponent, Texture& ship_tex, float width, float length) {
	// Add Sprite Component
	auto spr = player->addComponent<SpriteComponent>();
	spr->getSprite().setTexture(ship_tex);
	spr->getSprite().setOrigin(ship_tex.getSize().x / 2, ship_tex.getSize().y / 2);
	spr->getSprite().setScale(width / (float)ship_tex.getSize().x, length / (float)ship_tex.getSize().y);

	if (player == player2.get() && players == 1) {
		auto sm = player->addComponent<StateMachineComponent>();
		sm->addState("seek", make_shared<SeekState>(player2, player1));
		sm->addState("flee", make_shared<FleeState>(player2, player1));
		sm->addState("face", make_shared<FaceState>(player2, player1));
		sm->changeState("face");
	}

	// Add Player Physics Component and set mass
	vector<unsigned int> mask;
	std::shared_ptr<PlayerPhysicsComponent> p;
	int weapon_num = 0;
	if (player == player1.get()) {
		mask.push_back(P2_PROJECTILE_BIT);
		mask.push_back(P2_BIT);
		mask.push_back(BOUNDARY_BIT);
		p = player->addComponent<PlayerPhysicsComponent>(Vector2f(width, length), P1_BIT, mask);

	}
	else {
		mask.push_back(P1_PROJECTILE_BIT);
		mask.push_back(P1_BIT);
		mask.push_back(BOUNDARY_BIT);
		p = player->addComponent<PlayerPhysicsComponent>(Vector2f(width, length), P2_BIT, mask);
		weapon_num = 15;
	}
	p->setMass(5.0f);

	// Add weapons
	// CANNONS
	for (int i = 0; i < 8; i++) {
		// Add sprite for mount
		auto cannonSpr = player->addComponent<SpriteComponent>(90.0f);
		cannonSpr->setOffset(cannon_offsets.at(i));
		// Add weapon behaviour
		player->addComponent<WeaponComponent>(opponent, cannon_offsets.at(i), weapon_num, CANNONS);
		weapon_num++;
	}
	// TORPEDOS
	for (int i = 0; i < 5; i++) {
		// Add sprite for mount
		auto cannonSpr = player->addComponent<SpriteComponent>(90.0f);
		cannonSpr->setOffset(torpedo_offsets.at(i));
		// Add weapon behaviour
		player->addComponent<WeaponComponent>(opponent, torpedo_offsets.at(i), weapon_num, TORPEDOS);
		weapon_num++;
	}
	// MISSILES
	for (int i = 0; i < 2; i++) {
		// Add sprite for mount
		auto cannonSpr = player->addComponent<SpriteComponent>(90.0f);
		cannonSpr->setOffset(missile_offsets.at(i));
		// Add weapon behaviour
		player->addComponent<WeaponComponent>(opponent, missile_offsets.at(i), weapon_num, MISSILES);
		weapon_num++;
	}
	// Defensive turret
	// Add independently rotating sprite
	auto turret = player->addComponent<SpriteComponent>(0.0f, true);
	turret->getSprite().setTexture(ResourceManager::Tex_turret);
	turret->getSprite().setOrigin(ResourceManager::Tex_turret.getSize().x / 2, ResourceManager::Tex_turret.getSize().y / 2);
	turret->getSprite().setScale(Vector2f(0.25f, 0.25f));
	// Add the turret component
	if (player == player1.get()) {
		player->addComponent<TurretComponent>(0);
	}
	else {
		player->addComponent<TurretComponent>(1);
	}
	// Add the player state component
	player->addComponent<PlayerStateComponent>();



	// Thrusters
	// N
	auto t2 = player->addComponent<SpriteComponent>();
	t2->getSprite().setTexture(ResourceManager::Tex_thruster1_off);
	t2->setOffset(Vector2f(0.0f, -100.0f));
	t2->getSprite().setOrigin(ResourceManager::Tex_thruster1_off.getSize().x / 2, ResourceManager::Tex_thruster1_off.getSize().y / 2);
	t2->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x, length / (float)ResourceManager::Tex_player1.getSize().y * -1.0f);
	player->addComponent<AnimatorComponent>(t2, ResourceManager::Tex_thruster1_on, ResourceManager::Tex_thruster1_off.getSize(), 0.3f, 5);
	// NE
	auto t6 = player->addComponent<SpriteComponent>();
	t6->getSprite().setTexture(ResourceManager::Tex_thruster2_off);
	t6->setOffset(Vector2f(24.0f, -76.0f));
	t6->getSprite().setOrigin(ResourceManager::Tex_thruster2_off.getSize().x / 2, ResourceManager::Tex_thruster2_off.getSize().y / 2);
	t6->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x * -1.0f, length / (float)ResourceManager::Tex_player1.getSize().y);
	player->addComponent<AnimatorComponent>(t6, ResourceManager::Tex_thruster2_on, ResourceManager::Tex_thruster2_off.getSize(), 0.3f, 5);
	// SE
	auto t5 = player->addComponent<SpriteComponent>();
	t5->getSprite().setTexture(ResourceManager::Tex_thruster2_off);
	t5->setOffset(Vector2f(24.0f, 77.0f));
	t5->getSprite().setOrigin(ResourceManager::Tex_thruster2_off.getSize().x / 2, ResourceManager::Tex_thruster2_off.getSize().y / 2);
	t5->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x * -1.0f, length / (float)ResourceManager::Tex_player1.getSize().y);
	player->addComponent<AnimatorComponent>(t5, ResourceManager::Tex_thruster2_on, ResourceManager::Tex_thruster2_off.getSize(), 0.3f, 5);
	// S
	auto t1 = player->addComponent<SpriteComponent>();
	t1->getSprite().setTexture(ResourceManager::Tex_thruster1_off);
	t1->setOffset(Vector2f(0.0f, 100.0f));
	t1->getSprite().setOrigin(ResourceManager::Tex_thruster1_off.getSize().x / 2, ResourceManager::Tex_thruster1_off.getSize().y / 2);
	t1->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x, length / (float)ResourceManager::Tex_player1.getSize().y);
	player->addComponent<AnimatorComponent>(t1, ResourceManager::Tex_thruster1_on, ResourceManager::Tex_thruster1_off.getSize(), 0.3f, 5);
	// SW
	auto t3 = player->addComponent<SpriteComponent>();
	t3->getSprite().setTexture(ResourceManager::Tex_thruster2_off);
	t3->setOffset(Vector2f(-26.0f, 77.0f));
	t3->getSprite().setOrigin(ResourceManager::Tex_thruster2_off.getSize().x / 2, ResourceManager::Tex_thruster2_off.getSize().y / 2);
	t3->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x, length / (float)ResourceManager::Tex_player1.getSize().y);
	player->addComponent<AnimatorComponent>(t3, ResourceManager::Tex_thruster2_on, ResourceManager::Tex_thruster2_off.getSize(), 0.3f, 5);
	// NW
	auto t4 = player->addComponent<SpriteComponent>();
	t4->getSprite().setTexture(ResourceManager::Tex_thruster2_off);
	t4->setOffset(Vector2f(-26.0f, -76.0f));
	t4->getSprite().setOrigin(ResourceManager::Tex_thruster2_off.getSize().x / 2, ResourceManager::Tex_thruster2_off.getSize().y / 2);
	t4->getSprite().setScale(width / (float)ResourceManager::Tex_player1.getSize().x, length / (float)ResourceManager::Tex_player1.getSize().y);
	player->addComponent<AnimatorComponent>(t4, ResourceManager::Tex_thruster2_on, ResourceManager::Tex_thruster2_off.getSize(), 0.3f, 5);
}

void Level1Scene::createHud(std::shared_ptr<Entity> player) {
	// Create a container entity for player 1's hud
	shared_ptr<Entity> hud;
	hud = makeEntity();
	// Create a container entity for player 1's weapon type
	shared_ptr<Entity> weaponTypeEntity;
	weaponTypeEntity = makeEntity();
	// Create container entites for player 1's cooldowns
	vector <shared_ptr<Entity>> cooldowns;
	for (int i = 0; i < 8; i++) {
		shared_ptr<Entity> cool;
		cool = makeEntity();
		cooldowns.push_back(cool);
	}
	// Add the hud component
	hud->addComponent<HudComponent>(player, weaponTypeEntity, cooldowns, ce);
	// Health bar
	auto healthBarBg = hud->addComponent<ShapeComponent>();
	healthBarBg->setShape<sf::RectangleShape>(Vector2f(1.0f, 30.0f));
	healthBarBg->getShape().setScale(Vector2f(100.0f, 1.0f));
	auto healthBar = hud->addComponent<ShapeComponent>();
	healthBar->setShape<sf::RectangleShape>(Vector2f(1.0f, 30.0f));
	auto healthText = hud->addComponent<TextComponent>();
	healthText->SetText("Health");
	if (player == player1) {
		healthBarBg->getShape().setFillColor(Color::Red);
		healthText->SetColor(sf::Color::Blue);
	}
	else {
		healthBarBg->getShape().setFillColor(Color::Blue);
		healthText->SetColor(sf::Color::Red);
	}
	healthText->SetScale(0.5f);
	// Selected weapon type
	auto weaponType = weaponTypeEntity->addComponent<SpriteComponent>();
	// Cooldowns
	for (int i = 0; i < 8; i++) {
		auto cooldown = cooldowns.at(i)->addComponent<SpriteComponent>();
		cooldown->getSprite().setTexture(ResourceManager::tex_test);
		cooldown->getSprite().setOrigin(ResourceManager::tex_test.getSize().x / 2, ResourceManager::tex_test.getSize().y / 2);
		auto timer = cooldowns.at(i)->addComponent<ShapeComponent>();
		timer->setShape<sf::RectangleShape>(Vector2f(ResourceManager::tex_test.getSize().x, ResourceManager::tex_test.getSize().y));
		timer->getShape().setOrigin(ResourceManager::tex_test.getSize().x / 2, ResourceManager::tex_test.getSize().y / 2);
		sf::Color timerColor = sf::Color::Black;
		timerColor.a = 128.0f;
		timer->getShape().setFillColor(timerColor);
	}
}

void Level1Scene::loadSounds()
{
	bgBuffer.loadFromFile("res/sounds/bg.ogg");
	bgSound.setBuffer(bgBuffer);
}