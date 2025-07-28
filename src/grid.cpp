#include "grid.h"

void Grid::drawGrid() {
    for (int row = 0; row < Rows; row++) {
        for (int column = 0; column < Columns; column++) {
            cellColor = Cells[row][column] ? Color(LIGHTGRAY) : Color(BLACK);
            DrawRectangle(column * CellSize, row * CellSize, CellSize - 1, CellSize - 1, cellColor); 
        }
    }
}

void Grid::clearGrid() {
    for (int row = 0l; row < Rows; row++) {
        for (int column = 0; column < Columns; column++) {
            Cells[row][column] = 0;
        }
    }
}

void Grid::toggleGrid() {
    showGrid = !showGrid;
}
