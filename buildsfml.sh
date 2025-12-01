#!/bin/bash
g++ src/*.cpp -Iinclude -Iheader -Llib \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
    -o bin/game && ./bin/game
