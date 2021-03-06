#include "cmp_player_physics.h"
#include "system_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;


void PlayerPhysicsComponent::update(const double &dt) {
  const auto pos = _parent->getPosition();
  int player;
  if (_parent == player1.get()) {
	  player = 0;
  }
  else {
	  player = 1;
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
                                               const Vector2f& size, int categoryBits, vector<unsigned int> mask)
    : PhysicsComponent(p, true, size, categoryBits, mask) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 400.f);
  _speed = 30.f;
  _turningSpeed = 50.0f;
  _body->SetSleepingAllowed(false);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
}
