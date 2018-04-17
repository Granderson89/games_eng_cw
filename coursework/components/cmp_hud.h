#pragma once

#include "ecm.h"

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


public:
	explicit HudComponent(Entity* p, std::shared_ptr<Entity> player, 
		std::shared_ptr<Entity> weaponType, std::vector<std::shared_ptr<Entity>> cooldowns, 
		std::shared_ptr<Entity> camera);
	HudComponent() = delete;

	void update(const double &dt) override;
	void render() override;
};