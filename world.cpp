#include "world.hpp"

World::World(sf::Vector2u l_windSize) {
  m_blockSize = 16;
  m_windowSize = l_windSize;
  respawnApple();
  m_appleShape.setFillColor(sf::Color::Red);
  m_appleShape.setRadius(m_blockSize / 2);
  for (int i = 0; i < 4; ++i) {
    m_bounds[i].setFillColor(sf::Color::Blue);
    if (!((i + 1) % 2)) {
      m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
    } else {
      m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
    }
    if (i < 2) {
      m_bounds[i].setPosition(0, 0);
    } else {
      m_bounds[i].setOrigin(m_bounds[i].getSize());
      m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
    }
  }
}

World::~World() {}

void World::respawnApple() {
  int maxX = (m_windowSize.x / m_blockSize) - 2;
  int maxY = (m_windowSize.y / m_blockSize) - 2;
  m_item = sf::Vector2f(rand() % maxX + 1, rand() % maxY + 1);
  m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}

void World::update(Snake *l_player) {
  if (l_player->getPosition() == m_item) {
    l_player->extend();
    l_player->increaseScore();
    respawnApple();
  }
  int gridSize_x = m_windowSize.x / m_blockSize;
  int gridSize_y = m_windowSize.y / m_blockSize;
  if (l_player->getPosition().x <= 0 || l_player->getPosition().y <= 0 ||
      l_player->getPosition().x >= gridSize_x - 1 ||
      l_player->getPosition().y >= gridSize_y - 1) {
    // l_player.Lose();
    l_player->decreaseLives();
    if (l_player->getLives() == 0)
      l_player->setLost();
  }
}

void World::render(sf::RenderWindow *l_window) {
  for (int i = 0; i < 4; ++i) {
    l_window->draw(m_bounds[i]);
  }
  l_window->draw(m_appleShape);
}

int World::getBlockSize() { return m_blockSize; }
