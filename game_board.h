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

extern struct game_board gboard;

#define GAME_BOARD_CELL(x,y) (gboard.board[x + y*gboard.right_border])
#define LEFT_BORDER (gboard.left_border)
#define RIGHT_BORDER (gboard.right_border)
#define UPPER_BORDER (gboard.upper_border)
#define BOTTOM_BORDER (gboard.bottom_border)
//call after initscr()
void init_game_board();
void destroy_game_board();

#endif