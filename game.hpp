#ifndef GAME_H
#define GAME_H

#include "snake.hpp"
#include "textbox.hpp"
#include "world.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum state { TITLE, RUN, PAUSE, END };

class Game {
public:
  Game();
  ~Game();
  void render();
  void update(int state);
  void handleInput();
  void run();
  void toggleFullscreen();
  void create();
  sf::RenderWindow *GetWindow() { return m_window; };
  // Do we need the following methods?
  bool getIsDone() { return m_isDone; }
  void setIsDone(bool isDone) { m_isDone = isDone; }
  int getState() { return m_state; }
  void setState(int state) { m_state = state; }

private:
  int m_state; // Game state
  bool m_isDone; // Game window state
  sf::RenderWindow *m_window; // The actual game window
  World *m_world;
  Snake *m_snake;
  Textbox *m_textbox;
  float m_frameRate; // in fps
  int m_level;
  sf::Text m_gameInformation;
  sf::Font m_font;
  bool m_isFullscreen;
  Direction m_lastDirection; // Store last direction

  sf::Clock m_clock;
  sf::Time m_elapsed;
  float m_lag;

  sf::SoundBuffer m_sampleBuffer1;
  sf::Sound m_soundIntroMusic;
  sf::SoundBuffer m_sampleBuffer2;
  sf::Sound m_soundGameOver;
  sf::Music m_musicAtmosphere;
};

#endif // GAME_H
