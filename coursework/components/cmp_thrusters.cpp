#include "cmp_thrusters.h"
#include "cmp_physics.h"


using namespace std;
using namespace sf;

shared_ptr<PhysicsComponent> phc;


ThrustersComponent::ThrustersComponent(Entity* p, const Vector2f& dim, const float& power) : Component(p)
{
	_startingOffsets[0] = Vector2f(0.0f, -dim.y);	// N
	_startingOffsets[1] = Vector2f(dim.x, -dim.y);	// NE
	_startingOffsets[2] = Vector2f(dim.x, dim.y);	// SE
	_startingOffsets[3] = Vector2f(0.0f, dim.y);	// S
	_startingOffsets[4] = Vector2f(-dim.x, dim.y);	// SW
	_startingOffsets[5] = Vector2f(-dim.x, -dim.y);	// NW

	_startingNormals[0] = Vector2f(0.0f, 1.0f);		// N
	_startingNormals[1] = Vector2f(-1.0f, 0.0f);	// NE
	_startingNormals[2] = Vector2f(-1.0f, 1.0f);	// SE
	_startingNormals[3] = Vector2f(0.0f, -1.0f);	// S
	_startingNormals[4] = Vector2f(1.0f, 0.0f);		// SW
	_startingNormals[5] = Vector2f(1.0f, 0.0f);		// NW

	_power = power;

	_parent = p;
	phc = p->GetCompatibleComponent<PhysicsComponent>()[0];
}


ThrustersComponent::~ThrustersComponent()
{
	phc.~shared_ptr();
}


void ThrustersComponent::update(double dt)
{
	// Rotates the thruster locations and normals
	float rot = deg2rad(-_parent->getRotation());
	for (int i = 0; i < 6; i++)
	{
		_offsets[i] = Vector2f(_startingOffsets[i].x * cos(rot) - _startingOffsets[i].y * sin(rot), _startingOffsets[i].x * sin(rot) + _startingOffsets[i].y * cos(rot));
		_normals[i] = Vector2f(_startingNormals[i].x * cos(rot) - _startingNormals[i].y * sin(rot), _startingNormals[i].x * sin(rot) + _startingNormals[i].y * cos(rot));
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (Keyboard::isKeyPressed(Keyboard::Space))
		fireThruster(5);
}


void ThrustersComponent::fireThruster(const int& index)
{
	phc->impulse(_normals[index] * _power, _offsets[index]);
}