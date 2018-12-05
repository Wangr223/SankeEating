// 贪吃蛇游戏的设计 
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>  

#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define food $

void snake_move();   
void output();
int gameover();
void creat_food();
/*
 要开始一个贪吃蛇游戏，我先从玩法的角度入手。我首先需要定义一段可以活动的游戏区域

*/ 
char map[12][12] = {
    "***********",
    "*XXXXH    *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "***********",
};   //用该数组来定义一个活动范围

//接下来我们需要一条能活动，能进行吞食并增长的蛇 
int snake_length = 5; //这是蛇的基础长度
int snake_location_x[10] = {5, 4, 3, 2, 1}; //这是蛇的初始位置x
int snake_location_y[10] = {1, 1, 1, 1, 1}; //这是蛇的初始位置Y
int food_x;
int food_y; //这两行是食物的刷新位置


int main() {
    creat_food(); //随机创造食物
    char choice;
    output();
    while (1) {
        scanf(" %c", &choice);
        snake_move();
        if (choice == 'w') {
            snake_location_y[0] -= 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//上移，头部往上移动一位，其他身体部位向原本下一段的位置填充 
        }
        if (choice == 's') {
            snake_location_y[0] += 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//下移，头部往下移动一位，其他身体部位向原本下一段的位置填充 
        }
        if (choice == 'a') {
            snake_location_x[0] -= 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//左移，头部往左移动一位，其他身体部位向原本下一段的位置填充 
        }
        if (choice == 'd') {
            snake_location_x[0] += 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//右移，头部往右移动一位，其他身体部位向原本下一段的位置填充
        }          //以上是基本方向操作
        if (snake_location_x[0] == food_x && snake_location_y[0] == food_y) {
            creat_food();
            snake_length++;
            snake_location_x[snake_length - 1] = snake_location_x[snake_length - 2];
            snake_location_y[snake_length - 1] = snake_location_y[snake_length - 2];
            map[snake_location_y[snake_length - 1]][snake_location_x[snake_length - 1]] = 'X';  //如果吃到食物（蛇头与食物坐标重叠），则加长蛇身一个单位长度 
        }
        if (!gameover()) {
            printf("GAMEOVER!\n");//如果碰到墙或者自己的身体就算失败，并在主屏幕上打出“Game Over”字样 
            return 0;
        } else {
            output();
        }
    }  //蛇的头部碰撞到墙时，游戏结束并在对话框打出 "Game Over" 提示 
    return 0;
}    //头部的移动应该牵引着后面一系列的“身体”进行移动，并且前一个的位置会被后一个的位置所替代

void snake_move() {
    int i;
    map[snake_location_y[snake_length - 1]][snake_location_x[snake_length - 1]] = ' '; //蛇头与 空格 字符相接触，是正常的“移动 ”，只需要进行位置的移动就好 
    for (i = snake_length - 1; i > 0; i--) {
        snake_location_x[i] = snake_location_x[i - 1];
        snake_location_y[i] = snake_location_y[i - 1];
        map[snake_location_y[i]][snake_location_x[i]] = 'X'; //上面三行程序完成了 “尾巴段的身体向靠近头部的部分补进一个单位” 
    } //基础移动的代码表示
}

int gameover() {
    if (snake_location_x[0] == 10 || snake_location_x[0] == 0) { //碰到左墙以及右墙 
        return 0;
    }
    if (snake_location_y[0] == 10 || snake_location_y[0] == 0) {//碰到上顶以及下底 
        return 0;
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake_location_x[0] == snake_location_x[i] && snake_location_y[0] == snake_location_y[i]) {
            return 0; //碰到自己 “蛇 ”的身体 ，即描述蛇的身体两个字符数组相重叠 
        }
    }
    return 1;  //如果没碰撞到墙壁，游戏继续 ；  若碰到墙壁或者自己身体， 游戏结束 
}
void output() {
    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j <= 11; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
void creat_food() {
    srand((unsigned)(time(NULL)));
    food_x = rand() % 9 + 1;
    food_y = rand() % 9 + 1;
    while (map[food_y][food_x] != ' ') {
        food_x = rand() % 9 + 1;
        food_y = rand() % 9 + 1; //食物刷新的横纵坐标（其实是二维字符数组的 “坐标 ”） 
    }
    map[food_y][food_x] = '$';   //食物的创造应该是随机的 这里也用近似随机的方法来表示
}

