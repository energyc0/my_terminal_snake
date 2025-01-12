snake.out: main.c snake.c snake.h snake_game.c snake_game.h utils.h
	cc main.c snake.c snake_game.c -o snake.out -g -lcurses