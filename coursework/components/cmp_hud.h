#pragma once

#include "ecm.h"
#include "cmp_player_state.h"
#include "cmp_weapon_component.h"
#include "cmp_camera.h"
#include "cmp_text.h"

class HudComponent : public Component {
private:
	std::shared_ptr<Entity> _player;
	std::shared_ptr<Entity> _weaponType;
	std::vector<std::shared_ptr<Entity>> _cooldowns;
	std::shared_ptr<Entity> _camera;

	sf::Vector2f _healthBarZero;
	sf::Vector2f _healthTextZero;
	sf::Vector2f _healthBarScale;
	sf::Vector2f _healthBarBgScale;

	sf::Vector2f _weaponTypeZero;
	float _weaponTypeScale;

	sf::Vector2f _cooldownZero;
	float _cooldownGap;
	float _cooldownScale;
	float _timerScale;

	std::shared_ptr<CameraControllerComponent> cameraComp;
	std::shared_ptr<PlayerStateComponent> state;
	std::vector<std::shared_ptr<WeaponComponent>> weapons;
	std::shared_ptr<TextComponent> healthText;
	std::shared_ptr<ShapeComponent> healthBarBg;
	std::shared_ptr<ShapeComponent> healthBar;
	std::shared_ptr<SpriteComponent> weaponTypeSpr;
	std::vector<std::shared_ptr<SpriteComponent>> cooldownSpr;
	std::vector<std::shared_ptr<ShapeComponent>> timerSpr;


public:
	explicit HudComponent(Entity* p, std::shared_ptr<Entity> player, 
		std::shared_ptr<Entity> weaponType, std::vector<std::shared_ptr<Entity>> cooldowns, 
		std::shared_ptr<Entity> camera);
	HudComponent() = delete;

	void update(const double &dt) override;
	void render() override;
};