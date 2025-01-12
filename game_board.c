#include "game_board.h"
#include <stdlib.h>
#include <curses.h>

struct game_board __gboard;

void init_game_board(){
    __gboard.left_border = 0;
    __gboard.right_border = COLS-1;
    __gboard.upper_border = 0;
    __gboard.bottom_border = LINES-1;

    __gboard.board_size = GAME_BOARD_WIDTH * GAME_BOARD_HEIGHT;
    //allocate game board
    __gboard.board = calloc(LINES, sizeof(char[COLS]));
}

void destroy_game_board(){
    free(__gboard.board); 
}