#include "cmp_thrusters.h"
#include "cmp_physics.h"
#include <maths.h>


using namespace std;
using namespace sf;

shared_ptr<PhysicsComponent> phc;


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
	phc = p->GetCompatibleComponent<PhysicsComponent>()[0];

	for (auto &f : _firing)
		f = false;
}


ThrustersComponent::~ThrustersComponent()
{
	phc.~shared_ptr();
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
		if (_firing[i])
			phc->impulse(_normals[i] * _power * (float)dt, _parent->getPosition() - _offsets[i]);
		_firing[i] = false;
	}


	/////////////// to be removed later ///////////////////////////////////////////////////////////////////////////////
	if (Keyboard::isKeyPressed(Keyboard::Numpad8))
	{
		fireThruster(0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Numpad9))
	{
		fireThruster(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Numpad3))
	{
		fireThruster(2);
	}
	if (Keyboard::isKeyPressed(Keyboard::Numpad2))
	{
		fireThruster(3);
	}
	if (Keyboard::isKeyPressed(Keyboard::Numpad1))
	{
		fireThruster(4);
	}
	if (Keyboard::isKeyPressed(Keyboard::Numpad7))
	{
		fireThruster(5);
	}
}


void ThrustersComponent::fireThruster(const int& index)
{
	//phc->impulse(_normals[index] * _power, _parent->getPosition() - _offsets[index]);
	_firing[index] = true;
}