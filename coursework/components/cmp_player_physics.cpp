#include "cmp_player_physics.h"
#include "system_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;


void PlayerPhysicsComponent::update(double dt) {
  const auto pos = _parent->getPosition();

  if (im.Player[0].moveForward ||
	  im.Player[0].moveBackwards ||
	  im.Player[0].turnLeft ||
	  im.Player[0].turnRight) {
    // Moving Either Left or Right
    if (im.Player[0].turnRight) {
	  im.Player[0].turnRight = false;
	  if (_body->GetAngularVelocity() > -_maxVelocity.x)
		  _body->ApplyAngularImpulse(_turningSpeed * dt, true);
	}
	else if (im.Player[0].turnLeft) {
		im.Player[0].turnLeft = false;
		if (_body->GetAngularVelocity() < _maxVelocity.x)
			_body->ApplyAngularImpulse(-_turningSpeed * dt, true);
	}
	else if (im.Player[0].moveBackwards) {
		im.Player[0].moveBackwards = false;
		if (getVelocity().y > -_maxVelocity.y) {
			Vector2f heading = Vector2f(-sinf(_body->GetAngle()), cosf(_body->GetAngle()));
			impulse(heading * (float)(dt * _speed));
		}
	}
	else {
		im.Player[0].moveForward = false;
		if (getVelocity().y > -_maxVelocity.y) {
			Vector2f heading = Vector2f(-sinf(_body->GetAngle()), cosf(_body->GetAngle()));
			impulse(heading * -(float)(dt * _speed));
		}
    }
  } else {
    // Dampen X axis movement
    dampen({1.0f, 1.0f});
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
                                               const Vector2f& size)
    : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 400.f);
  _speed = 30.f;
  _turningSpeed = 50.0f;
  _body->SetSleepingAllowed(false);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
}
