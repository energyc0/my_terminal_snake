#include "snake.h"
#include "utils.h"
#include <stdlib.h>
#include <curses.h>

extern char* game_board;
extern struct window_borders win_border;

void move_cell(struct snake_cell* p);
void change_cells_dir(struct snake_cell* p);
struct snake_cell* add_new_cell(struct snake_cell* tail);

void init_snake(struct snake* p){
    p->head = malloc(sizeof(struct snake_cell));
    p->head->d = START_SNAKE_DIRECTION;
    p->head->x = win_border.r / 2;
    p->head->y = win_border.d/2;
    p->head->next = NULL;

    p->tail = add_new_cell(p->head);
}

int snake_logic(struct snake* p){
    //erase previous snake cell
    mvaddch(p->head->y, p->head->x, SNAKE_CELL_CHARACTER);
    game_board[p->head->x + p->head->y * win_border.r] = 1;

    mvaddch(p->tail->y, p->tail->x, ' ');
    game_board[p->tail->x + p->tail->y * win_border.r] = 0;

    move_cell(p->head);
    move_cell(p->tail);

    //snake is out of game
    if(p->head->x <= win_border.l || p->head->x >= win_border.r ||
     p->head->y <= win_border.u || p->head->y >= win_border.d ||
     game_board[p->head->x + p->head->y * win_border.r])
        return 1;
    mvaddch(p->head->y, p->head->x, SNAKE_HEAD_CHARACTER);
    return 0;
}

void move_cell(struct snake_cell* p){
    switch (p->d) {
        case UP: p->y--; ;break;
        case DOWN: p->y++; break;
        case LEFT: p->x--;break;
        case RIGHT: p->x++;break;
    }
    if(p->next)
        change_cells_dir(p);
}

void change_cells_dir(struct snake_cell* p){
    struct snake_cell* next_p = p->next;
    while (next_p) {
        p->d = next_p->d;
        next_p = next_p->next;
    }
}

struct snake_cell* add_new_cell(struct snake_cell* tail){
    struct snake_cell* ptr = malloc(sizeof(struct snake_cell));
    ptr->d = tail->d;
    ptr->next = tail;
    switch (tail->d) {
        case UP: ptr->y = tail->y - 1; ptr->x = tail->x;break;
        case DOWN: ptr->y = tail->y + 1;ptr->x = tail->x;break;
        case LEFT: ptr->x = tail->x + 1;ptr->y = tail->y;break;
        case RIGHT: ptr->x = tail->x - 1;ptr->y = tail->y;break;
        default: ptr->x = ptr->y = 0;
    }
    return ptr;
}

void destroy_snake(struct snake* p){
    struct snake_cell* ptr = p->tail;
    while (ptr) {
        struct snake_cell* n = ptr->next;
        free(ptr);
        ptr = n;
    }
}