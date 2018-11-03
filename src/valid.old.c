/* funcao is_gameover depreciada onde todas as verificações eram feitas simultaneamente */

// verifica se o jogo terminou
int is_gameover(Config *config){
    int z, count_1, count_2, count_3, count_4, count_5, count_6, N = config->N;
    char symbol_1, symbol_2, symbol_3, symbol_4, symbol_5, winner_symbol = '0';

    for(int i = 0; i < N; i++){
        // reseta contadores de pontuacao das linhas/colunas/diagonais
        count_1 = count_2 = count_3 = count_4 = count_5 = count_6 = 0;
        // simbolo inicial para saber se os restantes sao iguais a ele
        // se nao tiver simbolo inicial muda para '0' pra evitar que o contador conte espacos vazios
        symbol_1 = (config->board[i][0] != ' ') ? config->board[i][0] : '0';
        symbol_2 = (config->board[0][i] != ' ') ? config->board[0][i] : '0';
        symbol_3 = (config->board[i][N-1] != ' ') ? config->board[i][N-1] : '0';
        symbol_4 = (config->board[N-1][N-1-i] != ' ') ? config->board[N-1][N-1-i] : '0';
        symbol_5 = (config->board[N-1-i][0] != ' ') ? config->board[N-1-i][0] : '0';
        z = 0;

        // contabiliza o numero de preenchimentos em cada linha, coluna e subdiagonais
        for(int j = 0; j < N; j++){
            if (config->board[i][j] == symbol_1) count_1++;             // pontuacao na linha i
            if (config->board[j][i] == symbol_2) count_2++;             // pontuacao na coluna i
            if (config->board[j][j+i+z] == symbol_2) count_3++;         // pontuacao das sub-diagonais 1
            if (config->board[j+i+z][N-1-j] == symbol_3) count_4++;     // pontuacao das sub-diagonais 2
            if (config->board[N-1-j][N-1-j-i-z] == symbol_4) count_5++; // pontuacao das sub-diagonais 3
            if (config->board[N-1-j-i-z][j] == symbol_5) count_6++;     // pontuacao das sub-diagonais 4
            if (j+i >= N-1) z -= 2;                                     // 'rebate' a diagonal na parede 
        }
        
        // se houve N preenchimentos em alguma linha/coluna/diagonal armazena o simbolo vencedor em winner_symbol
        if (count_1 == N) winner_symbol = symbol_1;
        else if (count_2 == N) winner_symbol = symbol_2;
        else if (count_3 == N) winner_symbol = symbol_2;
        else if (count_4 == N) winner_symbol = symbol_3;
        else if (count_5 == N) winner_symbol = symbol_4;
        else if (count_6 == N) winner_symbol = symbol_5;
        
        // retorna o jogador vencedor
        if (winner_symbol == PLAYER_1_SYMBOL) return PLAYER_1;
        else if (winner_symbol == PLAYER_2_SYMBOL) return PLAYER_2;
        else if (winner_symbol == PLAYER_3_SYMBOL) return PLAYER_3;
      
    }

    return 0;
}
