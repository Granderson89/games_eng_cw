#pragma once

#include "cmp_physics.h"

using namespace std;

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;

public:
  float _speed;
  float _turningSpeed;

  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size, int categoryBits, vector<unsigned int> mask);

  PlayerPhysicsComponent() = delete;
};
