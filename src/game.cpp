#include "game.h"

void Game::init() {
    InitWindow(constants::screenWidth, constants::screenHeight, constants::title);
    SetTargetFPS(constants::FPS);
    populateCells();
    gameLoop();
}

void Game::gameLoop() {
    while(!WindowShouldClose()) {
        checkForInput();
        draw();
        if (isRunning) update();
    }
    CloseWindow();
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(background);
    grid.drawGrid();
    if (!isRunning) drawPause();
    EndDrawing();
}

void Game::drawPause() {
    DrawText("PAUSE", constants::screenWidth - 100,
        constants::screenHeight - (constants::screenHeight - 40), 20, WHITE);
}

void Game::populateCells() {
    for (int row = 0; row < grid.getRows(); row++) {
        for (int column = 0; column < grid.getColumns(); column++) {
            int randomValue = GetRandomValue(0, 5);
            grid.getCells()[row][column] = 1 ? randomValue == 1 : 0;
        }
    }
}

void Game::changeCellStatus(int row, int column) {
    grid.getCells()[row][column] = !grid.getCells()[row][column];
}

int Game::countNeighbours(int row, int column) {
    int neighboursPossibility[8][2] = {
        {-1, 0},    // Above
        {1, 0},     // Below
        {0, -1},    // To left
        {0, 1},     // To right
        {-1, -1},   // Upper left
        {-1, 1},    // Upper right
        {1, -1},    // Lower left
        {1, 1}      // Lower right
    };
    int aliveNeighbours = 0;
    for (const auto& position : neighboursPossibility) {
        int neighbourRow = row + position[0];
        int neighbourColumn = column + position[1];
        if (0 < neighbourRow && neighbourRow < grid.getRows()
            && 0 < neighbourColumn && neighbourColumn < grid.getColumns()) {
            aliveNeighbours += grid.getCellStaus(neighbourRow, neighbourColumn);
        }
    }
    return aliveNeighbours;
}

void Game::update() {
    nextGrid = grid;
    for (int row = 0; row < grid.getRows(); row++) {
        for (int column = 0; column < grid.getColumns(); column++) {
            int cellAlive = grid.getCellStaus(row, column);
            int numberOfNeighbours = countNeighbours(row, column);
            if (cellAlive) {
                if (numberOfNeighbours < 2 || numberOfNeighbours > 3) {
                    nextGrid.setCellStaus(row, column, 0);
                } else nextGrid.setCellStaus(row, column, 1);
            } else {
                if (numberOfNeighbours == 3) {
                    nextGrid.setCellStaus(row, column, 1);
                }
            }
        }
    }
    grid = nextGrid;
}

void Game::checkForInput() {
    if (IsKeyPressed(KEY_R) && !isRunning) populateCells();
    if (IsKeyPressed(KEY_Q) && !isRunning) grid.clearGrid();
    if (IsKeyPressed(KEY_SPACE)) isRunning = !isRunning;
    if (IsKeyPressed(KEY_G)) {
        grid.toggleGrid();
        if (grid.getShowGrid()) background = GRAY;
        else background = BLACK;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isRunning) {
        Vector2 mousePosition = GetMousePosition();
        int row = mousePosition.y / grid.getCellSize();
        int column = mousePosition.x / grid.getCellSize();
        changeCellStatus(row, column);
    }
}
