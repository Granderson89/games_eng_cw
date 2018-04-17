#include "cmp_thrusters.h"
#include <maths.h>
#include "../input_manager.h"


using namespace std;
using namespace sf;


// Sounds
sf::SoundBuffer ThrustersComponent::thrustBuffer;
sf::Sound ThrustersComponent::thrustSound;

ThrustersComponent::ThrustersComponent(Entity* p, const Vector2f& dim, const float& power) : Component(p)
{
	float x = dim.x / 2.0f;
	float y = dim.y / 2.0f;
	_startingOffsets[0] = Vector2f(0.0f, -y);	// N
	_startingOffsets[1] = Vector2f(x, -y);		// NE
	_startingOffsets[2] = Vector2f(x, y);		// SE
	_startingOffsets[3] = Vector2f(0.0f, y);	// S
	_startingOffsets[4] = Vector2f(-x, y);		// SW
	_startingOffsets[5] = Vector2f(-x, -y);		// NW

	_startingNormals[0] = Vector2f(0.0f, 1.0f);		// N
	_startingNormals[1] = Vector2f(-1.0f, 0.0f);	// NE
	_startingNormals[2] = Vector2f(-1.0f, 0.0f);	// SE
	_startingNormals[3] = Vector2f(0.0f, -1.0f);	// S
	_startingNormals[4] = Vector2f(1.0f, 0.0f);		// SW
	_startingNormals[5] = Vector2f(1.0f, 0.0f);		// NW

	_power = power;

	_parent = p;
	for (set<string>::iterator it = p->getTags().begin(); it != p->getTags().end(); ++it)
		if (*it == "p1")
		{
			pl = 0;
		}
	phc = p->GetCompatibleComponent<PhysicsComponent>()[0];

	for (auto &f : _firing)
		f = false;

	anims = p->GetCompatibleComponent<AnimatorComponent>();
}


ThrustersComponent::~ThrustersComponent()
{
//	phc.~shared_ptr();
	for (auto &a : anims)
		a.~shared_ptr();
	anims.clear();
}


void ThrustersComponent::update(double dt)
{
	// Rotates the thruster locations and normals
	for (int i = 0; i < 6; i++)
	{
		_offsets[i] = rotate(_startingOffsets[i], _parent->getRotation());
		_normals[i] = rotate(_startingNormals[i], _parent->getRotation());
	}

	for (int i = 0; i < 6; i++)
	{
		if (InputManager::Player[pl].thrusterOn[i])
		{
			if (i == 0 || i == 3)
				phc->impulse(_normals[i] * _power * 2.0f * (float)dt, _parent->getPosition() + _offsets[i]);
			else
				phc->impulse(_normals[i] * _power * (float)dt, _parent->getPosition() + _offsets[i]);
			if (!_firing[i])
			{
				anims[i]->start(true);
				_firing[i] = true;
			}
		}
		else
		{
			anims[i]->stop();
			_firing[i] = false;
		}
	}
	for (auto f : _firing)
	{
		if (f == true)
		{
			if (thrustSound.getStatus() != SoundSource::Status::Playing)
				thrustSound.play();
			break;
		}
	}
}

void ThrustersComponent::loadSounds()
{
	thrustBuffer.loadFromFile("res/sounds/thrust.wav");
	thrustSound.setBuffer(thrustBuffer);
}