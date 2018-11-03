#include <stdio.h>
#include <stdlib.h>
#include "../header/const.h"
#include "../header/utils.h"
#include "../header/interface.h"

void display_menu(char feedback[]){
    system("clear");
    puts(COLOR_YELLOW "Bem-vindo ao Jogo da Velha estendido\n" COLOR_RESET);
 
    puts(COLOR_YELLOW "            ###   ###");
    puts("           ###   ###");
    puts("      #################");
    puts("         ###   ###");
    puts("    #################");
    puts("       ###   ###");
    puts("      ###   ###" COLOR_CYAN " GAME" COLOR_RESET);
    
    puts("\nSelecione a opção desejada\n");
    puts("1 - Iniciar jogo");
    puts("2 - Como jogar");
    puts("3 - Opções");
    puts("4 - Sair");

    puts(feedback);
}


void display_rules(char feedback[]){
    system("clear");
    puts(COLOR_GREEN "Regras do Jogo da Velha\n" COLOR_RESET);
    
    puts("Para vencer o jogo da velha estendido é necessário que o jogador consiga assinalar seu símbolo em todas as células de uma linha, coluna, diagonal ou subdiagonal. Caso nenhum jogador consiga satisfazer esta condição, o jogo termina empatado.\n\n");
    
    puts("Selecione a opção desejada\n");
    puts("1 - Iniciar jogo");
    puts("2 - Voltar ao menu principal");
    puts("3 - Sair");

    puts(feedback);
}


void display_options(Config *config, char feedback[]){
    system("clear");
    puts(COLOR_GREEN "Opções do jogo\n" COLOR_RESET);
    
    puts("Selecione o código e a numeracão para fazer alteracão desejada");
    puts(COLOR_CYAN "Exemplo: A2 altera número de jogadores para 3, c5 altera dimensões para 5\n" COLOR_RESET);

    puts("A - Número de jogadores");
    if (config->num_players == 2) puts("\t2 - " COLOR_GREEN "Dois jogadores" COLOR_RESET);
    else puts("\t2 - Dois jogadores");
    if (config->num_players == 3) puts("\t3 - " COLOR_GREEN "Três jogadores\n" COLOR_RESET);
    else puts("\t3 - Três jogadores\n");
    
    puts("B - Tipo do jogador 2");
    if (config->player_2 == PLAYER_HUMAN) puts("\t1 - " COLOR_GREEN "Humano" COLOR_RESET);
    else puts("\t1 - Humano");
    if (config->player_2 == PLAYER_MACHINE) puts("\t2 - " COLOR_GREEN "Máquina\n" COLOR_RESET);
    else puts("\t2 - Máquina\n");
    
    puts("C - Número de dimensões do tabuleiro");
    printf("\tN - Número de dimensões (mínimo 4, máximo 9, atual\x1b[32m %d\x1b[0m)\n\n", config->N);
 
    puts("D - Dificuldade do jogo");
    if(config->difficulty == DIFFICULTY_EASY) puts("\t1 - " COLOR_GREEN "Fácil" COLOR_RESET);
    else puts("\t1 - Fácil");
    if(config->difficulty == DIFFICULTY_NORMAL) puts("\t2 - " COLOR_GREEN "Normal" COLOR_RESET);
    else puts("\t2 - Normal");
    if(config->difficulty == DIFFICULTY_HARD) puts("\t3 - " COLOR_GREEN "Difícil\n" COLOR_RESET);
    else puts("\t3 - Difícil\n");     

    puts("E - Selecionar a opção desejada");
    puts("\t1 - Iniciar jogo");
    puts("\t2 - Voltar ao menu principal");
    puts("\t3 - Sair");

    puts(feedback);
}


void display_gameover(Config *config, char feedback[]){
    system("clear");
    puts(COLOR_GREEN "Fim de jogo!\n\n" COLOR_RESET);

    if(config->winner == PLAYER_1)
        display_board(config, -1, COLOR_GREEN "O jogador 1 venceu!\n" COLOR_RESET);    
    else if (config->winner == PLAYER_2)
        display_board(config, -1, COLOR_GREEN "O jogador 2 venceu!\n" COLOR_RESET);
    else if (config->winner == PLAYER_3)
        display_board(config, -1, COLOR_GREEN "O jogador 3 venceu!\n" COLOR_RESET);
    else    
        display_board(config, -1, COLOR_GREEN "Não houve vencedor!\n" COLOR_RESET);
    
    puts("Selecione a opção desejada\n");
    puts("1 - Jogar novamente");
    puts("2 - Menu principal");
    puts("3 - Sair");

    puts(feedback);
}


void display_board(Config *config, int player, char feedback[]){
    int N = config->N;
    system("clear");

    // numeracao das colunas
    printf(COLOR_CYAN "\n     ");
    for (int j = 0; j < N; j++)
        printf("  %d   ", j); 
    printf(COLOR_RESET "\n\n");      

    for (int i = 0; i < N; i++){
        // este bloco de codigo printa uma linha do tabuleiro a cada iteracao i     

        // parte superior da celula
        printf("     ");
        for (int j = 0; j < N; j++){
            if (j < N-1) printf("     |");
            else printf("     ");
        }   
        printf("\n");

        // legenda das linhas
        printf(COLOR_CYAN "  %d  " COLOR_RESET, i); 

        // parte central onde tem o simbolo
        for (int j = 0; j < config->N; j++){
            if (j < N-1 && config->winner_marks[i][j]) printf(COLOR_YELLOW "  %c  " COLOR_RESET "|", config->board[i][j]);
            else if (j < N-1) printf("  %c  |", config->board[i][j]);
            else if (config->winner_marks[i][j]) printf(COLOR_YELLOW "  %c  " COLOR_RESET, config->board[i][j]);
            else printf("  %c  ", config->board[i][j]);
        }     
        printf("\n");

        // parte inferior da celula
        printf("     ");
        for (int j = 0; j < N; j++){
            if (j < N-1 && i < N-1) printf("_____|");
            else if (j < N-1 && !(i < N-1)) printf("     |");
            else if (!(j < N-1) && i < N-1) printf("_____");
        }   
        printf("\n");
    }

    printf("\n\n");


    if (player != -1)
        printf("Vez do jogador %d\n\nDigite os números da linha e da coluna ou " COLOR_CYAN "ex" COLOR_RESET " para sair:\n", player);  
    puts(feedback);
}

