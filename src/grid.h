#pragma once
#include "raylib.h"
#include <vector>

class Grid {
public:
    Grid() = default;
    Grid(int width, int height, int cellSize)
    : Rows {height / cellSize},
    Columns {width / cellSize},
    CellSize {cellSize},
    Cells(Rows, std::vector<int>(Columns, 0)),
    showGrid {false} {};

    int getRows() {return Rows;}
    int getColumns() {return Columns;}
    int getCellStaus(int row, int column) {return Cells[row][column];}
    int getCellSize() {return CellSize;}
    std::vector<std::vector<int>>& getCells() {return Cells;}
    bool getShowGrid() {return showGrid;}

    void setCellStaus(int row, int column, int status) {Cells[row][column] = status;}

    void drawGrid();
    void clearGrid();
    void toggleGrid();

private:
    int Rows;
    int Columns;
    int CellSize;
    std::vector<std::vector<int>> Cells;
    Color cellColor;
    bool showGrid;
};
