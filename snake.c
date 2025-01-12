#include "snake.h"
#include "game_board.h"
#include <stdlib.h>
#include <curses.h>

extern struct game_board gboard;

void move_cell(struct snake_cell* p);
void change_cells_dir(struct snake_cell* p);
struct snake_cell* add_new_cell(struct snake_cell* tail);

void init_snake(struct snake* p){
    p->head = malloc(sizeof(struct snake_cell));
    p->head->d = START_SNAKE_DIRECTION;
    p->head->px = gboard.right_border / 2;
    p->head->py = gboard.bottom_border/2;
    p->head->next = NULL;

    p->tail = add_new_cell(p->head);
}

int snake_logic(struct snake* p){
    //erase previous snake cell
    mvaddch(p->head->py, p->head->px, SNAKE_CELL_CHARACTER);
    GAME_BOARD_CELL(p->head->px, p->head->py) = GBSNAKE_CELL;

    mvaddch(p->tail->py, p->tail->px, ' ');
    GAME_BOARD_CELL(p->tail->px, p->tail->py) = GBNONE;

    move_cell(p->head);
    move_cell(p->tail);

    //snake is out of game
    if(p->head->px <= LEFT_BORDER || p->head->px >= RIGHT_BORDER ||
     p->head->py <= UPPER_BORDER || p->head->py >= BOTTOM_BORDER ||
     GAME_BOARD_CELL(p->head->px, p->head->py) == GBSNAKE_CELL)
        return 1;
    mvaddch(p->head->py, p->head->px, SNAKE_HEAD_CHARACTER);
    return 0;
}

void move_cell(struct snake_cell* p){
    switch (p->d) {
        case UP: p->py--; ;break;
        case DOWN: p->py++; break;
        case LEFT: p->px--;break;
        case RIGHT: p->px++;break;
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
        case UP: ptr->py = tail->py - 1; ptr->px = tail->px;break;
        case DOWN: ptr->py = tail->py + 1;ptr->px = tail->px;break;
        case LEFT: ptr->px = tail->px + 1;ptr->py = tail->py;break;
        case RIGHT: ptr->px = tail->px - 1;ptr->py = tail->py;break;
        default: ptr->px = ptr->py = 0;
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

#define POINT_SEARCH_FIELD 100

void spawn_new_point(snake_point* p){
    
}