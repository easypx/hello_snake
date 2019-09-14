#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

struct SnakeSegment {
  SnakeSegment(float x, float y) : position(x, y) {}
  sf::Vector2f position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake {
public:
  Snake(int l_blockSize);
  ~Snake();
  // Helper methods
  void setDirection(Direction l_dir);
  Direction getDirection();
  void setSpeed(int speed);
  int getSpeed();
  sf::Vector2f getPosition();
  int getLives();
  int getScore();
  void increaseScore();
  void decreaseScore(int score);
  bool getLost();
  void setLost();                          // Handle losing here
  void toggleLost();                       // Bring it back to life
  void extend();                           // Grow the snake
  void resetPosition();                    // Reset to starting position
  void move();                             // Movement method
  void update();                           // Update method
  void render(sf::RenderWindow *l_window); // Renders the snake
  void checkSelfBite();                    // Checking for self biting
  void decreaseLives();
  void setLevel(int level) { m_level = level; }
  int getLevel() { return m_level; }
  void restart();

private:
  SnakeContainer m_snakeBody;    // Segment vector
  int m_size;                    // Size of the graphics
  Direction m_dir;               // Current direction
  int m_speed;                   // Speed of the snake
  int m_lives;                   // Lives
  int m_score;                   // Score
  bool m_lost;                   // Losing state
  sf::RectangleShape m_bodyRect; // Shape used in rendering
  int m_level;

  // TODO: All samples in one buffer
  sf::SoundBuffer m_sampleBuffer1;
  sf::SoundBuffer m_sampleBuffer2;
  sf::SoundBuffer m_sampleBuffer3;
  sf::SoundBuffer m_sampleBuffer4;
  sf::Sound m_soundEating;
  sf::Sound m_soundMoving;
  sf::Sound m_soundLoseLive;
  sf::Sound m_soundSelfBite;
  int m_moduloCount; // Helper counter for n-frames sampleplay
};

#endif // SNAKE_H
