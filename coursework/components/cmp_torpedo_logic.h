#pragma once

#include "ecm.h"
#include "../game.h"
#include <SFML/Audio.hpp>

class TorpedoComponent : public Component {
protected:
	static float max_lifespan;
	static float strength;
	static float damage_range;
	static float speed;
	static sf::SoundBuffer explosionBuffer;
	static sf::Sound explosionSound;

	shared_ptr<Entity> _target;
	float _current_lifespan;



public:
	TorpedoComponent() = delete;
	explicit TorpedoComponent(Entity* p, shared_ptr<Entity> target, Vector2f direction);

	void explode();

	void update(const double &dt) override;
	void render() override;

	static void loadSounds();
};
