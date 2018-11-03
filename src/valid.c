#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../header/const.h"
#include "../header/utils.h"
#include "../header/valid.h"


// verifica se input e valido (numerico ou iniciais da palavra exit)
int is_valid_input(char c_row, char c_col){
    if(isdigit(c_row) && isdigit(c_col)) return INPUT_VALID;
    else if(c_row == 'e' && c_col == 'x') return INPUT_EXIT;

    return INPUT_INVALID;
}


// verifica se marcacao e valida (nao esta fora do limite do tabuleiro e nao foi preenchida)
int is_valid_mark(int row, int col, Config *config){
    if (row > config->N - 1 || row < 0 || col > config->N - 1 || col < 0) return MARK_INVALID;
    else if (config->board[row][col] != ' ') return MARK_TAKEN;

    return MARK_VALID;
}


// verifica se o jogo terminou
int is_gameover(Config *config){
    int z, count, N = config->N;
    char symbol;

    /*
        decidiu-se fazer cada verificação em um loop diferente para evitar alocar mais variáveis, também é possível que a condição desta função apareça logo no início, permitindo que os loops restantes sejam ignorados evitando computação desnecessária

    */

    // verifica se houve pontuacao maxima em alguma linha
    for(int i = 0; i < N; i++){
        // reseta contador de pontuacao
        count = 0;
        // simbolo inicial para saber se os restantes sao iguais a ele
        // se nao tiver simbolo inicial muda para '0' pra evitar que o contador conte espacos vazios
        symbol = (config->board[i][0] != ' ') ? config->board[i][0] : '0';

        for(int j = 0; j < N; j++){
            if (config->board[i][j] == symbol) count++;     // pontuacao na linha i
            config->winner_marks[i][j] = 1; // memoriza sequencia pra colorir no final
        }
        // se houve pontuacao maxima anota o vencedor e encerra a funcao
        if (count == N) {
            config->winner = (symbol == PLAYER_1_SYMBOL) ? PLAYER_1
                           : (symbol == PLAYER_2_SYMBOL) ? PLAYER_2
                           : PLAYER_3;
            return 1;
        }
        reset_array(config->winner_marks);
    }


    // verifica se houve pontuacao maxima em alguma coluna (similar à acima)
    for(int i = 0; i < N; i++){
        count = 0;
        symbol = (config->board[0][i] != ' ') ? config->board[0][i] : '0';
        for(int j = 0; j < N; j++){
            if (config->board[j][i] == symbol) count++; // pontuacao na linha coluna i
            config->winner_marks[j][i] = 1;
        }
        if (count == N) {
            config->winner = (symbol == PLAYER_1_SYMBOL) ? PLAYER_1
                           : (symbol == PLAYER_2_SYMBOL) ? PLAYER_2
                           : PLAYER_3;
            return 1;
        }
        reset_array(config->winner_marks);
    }
    

    // verifica se houve pontuacao maxima em alguma sub-diagonal 1 (similar à acima)
    for(int i = 0; i < N; i++){
        z = count = 0;
        symbol = (config->board[0][i] != ' ') ? config->board[0][i] : '0';
        for(int j = 0; j < N; j++){
            if (config->board[j][j+i+z] == symbol) count++;
            config->winner_marks[j][j+i+z] = 1;
            if (j+i >= N-1) z -= 2; // z e responsavel por 'rebater' a diagonal na parede, sequencias tangentes
        }
        if (count == N) {
            config->winner = (symbol == PLAYER_1_SYMBOL) ? PLAYER_1
                           : (symbol == PLAYER_2_SYMBOL) ? PLAYER_2
                           : PLAYER_3;
            return 1;
        }
        reset_array(config->winner_marks);
    }

    // a partir daqui os loops de fora começam em 1 e terminam em N-1 para evitar computar as diagonais principais já computadas no loop anterior
    // verifica se houve pontuacao maxima em alguma sub-diagonal 2 (similar à acima)
    for(int i = 1; i < N-1; i++){
        z = count = 0;
        symbol = (config->board[i][N-1] != ' ') ? config->board[i][N-1] : '0';
        for(int j = 0; j < N; j++){
            if (config->board[j+i+z][N-1-j] == symbol) count++;
            config->winner_marks[j+i+z][N-1-j] = 1;
            if (j+i >= N-1) z -= 2;
        }
        if (count == N) {
            config->winner = (symbol == PLAYER_1_SYMBOL) ? PLAYER_1
                           : (symbol == PLAYER_2_SYMBOL) ? PLAYER_2
                           : PLAYER_3;
            return 1;
        }
        reset_array(config->winner_marks);
    }

 
    // verifica se houve pontuacao maxima em alguma sub-diagonal 3 (similar à acima)
    for(int i = 1; i < N-1; i++){
        z = count = 0;
        symbol = (config->board[N-1][N-1-i] != ' ') ? config->board[N-1][N-1-i] : '0';
        for(int j = 0; j < N; j++){
            if (config->board[N-1-j][N-1-j-i-z] == symbol) count++;
            config->winner_marks[N-1-j][N-1-j-i-z] = 1;
            if (j+i >= N-1) z -= 2;
        }
        if (count == N) {
            config->winner = (symbol == PLAYER_1_SYMBOL) ? PLAYER_1
                           : (symbol == PLAYER_2_SYMBOL) ? PLAYER_2
                           : PLAYER_3;
            return 1;
        }
        reset_array(config->winner_marks);
    }


    // verifica se houve pontuacao maxima em alguma sub-diagonal 4 (similar à acima)
    for(int i = 1; i < N-1; i++){
        z = count = 0;
        symbol = (config->board[N-1-i][0] != ' ') ? config->board[N-1-i][0] : '0';
        for(int j = 0; j < N; j++){
            if (config->board[N-1-j-i-z][j] == symbol) count++;
            config->winner_marks[N-1-j-i-z][j] = 1;
            if (j+i >= N-1) z -= 2;
        }
        if (count == N) {
            config->winner = (symbol == PLAYER_1_SYMBOL) ? PLAYER_1
                           : (symbol == PLAYER_2_SYMBOL) ? PLAYER_2
                           : PLAYER_3;
            return 1;
        }
        reset_array(config->winner_marks);
    }

    return 0;
}
