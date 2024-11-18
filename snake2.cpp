#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
using namespace std;
bool gameOver;
const int width = 40;
const int length = 20;
int x, y, fruitX, fruitY, score;
enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setUp(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = length / 2;
    fruitX = rand() % width;
    fruitY = rand() % length;
    score = 0;
}
void draw(){
    system("cls");
    for(int i =0; i<length; i++){
        for (int j = 0; j<width; j++){
            if( i == 0 || i == length-1 || j == 0 || j == width-1){
                cout<<"*";
            }
            else if(i==y && j==x){
                cout<<"O";
            }
            else if(i==fruitY && j==fruitX){
                cout<<"F";
            }
            else{
                cout<<" ";
            }
        }
        cout<<endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));

}       


void input(){
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
void logic(){
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
    }

}

int main(){
    setUp();
    while(!gameOver){
        draw();
        input();
        logic();
    }
   

   

    return 0;
}