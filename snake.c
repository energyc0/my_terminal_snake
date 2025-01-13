#include "snake.h"
#include "game_board.h"
#include <stdlib.h>
#include <curses.h>
#include <ctype.h>

extern struct game_board __gboard;
struct snake player;
extern int is_game_over;

int has_added_new_cell = 0;

typedef struct vector snake_point;
snake_point spoint;

void move_cell(struct snake_cell* p);
void change_cells_dir(struct snake_cell* p);
struct snake_cell* add_new_cell(struct snake_cell* tail);

void init_snake(){
    player.head = malloc(sizeof(struct snake_cell));
    player.head->d = player.prev_frame_dir = START_SNAKE_DIRECTION;
    player.head->px = GAME_BOARD_WIDTH / 2;
    player.head->py = GAME_BOARD_HEIGHT/2;
    player.head->next = NULL;
    player.score = 0;
    player.tail = add_new_cell(player.head);
}

int snake_logic(){
    //erase previous snake cell
    if(is_game_over)
        return  is_game_over;
    player.prev_frame_dir = player.head->d;
    mvaddch(player.head->py, player.head->px, SNAKE_CELL_CHARACTER);
    GAME_BOARD_CELL(player.head->px, player.head->py) = GBSNAKE_CELL;
    move_cell(player.head);

    if(!has_added_new_cell){
        mvaddch(player.tail->py, player.tail->px, ' ');
        GAME_BOARD_CELL(player.tail->px, player.tail->py) = GBNONE;
        move_cell(player.tail);
    }else {
        has_added_new_cell = 0;
    }

    int cell;
    //snake is out of game
    if(player.head->px < LEFT_BORDER || player.head->px > RIGHT_BORDER ||
     player.head->py < UPPER_BORDER || player.head->py > BOTTOM_BORDER ||
     (cell = GAME_BOARD_CELL(player.head->px, player.head->py)) == GBSNAKE_CELL)
        return 1;

    if(cell == GBPOINT){
        player.tail = add_new_cell(player.tail);
        spawn_new_spoint();
    }
    change_cells_dir(player.tail);
    mvaddch(player.head->py, player.head->px, SNAKE_HEAD_CHARACTER);
    return 0;
}

void snake_input(int ch){
    #define SNAKE_UP 'w'
    #define SNAKE_DOWN 's'
    #define SNAKE_LEFT 'a'
    #define SNAKE_RIGHT 'd'

    switch(tolower(ch)){
        case SNAKE_UP: if(player.prev_frame_dir != DOWN) player.head->d = UP; break;
        case SNAKE_DOWN: if(player.prev_frame_dir != UP)  player.head->d = DOWN; break;
        case SNAKE_RIGHT: if(player.prev_frame_dir != LEFT)  player.head->d = RIGHT; break;
        case SNAKE_LEFT: if(player.prev_frame_dir != RIGHT) player.head->d = LEFT; break;
    }
}

void move_cell(struct snake_cell* p){
    switch (p->d) {
        case UP: p->py--; ;break;
        case DOWN: p->py++; break;
        case LEFT: p->px--;break;
        case RIGHT: p->px++;break;
    }
}

void change_cells_dir(struct snake_cell* p){
    struct snake_cell* next_p = p->next;
    while (next_p) {
        p->d = next_p->d;
        p = next_p;
        next_p = next_p->next;
    }
}

struct snake_cell* add_new_cell(struct snake_cell* tail){
    struct snake_cell* ptr = malloc(sizeof(struct snake_cell));
    ptr->d = tail->d;
    ptr->next = tail;
    ptr->py = tail->py;
    ptr->px = tail->px;
    has_added_new_cell = 1;
    player.score++;
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

void spawn_new_spoint(){
    int last_cell = -1;
    while (last_cell == -1) {
        int i = rand() % GAME_BOARD_SIZE;
        int field = rand() % POINT_SEARCH_FIELD;
        for(int j = 0; j < field; j++){
            if(__gboard.board[i] == GBNONE)
                last_cell = i;
            i = (i+1)% GAME_BOARD_SIZE;
        }
    }
    spoint.x = last_cell%GAME_BOARD_WIDTH;
    spoint.y = last_cell/GAME_BOARD_WIDTH;
    GAME_BOARD_CELL(spoint.x, spoint.y) = GBPOINT;
}
void draw_spoint(){
    mvaddch(spoint.y, spoint.x, SNAKE_POINT_CHARACTER);
}

int get_snake_score(){
    return player.score;
}