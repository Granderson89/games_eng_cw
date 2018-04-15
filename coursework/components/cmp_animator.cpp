#include "cmp_animator.h"

using namespace sf;
using namespace std;


AnimatorComponent::AnimatorComponent(Entity* p, shared_ptr<SpriteComponent> sc
	, Texture& spriteSheet, Vector2u size, float& length, int& frames) : Component(p)
{
	spr = sc;
	ir = IntRect(0, 0, size.x, size.y);
	tex = spriteSheet;
	this->length = length;
	this->frames = frames;
	originalTexture = *spr->getSprite().getTexture();
}


AnimatorComponent::~AnimatorComponent()
{
	spr.~shared_ptr();
}


void AnimatorComponent::start(bool repeating)
{
	animate = true;
	currentFrame = 0;
	this->repeating = repeating;
}


void AnimatorComponent::update(double dt)
{
	if (animate)
	{
		// Get the correct texture
		ir = IntRect(ir.width * currentFrame, 0, ir.width, ir.height);
		spr->getSprite().setTexture(tex);
		spr->getSprite().setTextureRect(ir);

		// Only switch to next animation frame if enough time has elapsed
		while (elapsed > length / (float)frames)
		{
			elapsed -= length / (float)frames;
			if (currentFrame >= frames - 1)
				if (repeating)
					currentFrame = 0;
				else
					stop();
			else
				currentFrame++;
		}
		elapsed += dt;
	}
}


void AnimatorComponent::stop()
{
	// Set the sprite component back to original texture
	spr->getSprite().setTexture(originalTexture, true);
}