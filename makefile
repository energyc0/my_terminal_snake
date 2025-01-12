snake.out: main.c snake.c snake.h snake_game.c snake_game.h utils.h game_board.c game_board.h
	cc main.c snake.c snake_game.c game_board.c -o snake.out -g -lcurses