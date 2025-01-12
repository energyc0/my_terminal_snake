#include "game_board.h"
#include <stdlib.h>
#include <curses.h>

struct game_board gboard;

void init_game_board(){
    gboard.left_border = 0;
    gboard.right_border = COLS-1;
    gboard.upper_border = 0;
    gboard.bottom_border = LINES-1;
    //allocate game board
    gboard.board = calloc(gboard.bottom_border, sizeof(char[gboard.right_border]));
}

void destroy_game_board(){
    free(gboard.board); 
}