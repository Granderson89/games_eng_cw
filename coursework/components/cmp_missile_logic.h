#pragma once

#include "../game.h"
#include <SFML/Audio.hpp>

using namespace sf;

class MissileComponent : public Component {
protected:
	static float strength;
	static float speed;
	static sf::SoundBuffer explosionBuffer;
	static sf::Sound explosionSound;

	shared_ptr<Entity> _target;

public:
	MissileComponent() = delete;
	explicit MissileComponent(Entity* p, shared_ptr<Entity> target);

	void explode();
	float getSpeed();

	void update(double dt) override;
	void render() override;

	static void loadSounds();
};
