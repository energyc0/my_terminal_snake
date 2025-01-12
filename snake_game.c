#include "snake_game.h"
#include "snake.h"
#include "game_board.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

#define SNAKE_UP 'w'
#define SNAKE_DOWN 's'
#define SNAKE_LEFT 'a'
#define SNAKE_RIGHT 'd'

int is_game_over = 0;

struct snake player;
snake_point point;

int fcntl_flags;

void on_key_press(int code);
void on_alarm(int code);
void on_interrupt(int code);

void set_delay(struct itimerval* t, int ms);

void game_init(){
    //initialize input
    fcntl(0, F_SETOWN, getpid());
    fcntl_flags = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, (fcntl_flags | O_ASYNC));
    //initialize curses
    initscr();
    noecho();
    nodelay(stdscr, true);
    curs_set(0);
    //inititalize game objects
    init_game_board();
    init_snake(&player);
    
    struct sigaction sgnl;
    //SIGIO
    sgnl.sa_handler = on_key_press;
    sigemptyset(&sgnl.sa_mask);
    sigaddset(&sgnl.sa_mask, SIGALRM);
    if(sigaction(SIGIO, &sgnl, NULL)){
        perror("sigaction SIGIO");
        is_game_over = 1;
        return;
    }
    //SIGALRM
    sgnl.sa_handler = on_alarm;
    sigdelset(&sgnl.sa_mask, SIGALRM);
    sigaddset(&sgnl.sa_mask, SIGIO);
    if(sigaction(SIGALRM, &sgnl, NULL)){
        perror("sigaction SIGALRM");
        is_game_over = 1;
        return;
    }
    //SIGINT
    sgnl.sa_handler = on_interrupt;
    sigdelset(&sgnl.sa_mask, SIGIO);
    if(sigaction(SIGINT, &sgnl, NULL)){
        perror("sigaction SIGINT");
        is_game_over = 1;
        return;
    }

    //set draw timer
    struct itimerval draw_timer;
    set_delay(&draw_timer, MS_PER_FRAME);
    if(setitimer(ITIMER_REAL, &draw_timer, NULL)){
        perror("setitimer");
        is_game_over = 1;
        return;
    }
}

void game_loop(){
    while (!is_game_over) {
        pause();
    }   
}

void game_clear(){
    endwin();
    printf("x: %d, y: %d\n", player.head->px, player.head->py);
    destroy_game_board();
    destroy_snake(&player);
    fcntl(0, F_SETFL, fcntl_flags);
}

void on_key_press(int code){
    int ch = getchar();
    switch(ch){
        case SNAKE_UP: if(player.head->d != DOWN) player.head->d = UP; break;
        case SNAKE_DOWN: if(player.head->d != UP)  player.head->d = DOWN; break;
        case SNAKE_RIGHT: if(player.head->d != LEFT)  player.head->d = RIGHT; break;
        case SNAKE_LEFT: if(player.head->d != RIGHT) player.head->d = LEFT; break;
    }
}

void on_alarm(int code){
    if((is_game_over = snake_logic(&player)))
        return;

    refresh();
}

void on_interrupt(int code){
    is_game_over = 1;
}

void set_delay(struct itimerval* t, int ms){
    t->it_interval.tv_sec = t->it_value.tv_sec = ms / 1000;
    t->it_interval.tv_usec = t->it_value.tv_usec = ms * 1000;
}
