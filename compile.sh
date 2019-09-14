# compiles and runs the program

g++ -c main.cpp game.cpp world.cpp snake.cpp  textbox.cpp
g++ main.o game.o world.o snake.o  textbox.o -o snake -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./snake