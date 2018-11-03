#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/const.h"
#include "../header/utils.h"
#include "../header/valid.h"
#include "../header/machine.h"


void machine_play(int *row, int *col, Config *config){
    int p;

    // a maquina ira jogar de acordo com a dificuldade escolhida
    switch(config->difficulty){

        // neste modo a maquina seleciona a linha e a coluna aleatoriamente
        case DIFFICULTY_EASY:
            play_random(row, col, config);
            break;

        // neste modo existe uma chance de 75% da maquina jogar no dificil e 25% da maquina jogar no facil
        case DIFFICULTY_NORMAL:
            p = random_int(1, 100);
            if (p > 75) play_random(row, col, config);
            else play_hard(row, col, config);
            break;
        
        // neste modo a maquina joga sem permitir que o jogador preencha linhas/colunas/diagonais diretamente
        case DIFFICULTY_HARD:
            play_hard(row, col, config);
            break;
    }
}


void play_random(int *row, int *col, Config *config){
    int not_valid_mark = 1, N = config->N;
    srand(time(NULL));

    while(not_valid_mark){
        *row = rand() % N;
        *col = rand() % N;
        // encerra a funcao se a celula for valida
        if(is_valid_mark(*row, *col, config) == MARK_VALID)
            return;
    }

}


void play_hard(int *row, int *col, Config *config){
    int z, i, j, empty_row, empty_col, count, N = config->N;
    char symbol;

    // procura por N-1 preenchimentos em cada linha, se tiver, escolhe a celula vazia
    for(i = 0; i < N; i++){
        empty_row = -1;
        // reseta contador de pontuacao
        count = 0;
        symbol = ' ';
        // verifica se tem simbolo na linha
        for(j = 0; j < N; j++)
            if (config->board[i][j] != ' ' && config->board[i][j] != 'O') {
                symbol = config->board[i][j];
                break;
            }
        // se nao tem simbolo pula pra proxima linha
        if(symbol == ' ') continue;

        // conta pontuacao na linha i
        for(j = 0; j < N; j++){
            if (config->board[i][j] == symbol) count++;
            else if (config->board[i][j] == ' ') {
                empty_row = i; empty_col = j; // guarda celula vazia 
            }
        }
        // se tem N-1 preenchimentos, escolhe a celula vazia empty_row, empty_col
        if (count == N-1 && empty_row != -1){
            *row = empty_row;
            *col = empty_col;
            return;
        }
    }

    // procura por N-1 preenchimentos em cada coluna, se tiver, escolhe a celula vazia (similar a acima)
    for(i = 0; i < N; i++){
        empty_row = -1;
        count = 0;
        symbol = ' ';
        for(j = 0; j < N; j++)
            if (config->board[j][i] != ' ' && config->board[j][i] != 'O') {
                symbol = config->board[j][i];
                break;
            }
        if(symbol == ' ') continue;

        for(j = 0; j < N; j++){
            if (config->board[j][i] == symbol) count++;
            else if (config->board[j][i] == ' '){
                empty_row = j; empty_col = i;
            }
        }

        if (count == N-1 && empty_row != -1){
            *row = empty_row; *col = empty_col;
            return;
        }
    }

    // procura por N-1 preenchimentos em cada sub-diagonal 1, se tiver, escolhe a celula vazia (similar a acima)
    for(i = 0; i < N-1; i++){
        empty_row = -1;
        z = count = 0;
        symbol = ' ';
        for(j = 0; j < N; j++){
            if (config->board[j][j+i+z] != ' ' && config->board[j][j+i+z] != 'O') {
                symbol = config->board[j][j+i+z];
                break;
            }
            if (j+i >= N-1) z -= 2; // rebate na parede
        }
        if (symbol == ' ') continue;
        z = 0;
        for(j = 0; j < N; j++){
            if (config->board[j][j+i+z] == symbol) count++;
            else if (config->board[j][j+i+z] == ' '){
                empty_row = j; empty_col = j+i+z;
            }
            if (j+i >= N-1) z -= 2;
        }
        if (count == N-1 && empty_row != -1){
            *row = empty_row; *col = empty_col;
            return;
        }
    }

    // procura por N-1 preenchimentos em cada sub-diagonal 2, se tiver, escolhe a celula vazia (similar a acima)
    for(i = 0; i < N-1; i++){
        empty_row = -1;
        z = count = 0;
        symbol = ' ';
        for(j = 0; j < N; j++){
            if (config->board[j+i+z][N-1-j] != ' ' && config->board[j+i+z][N-1-j] != 'O') {
                symbol = config->board[j+i+z][N-1-j];
                break;
            }
            if (j+i >= N-1) z -= 2; // rebate na parede
        }
        if (symbol == ' ') continue;
        z = 0;
        for(j = 0; j < N; j++){
            if (config->board[j+i+z][N-1-j] == symbol) count++;
            else if (config->board[j+i+z][N-1-j] == ' '){
                empty_row = j+i+z; empty_col = N-1-j;
            }
            if (j+i >= N-1) z -= 2;
        }
        if (count == N-1 && empty_row != -1){
            *row = empty_row; *col = empty_col;
            return;
        }
    }

    // procura por N-1 preenchimentos em cada sub-diagonal 3, se tiver, escolhe a celula vazia (similar a acima)
    for(i = 0; i < N-1; i++){
        empty_row = -1;
        z = count = 0;
        symbol = ' ';
        for(j = 0; j < N; j++){
            if (config->board[N-1-j][N-1-j-i-z] != ' ' && config->board[N-1-j][N-1-j-i-z] != 'O') {
                symbol = config->board[N-1-j][N-1-j-i-z];
                break;
            }
            if (j+i >= N-1) z -= 2; // rebate na parede
        }
        if (symbol == ' ') continue;
        z = 0;
        for(j = 0; j < N; j++){
            if (config->board[N-1-j][N-1-j-i-z] == symbol) count++;
            else if (config->board[N-1-j][N-1-j-i-z] == ' '){
                empty_row = N-1-j; empty_col = N-1-j-i-z;
            }
            if (j+i >= N-1) z -= 2;
        }
        if (count == N-1 && empty_row != -1){
            *row = empty_row; *col = empty_col;
            return;
        }
    }

    // procura por N-1 preenchimentos em cada sub-diagonal 4, se tiver, escolhe a celula vazia (similar a acima)
    for(i = 0; i < N-1; i++){
        empty_row = -1;
        z = count = 0;
        symbol = ' ';
        for(j = 0; j < N; j++){
            if (config->board[N-1-j-i-z][j] != ' ' && config->board[N-1-j-i-z][j] != 'O') {
                symbol = config->board[N-1-j-i-z][j];
                break;
            }
            if (j+i >= N-1) z -= 2; // rebate na parede
        }
        if (symbol == ' ') continue;
        z = 0;
        for(j = 0; j < N; j++){
            if (config->board[N-1-j-i-z][j] == symbol) count++;
            else if (config->board[N-1-j-i-z][j] == ' '){
                empty_row = N-1-j-i-z; empty_col = j;
            }
            if (j+i >= N-1) z -= 2;
        }
        if (count == N-1 && empty_row != -1){
            *row = empty_row; *col = empty_col;
            return;
        }
    }


    // se nenhuma condicao acima foi satisfeita escolhe aleatoriamente
    play_random(row, col, config);

}
