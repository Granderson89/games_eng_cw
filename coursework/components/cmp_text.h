#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
  TextComponent() = delete;
  explicit TextComponent(Entity* p, const std::string& str = "");
  void update(const double &dt) override;

  void render() override;

  ~TextComponent() override = default;

  void SetText(const std::string& str);
  void AddText(const std::string& str);
  void SetPosition(sf::Vector2f& pos);

  void Highlight();
  void NoHighlight();
  void SetScale(const float scale);
  void SetColor(sf::Color color);

protected:
  std::shared_ptr<sf::Font> _font;
  std::string _string;
  sf::Text _text;
};
