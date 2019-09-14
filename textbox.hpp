#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class Textbox {
public:
  Textbox();
  Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
  ~Textbox();
  void setup(int l_visible, int l_charSize, int l_width,
             sf::Vector2f l_screenPos);
  void add(std::string l_message);
  void clear();
  void render(sf::RenderWindow *l_wind);

private:
  MessageContainer m_messages;
  int m_numVisible;
  sf::RectangleShape m_backdrop;
  sf::Font m_font;
  sf::Text m_content;
};

#endif // TEXTBOX_H
