#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;
  sf::Vector2f _offset;
  float _rotationOffset;
  bool _visible = true;
  bool _rotationIndependent = false;

public:
  SpriteComponent() = delete;

  explicit SpriteComponent(Entity* p);
  explicit SpriteComponent(Entity* p, float rotation);
  explicit SpriteComponent(Entity* p, float rotation, bool rotationIndependent);

  void update(double dt) override;
  void render() override;

  sf::Sprite& getSprite() const;
  void toPort();
  void toStarboard();
  void rotateOffset(float);
  float getRotationOffset();

  void setOffset(sf::Vector2f);
  void setRotationOffset(float);
  void setVisible(bool);

  template <typename... Targs> void setSprite(Targs... params) {
    _sprite.reset(new sf::Sprite(params...));
  }
};

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
  // sf::Shape _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void update(double dt) override;
  void render() override;
  sf::Shape& getShape() const;
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};