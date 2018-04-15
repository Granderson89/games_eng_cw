#pragma once
#include <SFML\Graphics.hpp>
#include "ecm.h"
#include "cmp_sprite.h"


// This component is meant to be attached to a dummy Entity as it only needs to run once per frame after being properly initialized
class AnimatorComponent : public Component
{
private:
	std::shared_ptr<SpriteComponent> spr;	// Sprite component of the parent entity
	sf::IntRect ir;							// Stores the sprite position in the spritesheet
	sf::Texture tex;						// Animation texture
	float length;							// Duration of a single animation loop
	float elapsed = 0.0f;					// Time elapsed since last animation frame
	int frames;								// Number of animation frames
	int currentFrame;						// Current animation frame
	bool animate = false;					// Whether the animation is currently active
	sf::Texture originalTexture;			// Non-animated texture of the entity
	bool repeating;							// Whether or not to repeat the animation after a full loop
public:
	explicit AnimatorComponent(Entity* p, std::shared_ptr<SpriteComponent> sc
		, sf::Texture& spriteSheet, sf::Vector2u size, float& length, int& frames);
	AnimatorComponent() = delete;
	~AnimatorComponent();

	void update(double dt) override;
	void render() override {}

	// Starts the animation. Animation stops after reaching the end if repeating is false
	void start(bool repeating);
	// Stops the animation
	void stop();
};