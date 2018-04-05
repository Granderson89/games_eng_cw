#include "cmp_player_physics.h"
#include "system_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
  auto touch = getTouching();
  const auto& pos = _body->GetPosition();
  const float halfPlrHeigt = _size.y * .5f;
  const float halfPlrWidth = _size.x * .52f;
  b2WorldManifold manifold;
  for (const auto& contact : touch) {
    contact->GetWorldManifold(&manifold);
    const int numPoints = contact->GetManifold()->pointCount;
    bool onTop = numPoints > 0;
    // If all contacts are below the player.
    for (int j = 0; j < numPoints; j++) {
      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
    }
    if (onTop) {
      return true;
    }
  }

  return false;
}

void PlayerPhysicsComponent::update(double dt) {
  const auto pos = _parent->getPosition();

  //Teleport to start if we fall off map.
  //if (pos.y > ls::getHeight() * ls::getTileSize()) {
  //  teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
  //}

  if (im.Player[0].moveForward ||
	  im.Player[0].moveBackwards ||
	  im.Player[0].turnLeft ||
	  im.Player[0].turnRight) {
    // Moving Either Left or Right
    if (im.Player[0].turnRight) {
	  im.Player[0].turnRight = false;
	  if (_body->GetAngularVelocity() > -_maxVelocity.x)
		  _body->SetAngularVelocity(_body->GetAngularVelocity() + 2.0f * dt);
	}
	else if (im.Player[0].turnLeft) {
		im.Player[0].turnLeft = false;
		if (_body->GetAngularVelocity() < _maxVelocity.x)
			_body->SetAngularVelocity(_body->GetAngularVelocity() - 2.0f * dt);
	}
	else if (im.Player[0].moveBackwards) {
		im.Player[0].moveBackwards = false;
		if (getVelocity().y > -_maxVelocity.y) {
			Vector2f heading = Vector2f(cosf(_body->GetAngle()), sinf(_body->GetAngle()));
			impulse(heading * (float)(dt * _groundspeed));
		}
	}
	else {
		im.Player[0].moveForward = false;
		if (getVelocity().y > -_maxVelocity.y) {
			Vector2f heading = Vector2f(cosf(_body->GetAngle()), sinf(_body->GetAngle()));
			impulse(heading * -(float)(dt * _groundspeed));
		}
    }
  } else {
    // Dampen X axis movement
    dampen({1.0f, 1.0f});
  }

  // Handle Jump
  if (Keyboard::isKeyPressed(Keyboard::Up)) {
    _grounded = isGrounded();
    if (_grounded) {
      setVelocity(Vector2f(getVelocity().x, 0.f));
      teleport(Vector2f(pos.x, pos.y - 2.0f));
      impulse(Vector2f(0, -6.f));
    }
  }

  //Are we in air?
  if (!_grounded) {
    // Check to see if we have landed yet
    _grounded = isGrounded();
    // disable friction while jumping
    setFriction(0.f);
  } else {
    setFriction(0.1f);
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
                                               const Vector2f& size, int categoryBits, int mask)
    : PhysicsComponent(p, true, size, categoryBits, mask) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 400.f);
  _groundspeed = 30.f;
  _grounded = false;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
}
