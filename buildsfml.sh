#!/bin/bash
g++ $(find src -name '*.cpp') -Iinclude -Iheader -Llib \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
    -o bin/game && ./bin/game
