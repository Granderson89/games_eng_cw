#pragma once

#include "ecm.h"
#include "../game.h"
#include <SFML/Audio.hpp>

class PlasmaComponent : public Component {
protected:
	static float max_lifespan;
	static float max_strength;
	static float speed;
	static sf::SoundBuffer explosionBuffer;
	static sf::Sound explosionSound;

	Entity* _target;
	float _current_strength;
	float _current_lifespan;

public:
	PlasmaComponent() = delete;
	explicit PlasmaComponent(Entity* p, Entity* target, Vector2f direction);

	void reduceStrength();

	void update(double dt) override;
	void render() override;

	static void loadSounds();
};
