#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

bool gameOver;
const int width = 40;
const int length = 20;
int x, y, fruitX, fruitY, score;
int tailX[100],tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setUp() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = length / 2;
    fruitX = rand() % width;
    fruitY = rand() % length;
    score = 0;
}

void draw() {
    vector<string> buffer(length, string(width, ' '));

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == length - 1 || j == 0 || j == width - 1) {
                buffer[i][j] = '*';
            } else if (i == y && j == x) {
                buffer[i][j] = 'O';
            } else if (i == fruitY && j == fruitX) {
                buffer[i][j] = 'F';
            }
        }
    }

    system("cls");
    for (const auto& line : buffer) {
        cout << line << endl;
    }
    cout << "Score: " << score << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    for(int i =1; i<nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x >= width || x < 0 || y >= length || y < 0) {
        gameOver = true;
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % length;
        nTail ++;
    }
}

int main() {
    setUp();
    while (!gameOver) {
        draw();
        input();
        logic();
    }
    return 0;
}