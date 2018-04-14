#include "cmp_hud.h"
#include "cmp_player_state.h"
#include "cmp_weapon_component.h"
#include "cmp_camera.h"
#include "cmp_text.h"
#include "../game.h"
#include "../resource_manager.h"




HudComponent::HudComponent(Entity* p, std::shared_ptr<Entity> player, std::shared_ptr<Entity> weaponType, std::vector<std::shared_ptr<Entity>> cooldowns, std::shared_ptr<Entity> camera)
	: Component(p), _player(player), _weaponType(weaponType), _cooldowns(cooldowns), _camera(camera),
	_healthBarZero(Vector2f(90.0f, 10.0f)),
	_healthTextZero(Vector2f(120.0f, 5.0f)),
	_weaponTypeZero(Vector2f(40.0f, 40.0f)),
	_cooldownZero(Vector2f(90.0f, 60.0f)),
	_healthBarBgScale(Vector2f(200.0f, 1.0f)),
	_healthBarScale(Vector2f(2.0f, 1.0f)),
	_weaponTypeScale(60.0f), 
	_cooldownScale(20.0f), 
	_cooldownGap(30.0f), 
	_timerScale(0.2f) {}

void HudComponent::update(double dt) {
	// Get camera and view
	auto cameraComp = _camera->GetCompatibleComponent<CameraControllerComponent>().at(0);
	Vector2f position = cameraComp->getMidpoint();
	Vector2f view_dims = cameraComp->getView().getSize();
	// Get scale of view to resize hud accordingly
	float view_scale;
	view_scale = view_dims.x / resolution.x;

	// Get player state
	auto state = _player->GetCompatibleComponent<PlayerStateComponent>().front();
	auto weapons = _player->GetCompatibleComponent<WeaponComponent>();
	
	// Scale text
	auto healthText = _parent->GetCompatibleComponent<TextComponent>().at(0);
	healthText->SetScale(view_scale);
	// Update and scale health bar
	auto healthBarBg = _parent->GetCompatibleComponent<ShapeComponent>().at(0);
	healthBarBg->getShape().setScale(_healthBarBgScale * view_scale);
	auto healthBar = _parent->GetCompatibleComponent<ShapeComponent>().at(1);
	sf::Vector2f healthBarScale;
	healthBarScale = _healthBarScale;
	healthBarScale.x *= state->health;
	healthBar->getShape().setScale(healthBarScale * view_scale);

	// Update weapon selection
	string activeType;
	if (_player == player1) {
		activeType = weapons.at(0)->getP1ActiveType();
	}
	else {
		activeType = weapons.at(0)->getP2ActiveType();
	}
	if (activeType == "CANNONS") {
		_weaponType->setRotation(0.0f);
	}
	else if (activeType == "TORPEDOS") {
		_weaponType->setRotation(90.0f);
	}
	else if (activeType == "MISSILES") {
		_weaponType->setRotation(180.0f);
	}
	// Scale weapon type sprite
	auto weaponTypeSpr = _weaponType->GetCompatibleComponent<SpriteComponent>().at(0);
	weaponTypeSpr->getSprite().setScale(_weaponTypeScale  * view_scale / (float)ResourceManager::tex_test.getSize().x,
		_weaponTypeScale  * view_scale / (float)ResourceManager::tex_test.getSize().y);

	// Get all current weapon cooldowns
	std::vector<float> cannonCools;
	std::vector<float> torpedoCools;
	std::vector<float> missileCools;
	// Cannons
	for (int i = 0; i < 8; i++) {
		auto weapon = weapons.at(i);
		float cooldown = weapon->getCooldown();
		cannonCools.push_back(cooldown);
	}
	// Torpedos
	for (int i = 8; i < 13; i++) {
		auto weapon = weapons.at(i);
		float cooldown = weapon->getCooldown();
		torpedoCools.push_back(cooldown);
	}
	// Missiles
	for (int i = 13; i < 15; i++) {
		auto weapon = weapons.at(i);
		float cooldown = weapon->getCooldown();
		missileCools.push_back(cooldown);
	}
	// Update weapon cooldown sprites
	for (int i = 0; i < 8; i++) {
		// Scale cooldown sprite
		auto cooldownSpr = _cooldowns.at(i)->GetCompatibleComponent<SpriteComponent>().at(0);
		cooldownSpr->getSprite().setScale(_cooldownScale  * view_scale / (float)ResourceManager::tex_test.getSize().x,
			_cooldownScale  * view_scale / (float)ResourceManager::tex_test.getSize().y);
		// Get transparent timer sprite
		auto timerSpr = _cooldowns.at(i)->GetCompatibleComponent<ShapeComponent>().at(0);
		// Set scale of transparent sprite, update it's visibility and type
		if (activeType == "CANNONS") {
			float scale = cannonCools.at(i) * _timerScale * view_scale;
			_cooldowns.at(i)->setVisible(true);
			_cooldowns.at(i)->setRotation(0.0f);
			timerSpr->getShape().setScale(1.0f * _timerScale * view_scale, scale);
		}
		else if (activeType == "TORPEDOS") {
			if (i < 1 || i > 5) {
				_cooldowns.at(i)->setVisible(false);
			}
			else {
				float scale = torpedoCools.at(i - 1) / 2.0f * _timerScale * view_scale;
				_cooldowns.at(i)->setVisible(true);
				_cooldowns.at(i)->setRotation(90.0f);
				timerSpr->getShape().setScale(1.0f * _timerScale * view_scale, scale);
			}
		}
		else if (activeType == "MISSILES") {
			if (i < 3 || i > 4) {
				_cooldowns.at(i)->setVisible(false);
			}
			else {
				float scale = missileCools.at(i - 3) / 3.0f * _timerScale * view_scale;
				_cooldowns.at(i)->setVisible(true);
				_cooldowns.at(i)->setRotation(180.0f);
				timerSpr->getShape().setScale(1.0f * _timerScale * view_scale, scale);
			}
		}
	}

	// Update positions
	if (_player == player1) {
		// Top left
		position -= Vector2f(view_dims.x / 2.0f, view_dims.y / 2.0f);
	}
	else {
		// Top centre
		position -= Vector2f(0.0f, view_dims.y / 2.0f);
	}
	_parent->setPosition(position + _healthBarZero * view_scale);
	healthText->SetPosition(position + _healthTextZero * view_scale);
	_weaponType->setPosition(position + _weaponTypeZero * view_scale);
	for (int i = 0; i < 8; i++) {
		_cooldowns.at(i)->setPosition(position + (_cooldownZero + Vector2f(_cooldownGap * i, 0.0f))  * view_scale);
	}
}

void HudComponent::render() {

}
