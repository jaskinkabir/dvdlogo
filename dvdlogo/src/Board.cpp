#include <stdio.h>
#include "Board.h"
#include <vector>
#include <string>
#include <iostream>

using namespace B;


void Board::setBlank() {
    std::vector<std::vector<int>> res(
        rows,
        std::vector<int>(cols)
    );
    board = res;

}

int Board::getVal(int y, int x) {
    return board[y][x];
}

void Board::setVal(int y, int x, int val) {
    board[y][x] = val;
}

void Board::draw() {
    for (int y = 0; y < rows * cellY + 2; y++) {
        for (int x = 0; x < cols + 2; x++) {

            if (x == 0 || x == cols + 1) {
                std::cout << '|';
                continue;
            }

            if (y == 0 || y == rows * cellY + 1) {
                for (int i = 0; i < cellX; i++) std::cout << "-";
                continue;
            }

            int xGrid = x - 1;
            int yGrid = (y - 1) / cellY;
            int yCell = (y - 1) % cellY;

            int texture = board[yGrid][xGrid];

            std::cout << Textures[texture][yCell];


        }
        std::cout << '\n';
    }

}


Board::Board(int rs, int cs, int cX, int cY, std::vector<std::vector<std::string>> tex, bool blank) {
    rows = rs;
    cols = cs;
    cellX = cX;
    cellY = cY;
    Textures = tex;


    if (blank) {
        setBlank();
    }
}