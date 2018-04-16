
#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _offset(sf::Vector2f(0.0f, 0.0f)), _rotationOffset(0.0f), _sprite(make_shared<sf::Sprite>()) {}

SpriteComponent::SpriteComponent(Entity* p, float rotation)
    : Component(p), _rotationOffset(rotation), _sprite(make_shared<sf::Sprite>()) {}

SpriteComponent::SpriteComponent(Entity* p, float rotation, bool rotationIndependent)
	: Component(p), _rotationOffset(rotation), _rotationIndependent(rotationIndependent), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
  _sprite->setPosition(_parent->getPosition() + rotate(_offset, _parent->getRotation()));
  if (!_rotationIndependent) {
	  _sprite->setRotation(_parent->getRotation() + _rotationOffset);
  }
  else {
	  _sprite->setRotation(_rotationOffset);
  }
}

void SpriteComponent::render() { if (_visible) Renderer::queue(_sprite.get()); }

void ShapeComponent::update(double dt) {
  _shape->setPosition(_parent->getPosition());
  _shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
    : Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

void SpriteComponent::toPort()
{
	_rotationOffset = -90.0f;
	if (_offset.x > 0.0f) {
		_offset.x *= -1.0f;
	}
}

void SpriteComponent::toStarboard()
{
	_rotationOffset = 90.0f;
	if (_offset.x < 0.0f) {
		_offset.x *= -1.0f;
	}
}

void SpriteComponent::rotateOffset(float dt)
{
	_rotationOffset += dt;
}

float SpriteComponent::getRotationOffset()
{
	return _rotationOffset;
}

void SpriteComponent::setOffset(sf::Vector2f offset)
{
	_offset = offset;
}

void SpriteComponent::setRotationOffset(float offset)
{
	_rotationOffset = offset;
}

void SpriteComponent::setVisible(bool visible)
{
	_visible = visible;
}
