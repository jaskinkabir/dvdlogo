// dvdlogo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    TODO:
    - Smoother animations with physics frames vs graphics frames and microseconds clock
    - Send to corner button
*/


#include <iostream>
#include "Board.h"
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <chrono>
#include <conio.h>
using namespace B;

#define PI 3.14159265

int timestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
        ).count();
}

void clear() {
    system("cls");
}


std::vector< std::vector<std::string>> Textures = {
    {
        "   ",
        "   ",
        "   "
    },
    {
        "___",
        "DVD",
        "<->"
    },
    {
        "<=>",
        "VDV",
        "---"
    }
};


int genSpice() {
    if (! int(rand() % 2)) return 0;

    return int(rand() % 2) ? 1 : -1;

}

class Logo {
private:
    int rows = 0;
    int cols = 0;
    int xPos = 0;
    int yPos = 0;
    int xVel = 0;
    int yVel = 0;
    int bumpCount = 0;
    int randLevel = 1;


public:

    Logo(int xLim, int yLim, int totalSpeed) {
        rows = xLim;
        cols = yLim;


        srand(timestamp());

        xPos = rand() % (cols - 1);
        yPos = rand() % (rows - 1);
        double ang = (rand() % 360) * (PI / 180);

        xVel = totalSpeed * cos(ang);
        xVel = int(rand() % 2) ? ceil(xVel) : floor(xVel);
        yVel = totalSpeed * sin(ang);
        yVel = int(rand() % 2) ? ceil(yVel) : floor(yVel);

    }

    int getRandLevel() {
        return randLevel;
    }

    void setPos(int x, int y) {
        xPos = x;
        yPos = y;
    }

    void spiceBounce() {
        if (!randLevel) return;

        int chance = 6 - randLevel;

        if (int(rand() % chance)) return;
        


        int vel = 0;    
        int spice = genSpice();
        
        if (int(rand() % 2)) {
            vel = 1;
        }

        switch (vel) {
        case 0:
            xVel += spice;
            break;
        case 1:
            yVel += spice;
        }
         
        std::cout << std::endl << "Spice!";
    }

    void move() {
        
        int curX = xPos;
        int curY = yPos;

        int tempX = xPos + xVel;
        int tempY = yPos + yVel;

        if (tempX < 0) {
            //Logo has hit left wall
            xPos = -tempX;
            xVel = -xVel;
            spiceBounce();
        }
        else if (tempX >= cols) {
            xPos = 2 * (cols - 1) - tempX;
            xVel = -xVel;
            spiceBounce();
        }
        else {
            xPos = tempX;
        }

        if (tempY < 0) {
            yPos = -tempY;
            yVel = -yVel;
            spiceBounce();
        }
        else if (tempY >= rows) {
            yPos = 2 * (rows - 1) - tempY;
            yVel = -yVel;
            spiceBounce();
        }
        else {
            yPos = tempY;
        }

    }

    void changeX(int change) {
        xVel += change;
    }

    void changeY(int change) {
        yVel += change;
    }

    void stop() {
        xVel = 0;
        yVel = 0;
    }

    void cycleRand() {
        if (randLevel == 4) {
            randLevel = -1;
        }
        randLevel++;

        int fuckyou = 0;
    }

    int getX() {
        return xPos;
    }

    int getY() {
        return yPos;
    }

};


int main()
{
    srand(timestamp());

    int rows = 12;
    int cols = 24;
    int cellX = 3;
    int cellY = 3;
    int logoSpeed = 3;
    

    Board board = Board(rows, cols, cellX, cellY, Textures);
    
    Logo logo = Logo(rows, cols, logoSpeed);

    board.setVal(logo.getY(), logo.getX(), 1);
    clear();
    board.draw();

    int lastTime = timestamp();
    int curTime;
    int fps = 10;
    int fpsStep = 5;
    int millisPerFrame = 1000 / fps;

    

    while (1) {
        


        if (_kbhit()) {
            char a = _getch();

            switch (a) {
            case ('e'):
                if (fps + fpsStep >= 1000) break;
                fps += fpsStep;
                millisPerFrame = 1000 / fps;
                break;
            case ('q'):
                if (fps == fpsStep) break;
                fps -= fpsStep;
                millisPerFrame = 1000 / fps;
                break;

            case ('w'):
                logo.changeY(-1);
                break;
            case ('a'):
                logo.changeX(-1);
                break;
            case ('s'):
                logo.changeY(1);
                break;
            case ('d'):
                logo.changeX(1);
                break;
            case ('r'):
                logo.cycleRand();
                break;
            case ('f'):
                logo.stop();
                break;
            }

            
        }

        curTime = timestamp();
        if (curTime - lastTime >= millisPerFrame) {
            board.setVal(logo.getY(), logo.getX(), 0);

            logo.move();
            board.setVal(logo.getY(), logo.getX(), 1);

            clear();
            board.draw();
            std::cout << "Randomness level: " << logo.getRandLevel() << std::endl << "FPS: " << fps;

            lastTime = timestamp();
            srand(lastTime);
        }
    }
   

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
