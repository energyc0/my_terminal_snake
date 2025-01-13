#ifndef GAME_BOARD_H
#define GAME_BOARD_H

enum game_board_cell_t{
    GBNONE = 0,
    GBSNAKE_CELL = 1,
    GBPOINT = 2
};

struct game_board{
    int left_border;
    int right_border;
    int upper_border;
    int bottom_border;
    char* board;
    unsigned int board_size;
};

extern struct game_board __gboard;

#define GAME_BOARD_CELL(x,y) (__gboard.board[x + y*__gboard.right_border])
#define GAME_BOARD_SIZE (__gboard.board_size)
#define LEFT_BORDER (__gboard.left_border)
#define RIGHT_BORDER (__gboard.right_border)
#define UPPER_BORDER (__gboard.upper_border)
#define BOTTOM_BORDER (__gboard.bottom_border)

#define GAME_BOARD_WIDTH RIGHT_BORDER
#define GAME_BOARD_HEIGHT BOTTOM_BORDER
//call after initscr()
void init_game_board();
void destroy_game_board();

#endif