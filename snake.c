#include "snake.h"
#include "game_board.h"
#include <stdlib.h>
#include <curses.h>

extern struct game_board gboard;
struct snake player;

void move_cell(struct snake_cell* p);
void change_cells_dir(struct snake_cell* p);
struct snake_cell* add_new_cell(struct snake_cell* tail);

void init_snake(){
    player.head = malloc(sizeof(struct snake_cell));
    player.head->d = START_SNAKE_DIRECTION;
    player.head->px = gboard.right_border / 2;
    player.head->py = gboard.bottom_border/2;
    player.head->next = NULL;

    player.tail = add_new_cell(player.head);
}

int snake_logic(){
    //erase previous snake cell
    mvaddch(player.head->py, player.head->px, SNAKE_CELL_CHARACTER);
    GAME_BOARD_CELL(player.head->px, player.head->py) = GBSNAKE_CELL;

    mvaddch(player.tail->py, player.tail->px, ' ');
    GAME_BOARD_CELL(player.tail->px, player.tail->py) = GBNONE;

    move_cell(player.head);
    move_cell(player.tail);

    //snake is out of game
    if(player.head->px <= LEFT_BORDER || player.head->px >= RIGHT_BORDER ||
     player.head->py <= UPPER_BORDER || player.head->py >= BOTTOM_BORDER ||
     GAME_BOARD_CELL(player.head->px, player.head->py) == GBSNAKE_CELL)
        return 1;
    mvaddch(player.head->py, player.head->px, SNAKE_HEAD_CHARACTER);
    return 0;
}

void snake_input(int ch){
    #define SNAKE_UP 'w'
    #define SNAKE_DOWN 's'
    #define SNAKE_LEFT 'a'
    #define SNAKE_RIGHT 'd'
    
    switch(ch){
        case SNAKE_UP: if(player.head->d != DOWN) player.head->d = UP; break;
        case SNAKE_DOWN: if(player.head->d != UP)  player.head->d = DOWN; break;
        case SNAKE_RIGHT: if(player.head->d != LEFT)  player.head->d = RIGHT; break;
        case SNAKE_LEFT: if(player.head->d != RIGHT) player.head->d = LEFT; break;
    }
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

void destroy_snake(){
    struct snake_cell* ptr = player.tail;
    while (ptr) {
        struct snake_cell* n = ptr->next;
        free(ptr);
        ptr = n;
    }
}

#define POINT_SEARCH_FIELD 100

void spawn_new_point(){
    
}
