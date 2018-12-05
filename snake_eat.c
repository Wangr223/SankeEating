// ̰������Ϸ����� 
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
 Ҫ��ʼһ��̰������Ϸ�����ȴ��淨�ĽǶ����֡���������Ҫ����һ�ο��Ի����Ϸ����

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
};   //�ø�����������һ�����Χ

//������������Ҫһ���ܻ���ܽ�����ʳ���������� 
int snake_length = 5; //�����ߵĻ�������
int snake_location_x[10] = {5, 4, 3, 2, 1}; //�����ߵĳ�ʼλ��x
int snake_location_y[10] = {1, 1, 1, 1, 1}; //�����ߵĳ�ʼλ��Y
int food_x;
int food_y; //��������ʳ���ˢ��λ��


int main() {
    creat_food(); //�������ʳ��
    char choice;
    output();
    while (1) {
        scanf(" %c", &choice);
        snake_move();
        if (choice == 'w') {
            snake_location_y[0] -= 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//���ƣ�ͷ�������ƶ�һλ���������岿λ��ԭ����һ�ε�λ����� 
        }
        if (choice == 's') {
            snake_location_y[0] += 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//���ƣ�ͷ�������ƶ�һλ���������岿λ��ԭ����һ�ε�λ����� 
        }
        if (choice == 'a') {
            snake_location_x[0] -= 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//���ƣ�ͷ�������ƶ�һλ���������岿λ��ԭ����һ�ε�λ����� 
        }
        if (choice == 'd') {
            snake_location_x[0] += 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';//���ƣ�ͷ�������ƶ�һλ���������岿λ��ԭ����һ�ε�λ�����
        }          //�����ǻ����������
        if (snake_location_x[0] == food_x && snake_location_y[0] == food_y) {
            creat_food();
            snake_length++;
            snake_location_x[snake_length - 1] = snake_location_x[snake_length - 2];
            snake_location_y[snake_length - 1] = snake_location_y[snake_length - 2];
            map[snake_location_y[snake_length - 1]][snake_location_x[snake_length - 1]] = 'X';  //����Ե�ʳ���ͷ��ʳ�������ص�������ӳ�����һ����λ���� 
        }
        if (!gameover()) {
            printf("GAMEOVER!\n");//�������ǽ�����Լ����������ʧ�ܣ���������Ļ�ϴ����Game Over������ 
            return 0;
        } else {
            output();
        }
    }  //�ߵ�ͷ����ײ��ǽʱ����Ϸ�������ڶԻ����� "Game Over" ��ʾ 
    return 0;
}    //ͷ�����ƶ�Ӧ��ǣ���ź���һϵ�еġ����塱�����ƶ�������ǰһ����λ�ûᱻ��һ����λ�������

void snake_move() {
    int i;
    map[snake_location_y[snake_length - 1]][snake_location_x[snake_length - 1]] = ' '; //��ͷ�� �ո� �ַ���Ӵ����������ġ��ƶ� ����ֻ��Ҫ����λ�õ��ƶ��ͺ� 
    for (i = snake_length - 1; i > 0; i--) {
        snake_location_x[i] = snake_location_x[i - 1];
        snake_location_y[i] = snake_location_y[i - 1];
        map[snake_location_y[i]][snake_location_x[i]] = 'X'; //�������г�������� ��β�Ͷε������򿿽�ͷ���Ĳ��ֲ���һ����λ�� 
    } //�����ƶ��Ĵ����ʾ
}

int gameover() {
    if (snake_location_x[0] == 10 || snake_location_x[0] == 0) { //������ǽ�Լ���ǽ 
        return 0;
    }
    if (snake_location_y[0] == 10 || snake_location_y[0] == 0) {//�����϶��Լ��µ� 
        return 0;
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake_location_x[0] == snake_location_x[i] && snake_location_y[0] == snake_location_y[i]) {
            return 0; //�����Լ� ���� �������� ���������ߵ����������ַ��������ص� 
        }
    }
    return 1;  //���û��ײ��ǽ�ڣ���Ϸ���� ��  ������ǽ�ڻ����Լ����壬 ��Ϸ���� 
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
        food_y = rand() % 9 + 1; //ʳ��ˢ�µĺ������꣨��ʵ�Ƕ�ά�ַ������ ������ ���� 
    }
    map[food_y][food_x] = '$';   //ʳ��Ĵ���Ӧ��������� ����Ҳ�ý�������ķ�������ʾ
}

