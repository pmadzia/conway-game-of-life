#pragma once
#include "raylib.h"
#include "grid.h"
#include "constans.h"

class Game {
public:
    Game()
    : grid {
        constants::screenWidth,
        constants::screenHeight,
        constants::cellSize},
    isRunning {true},
    background {BLACK} {}; 

    void init();
    void gameLoop();
    void draw();
    void drawPause();
    void populateCells();
    void checkForInput();
    void update();
    void changeCellStatus(int row, int column);
    int countNeighbours(int row, int column);

private:
    Grid grid;
    Grid nextGrid;
    bool isRunning;
    Color background;
};
