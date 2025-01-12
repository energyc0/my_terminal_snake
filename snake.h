#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_CELL_CHARACTER '*'
#define SNAKE_HEAD_CHARACTER '@'
#define SNAKE_POINT_CHARACTER 'O'

enum dir_t{
    LEFT = 0,
    UP = 1,
    DOWN = 2,
    RIGHT = 3
};

#define START_SNAKE_DIRECTION LEFT

struct vector{
    int x;
    int y;
};

struct snake_cell{
    struct vector __pos;
    #define px __pos.x
    #define py __pos.y
    enum dir_t d;
    struct snake_cell* next;
};

struct snake{
    struct snake_cell* head;
    struct snake_cell* tail;
};

void destroy_snake();
void init_snake();
//return game state
int snake_logic();
void snake_input(int ch);

//checks gameboard and create randomly a point there
void spawn_new_spoint();
void draw_spoint();
#endif