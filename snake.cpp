#include "snake.hpp"

Snake::Snake(int l_blockSize) {
  m_size = l_blockSize;
  m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
  m_speed = 1; // Not used yet
  m_lives = 3;
  m_score = 0;
  m_lost = false;
  m_level = 1;
  m_moduloCount = 0;

  m_sampleBuffer1.loadFromFile("apple_bite.wav");
  m_soundEating.setBuffer(m_sampleBuffer1);

  m_sampleBuffer2.loadFromFile("scratch.wav");
  m_soundMoving.setBuffer(m_sampleBuffer2);

  m_sampleBuffer3.loadFromFile("bite.wav");
  m_soundSelfBite.setBuffer(m_sampleBuffer3);

  m_sampleBuffer4.loadFromFile("water_splash.wav");
  m_soundLoseLive.setBuffer(m_sampleBuffer4);

  resetPosition();
}

Snake::~Snake() {}

void Snake::resetPosition() {
  m_snakeBody.clear();
  m_snakeBody.push_back(SnakeSegment(5, 7));
  m_snakeBody.push_back(SnakeSegment(5, 6));
  m_snakeBody.push_back(SnakeSegment(5, 5));
  setDirection(Direction::None); // Start off still.
}

void Snake::restart() {
  m_speed = 1;
  m_lives = 3;
  m_score = 0;
  m_lost = false;
  m_level = 1;
  m_moduloCount = 0;
  resetPosition();
}

void Snake::setDirection(Direction l_dir) { m_dir = l_dir; }

Direction Snake::getDirection() { return m_dir; }

int Snake::getSpeed() { return m_speed; }

sf::Vector2f Snake::getPosition() {
  return (!m_snakeBody.empty() ? m_snakeBody.front().position
                               : sf::Vector2f(1, 1));
}

void Snake::setSpeed(int speed) { m_speed += speed; }

int Snake::getLives() { return m_lives; }

int Snake::getScore() { return m_score; }

void Snake::increaseScore() {
  m_score += (10 * m_level);
  if (m_score >= m_level * 500) {
    // m_speed += 1; // NOTE: Speed increase don't work yet!
    m_level++;
  }
  // sound1.setBuffer(buffer1);
  m_soundEating.setVolume(100.0);
  m_soundEating.play();
}

void Snake::decreaseScore(int score) {
  m_score -= score;
  if (m_score < 0)
    m_score = 0;
}

bool Snake::getLost() { return m_lost; }

void Snake::setLost() { m_lost = true; }

void Snake::toggleLost() { m_lost = !m_lost; }

void Snake::decreaseLives() {
  std::cout << "Lost a live!" << endl;
  --m_lives;
  if (m_lives == 0) {
    setLost();
    std::cout << "Lose!" << endl;
  }
  m_soundLoseLive.setVolume(100.0);
  m_soundLoseLive.play();
  resetPosition();
}

void Snake::extend() {
  if (m_snakeBody.empty()) {
    return;
  }
  SnakeSegment &tail_head = m_snakeBody[m_snakeBody.size() - 1];
  if (m_snakeBody.size() > 1) {
    SnakeSegment &tail_bone = m_snakeBody[m_snakeBody.size() - 2];
    if (tail_head.position.x == tail_bone.position.x) {
      if (tail_head.position.y > tail_bone.position.y) {
        m_snakeBody.push_back(
            SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
      } else {
        m_snakeBody.push_back(
            SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
      }
    } else if (tail_head.position.y == tail_bone.position.y) {
      if (tail_head.position.x > tail_bone.position.x) {
        m_snakeBody.push_back(
            SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
      } else {
        m_snakeBody.push_back(
            SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
      }
    }
  } else {
    if (m_dir == Direction::Up) {
      m_snakeBody.push_back(
          SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
    } else if (m_dir == Direction::Down) {
      m_snakeBody.push_back(
          SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
    } else if (m_dir == Direction::Left) {
      m_snakeBody.push_back(
          SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
    } else if (m_dir == Direction::Right) {
      m_snakeBody.push_back(
          SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
    }
  }
}

void Snake::update() {
  if (m_snakeBody.empty()) {
    return;
  }
  if (m_dir == Direction::None) {
    return;
  }
  move();
  checkSelfBite();
}

void Snake::move() {
  for (int i = m_snakeBody.size() - 1; i > 0; --i) {
    m_snakeBody[i].position = m_snakeBody[i - 1].position;
  }
  if (m_dir == Direction::Left) {
    --m_snakeBody[0].position.x;
  } else if (m_dir == Direction::Right) {
    ++m_snakeBody[0].position.x;
  } else if (m_dir == Direction::Up) {
    --m_snakeBody[0].position.y;
  } else if (m_dir == Direction::Down) {
    ++m_snakeBody[0].position.y;
  }
  // We play movement sound only every 5 frames
  // Is there a better way?
  ++m_moduloCount;
  if (m_moduloCount % 5 == 0) {
    // sound2.setBuffer(buffer2);
    m_soundMoving.setVolume(50.0);
    m_soundMoving.play();
    m_moduloCount = 0;
  }
}

// NOTE: This is not classic snake. If you bite yourself, you are going to be shorter and lose points.
void Snake::checkSelfBite() {
  // What's that?
  /*if (m_snakeBody.size() < 5) {
    return;
  }*/

  // Checking wall collisions are done in World::Update(...)!

  // Snake bites itself & decrease score by 50
  SnakeSegment &head = m_snakeBody.front();
  for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
    if (itr->position == head.position) {
      int segments = m_snakeBody.end() - itr;
      for (int i = 0; i < segments; ++i) {
          m_snakeBody.pop_back();
      }
      std::cout << "Bite! Decrease score by " <<  segments * 10 << " points!" << endl;
      decreaseScore(segments * 10);
      m_soundSelfBite.setVolume(100.0);
      m_soundSelfBite.play();
      break;
    }
  }
}

void Snake::render(sf::RenderWindow *l_window) {
  if (m_snakeBody.empty()) {
    return;
  }
  auto head = m_snakeBody.begin();
  m_bodyRect.setFillColor(sf::Color::Yellow);
  m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
  l_window->draw(m_bodyRect);
  m_bodyRect.setFillColor(sf::Color::Green);
  for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
    m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
    l_window->draw(m_bodyRect);
  }
}
