#define _USE_MATH_DEFINES

#include "steering.h"
#include <math.h>

using namespace sf;

SteeringOutput Seek::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = atan2(steering.direction.y, steering.direction.x) + M_PI_2;
	return steering;
}

SteeringOutput Flee::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = atan2(steering.direction.y, steering.direction.x) + M_PI_2;
	return steering;
}

SteeringOutput Face::getSteering() const noexcept {
	SteeringOutput steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = atan2(steering.direction.y, steering.direction.x) + M_PI;
	return steering;
}