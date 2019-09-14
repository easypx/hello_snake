TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        game.cpp \
        main.cpp \
        snake.cpp \
        textbox.cpp \
        world.cpp

HEADERS += \
    game.hpp \
    snake.hpp \
    textbox.hpp \
    world.hpp

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
