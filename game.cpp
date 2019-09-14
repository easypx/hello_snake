// TODO: Sprites, textures, levels, cleanup

#include "game.hpp"

Game::Game() { this->create(); }

Game::~Game() {
  delete m_window;
  delete m_world;
  delete m_snake;
  delete m_textbox;
};

void Game::create() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 2;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.minorVersion = 2.0;
  settings.majorVersion = 3.0;

  auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
  m_window = new sf::RenderWindow(sf::VideoMode(640, 480), "Hello Snake", style,
                                  settings);
  m_frameRate = 10.0; // fps
  m_window->setFramerateLimit(m_frameRate);
  // Synch with graphics card vsync which limits framerate to vsync (default:
  // false)
  m_window->setVerticalSyncEnabled(false);
  m_window->setActive(); // Set focus to game window

  m_world = new World(sf::Vector2u(640, 480)); // New world (level design)

  m_snake = new Snake(m_world->getBlockSize()); // New snake

  m_textbox = new Textbox(); // New information overlay display
  m_textbox->setup(5, 14, 350, sf::Vector2f(0, 1));

  m_font.loadFromFile("arial.ttf");
  m_gameInformation.setFont(m_font);
  m_gameInformation.setCharacterSize(10); // In pixels, not points!
  m_gameInformation.setPosition(0, m_window->getSize().y - 15);
  m_gameInformation.setString(
      "Hello Snake version 20190912 (Book: SFML Game "
      "Development by Example), made it work, easy_p 09/2019");

  m_isDone = false; // Game window state

  m_state = TITLE; // Game logic state

  m_lastDirection = Direction::None; // Snakes last direction

  // TODO: All samples in one buffer
  /*m_sampleBuffer1.loadFromFile("intro_music.wav");
  m_soundIntroMusic.setBuffer(sampleBuffer1);
  m_soundIntroMusic.setLoop(true);
  m_soundIntroMusic.play();*/

  m_sampleBuffer2.loadFromFile("game_over.wav");
  m_soundGameOver.setBuffer(m_sampleBuffer2);
  m_soundGameOver.setVolume(100.0);

  m_musicAtmosphere.openFromFile("atmosphere.wav");
  m_musicAtmosphere.setLoop(true);
  m_musicAtmosphere.play();
}

void Game::handleInput() {
  float t1 = m_clock.getElapsedTime().asSeconds();
  // Let's check for keyboard events asynchronously to get precise control
  while ((m_clock.getElapsedTime().asSeconds() - t1) < 1.0f / m_frameRate) {
    sf::Event event;
    while (m_window->pollEvent(event)) {
      // cout << event.key.code << endl;
      // Windows events
      if (event.type == sf::Event::Closed) {
        // Close game
        std::cout << "End!" << endl;
        std::cout << "Level: " << m_snake->getLevel() << endl;
        std::cout << "Score: " << m_snake->getScore() << endl;
        std::cout << "I hope you had fun!" << endl;
        // m_window->close();
        m_isDone = true;
      }
      // Keyboard events
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Q:
          // Close game
          std::cout << "End!" << endl;
          std::cout << "Level: " << m_snake->getLevel() << endl;
          std::cout << "Score: " << m_snake->getScore() << endl;
          std::cout << "I hope you had fun!" << endl;
          // m_window->close();
          m_isDone = true;
        case sf::Keyboard::F:
          // Toggle fullscreen
          // ATTENTION: Crashes on raspi 3!
          // NOTE: On some systems f11 works out of the box so i left it out.
          // this->toggleFullscreen();
          break;
        case sf::Keyboard::S:
          // Restart game
          m_state = RUN;
          m_snake->restart();
          m_snake->setDirection(Direction::Down);
          m_soundGameOver.stop();
          break;
        case sf::Keyboard::P:
          // Pause game toggle switch
          if (m_state == RUN) {
            m_state = PAUSE;
            m_lastDirection = m_snake->getDirection();
            m_snake->setDirection(Direction::None);
          } else if (m_state == PAUSE) {
            m_state = RUN;
            m_snake->setDirection(m_lastDirection);
          }
          break;
        case sf::Keyboard::Up:
          if (m_snake->getDirection() != Direction::Down) {
            m_snake->setDirection(Direction::Up);
          }
          break;
        case sf::Keyboard::Down:
          if (m_snake->getDirection() != Direction::Up) {
            m_snake->setDirection(Direction::Down);
          }
          break;
        case sf::Keyboard::Left:
          if (m_snake->getDirection() != Direction::Right) {
            m_snake->setDirection(Direction::Left);
          }
          break;
        case sf::Keyboard::Right:
          if (m_snake->getDirection() != Direction::Left) {
            m_snake->setDirection(Direction::Right);
          }
          break;
        default:
          break;
        }
      }
    }
  }
}

void Game::update(int state) {

  // Calculate framerate
  /*float frameRate = 1.f / clock1.getElapsedTime().asSeconds();
  clock1.restart();
  cout << Framerate: << frameRate << endl;*/

  if (m_snake->getLost() && m_state != END) {
    m_state = END;
    m_soundGameOver.play();
    // m_musicAtmosphere.stop();
  }

  switch (state) {
  case TITLE:
    m_textbox->clear();
    m_textbox->add("Welcome to Hello Snake. Press S to start!");
    break;
  case RUN:
    m_textbox->clear();
    // m_textbox->Add("Framerate: " + std::to_string(frameRate) + " fps");
    m_textbox->add("Level: " + std::to_string(m_snake->getLevel()));
    m_textbox->add("Lives: " + std::to_string(m_snake->getLives()));
    m_textbox->add("Scores: " + std::to_string(m_snake->getScore()));
    m_snake->update();
    m_world->update(m_snake);
    break;
  case PAUSE:
    m_textbox->clear();
    m_textbox->add("Pause game. Press P to go on!");
    break;
  case END:
    m_textbox->clear();
    // m_textbox->Add("Framerate: " + std::to_string(frameRate) + " fps");
    m_textbox->add("Level: " + std::to_string(m_snake->getLevel()));
    m_textbox->add("Lives: " + std::to_string(m_snake->getLives()));
    m_textbox->add("Scores: " + std::to_string(m_snake->getScore()));
    m_textbox->add("Game over! Press S to restart or Q to quit!");
    break;
  default:
    break;
  }
}

void Game::render() {
  m_window->clear(sf::Color(0, 80, 0)); // Clear screen
  // Render all drawables objects here by passing a pointer to the game window
  m_world->render(m_window);
  m_snake->render(m_window);
  m_textbox->render(m_window);
  m_window->draw(m_gameInformation); // Bottom text informations

  m_window->display(); // Finally display image
}

void Game::run() {
  while (!getIsDone()) {
    // Game loop
    // TODO: Framerate limitation with timer aside global framerate setting?

    // lag = clock2.restart().asSeconds();
    // while (lag > 1.f / m_frameRate) {
    handleInput();
    update(m_state);
    render();
    // lag -= 1.f / m_frameRate;
    // }
  }

}

// TODO: Fullscreen toggling crashes on raspi3
void Game::toggleFullscreen() {
  m_isFullscreen = !m_isFullscreen;
  m_window->close();
  create();
}
