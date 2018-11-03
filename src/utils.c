#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/const.h"
#include "../header/utils.h"

// altera o estado de jogo
void set_state(int state_id, State *state){
    
    // desativa todos os estados
    state->gameover = state->menu = state->rules = state->options = state->ingame = state->exit = 0;
    
    // ativa o estado requerido
    switch(state_id){
        case STATE_GAMEOVER: state->gameover = 1; break;
        case STATE_MENU:     state->menu = 1;     break;
        case STATE_RULES:    state->rules = 1;    break;
        case STATE_OPTIONS:  state->options = 1;  break;
        case STATE_INGAME:   state->ingame = 1;   break;
        case STATE_EXIT:     state->exit = 1;     break;
        default:
            state->exit = 1;
            break;
    }

}


// insere marcacao no tabuleiro
void insert_mark(int row, int col, int player, Config *config){
    switch(player){
        case PLAYER_1: config->board[row][col] = PLAYER_1_SYMBOL; break;
        case PLAYER_2: config->board[row][col] = PLAYER_2_SYMBOL; break;
        case PLAYER_3: config->board[row][col] = PLAYER_3_SYMBOL; break;
    }
}


// zera vetor
void reset_array(int array[9][9]){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            array[i][j] = 0;
}


// gera numero inteiro aleatorio no intervalo (inclui extremos)
int random_int(int min, int max){
    int range = max - min;
    srand(time(NULL));
    int r = (rand() % (range + 1)) + min;
    return r;
}

