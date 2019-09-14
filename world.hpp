#ifndef WORLD_H
#define WORLD_H

#include "snake.hpp"
#include <SFML/Graphics.hpp>

class World {
public:
  World(sf::Vector2u l_windSize);
  ~World();
  int getBlockSize();
  void respawnApple();
  void update(Snake *l_player);
  void render(sf::RenderWindow *l_window);

private:
  sf::Vector2u m_windowSize;
  sf::Vector2f m_item;
  int m_blockSize;
  sf::CircleShape m_appleShape;
  sf::RectangleShape m_bounds[4];
};

#endif // WORLD_H
