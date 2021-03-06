#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(const double &dt) {}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _text.setPosition(_parent->getPosition());
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

void TextComponent::AddText(const std::string& str) {
	_string = str;
	_text.setString(_text.getString() + _string);
}

void TextComponent::SetPosition(sf::Vector2f & pos)
{
	_text.setPosition(pos);
}

void TextComponent::Highlight() {
	_text.setColor(sf::Color::Red);
}

void TextComponent::NoHighlight() {
	_text.setColor(sf::Color::White);
}

void TextComponent::SetScale(const float scale)
{
	_text.setScale(sf::Vector2f(scale, scale));
}

void TextComponent::SetColor(sf::Color color) {
	_text.setColor(color);
}