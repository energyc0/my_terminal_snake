#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_CELL_CHARACTER '#'
#define SNAKE_HEAD_CHARACTER '*'

enum dir_t{
    LEFT = 0,
    UP = 1,
    DOWN = 2,
    RIGHT = 3
};

#define START_SNAKE_DIRECTION LEFT

struct snake_cell{
    int x;
    int y; //y coordinate is doubled for x/y speed equality
    enum dir_t d;
    struct snake_cell* next;
};

struct snake{
    struct snake_cell* head;
    struct snake_cell* tail;
};

void destroy_snake(struct snake* p);
void init_snake(struct snake* p);
//return game state
int snake_logic(struct snake* p);
#endif