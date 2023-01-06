#pragma once
#include <stdio.h>
#include "Board.h"
#include <vector>
#include <string>
#include <iostream>

namespace B {
    class Board {
    private:
        int rows;
        int cols;
        int cellX;
        int cellY;

        std::vector<std::vector<std::string>> Textures;


        std::vector<std::vector<int>> board;

        void setBlank();



    public:
        int getVal(int y, int x);

        void setVal(int y, int x, int val);

        void draw();


        Board(int rs, int cs, int cX, int cY, std::vector<std::vector<std::string>> tex, bool blank = true);
    };
}