/*
 * "Hello Snake"
 * Book: SFML Game Development by Example (PACKT Pubishing)
 * fixed some errors/issues
 * 09/2019 easy_p
 *
*/

#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <unistd.h>

int main(__attribute__((unused)) int argc,
         __attribute__((unused)) char *argv[]) {
  // Program entry point
  Game *game = new Game(); // Creating our game object.
  game->run();
  /* Because we get the error on exit: "AL lib: (EE) alc_cleanup: 1 device not
  * closed", i tried to wait for destroying audio objects, but it's not going to
  * work so far. Anyway, the error is harmeless.
  */
  // usleep(2000000);
  return 0;
}
