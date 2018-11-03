#include <stdio.h>
#include <stdlib.h>
#include "../header/const.h"
#include "../header/utils.h"
#include "../header/render.h"
#include "../header/interface.h"
#include "../header/valid.h"
#include "../header/machine.h"


// função responsável por renderizar o menu para o jogador e lidar com a entrada
void render_menu(State *state, Config *config){
    char key;

    // mostra tela do menu sem mensagem de feedback
    display_menu("");

    // loop da tela de menu
    while(state->menu){
        scanf(" %c", &key); getchar();

        // altera estado de jogo de acordo com a opcao escolhida
        if (key == '1') set_state(STATE_INGAME, state);
        else if (key == '2') set_state(STATE_RULES, state);
        else if (key == '3') set_state(STATE_OPTIONS, state);
        else if (key == '4') exit_game(state);
        else display_menu(ERROR_INVALID_OPTION);  // mostra menu e mensagem de erro ao jogador
    }
}


void render_rules(State *state, Config *config){
    char key;

    display_rules("");

    // loop da tela de regras
    while(state->rules){
        scanf(" %c", &key); getchar();

        if (key == '1') set_state(STATE_INGAME, state);
        else if (key == '2') set_state(STATE_MENU, state);
        else if (key == '3') exit_game(state);
        else display_rules(ERROR_INVALID_OPTION);
    }
}


void render_options(State *state, Config *config){
    char key1, key2;
    int ikey2, delta = 'A' - 'a', aindex = 'a', zindex = 'z', invalid_option = 0;

    display_options(config, "");

    // loop da tela de regras
    while(state->options){
        scanf(" %c  %c", &key1, &key2); getchar();
        
        if (key1 >= aindex && key1 <= zindex)
            key1 += delta; // converte minuscula para maiuscula
        ikey2 = (int) key2 - '0';

        // altera numero de jogadores
        if (key1 == 'A'){
            if (ikey2 >= MIN_PLAYERS && ikey2 <= MAX_PLAYERS) config->num_players = ikey2;
            else invalid_option = 1;
        }
        // altera tipo do jogador 2
        else if (key1 == 'B'){
            if (ikey2 == PLAYER_HUMAN || ikey2 == PLAYER_MACHINE) config->player_2 = ikey2;
            else invalid_option = 1;
        }
        // altera numero de dimensoes do tabuleiro
        else if (key1 == 'C') {
            if (ikey2 >= MIN_DIM && ikey2 <= MAX_DIM) config->N = ikey2;
            else invalid_option = 1;
        }
        // altera dificuldade da maquina
        else if (key1 == 'D') {
            if (ikey2 == DIFFICULTY_EASY || ikey2 == DIFFICULTY_NORMAL || ikey2 == DIFFICULTY_HARD) config->difficulty = ikey2;
            else invalid_option = 1;
        }
        // mudanca de estado do jogo
        else if (key1 == 'E'){
            if (key2 == '1') set_state(STATE_INGAME, state);
            else if (key2 == '2') set_state(STATE_MENU, state);
            else if (key2 == '3') exit_game(state);
            else invalid_option = 1;
        } 
        else invalid_option = 1;

        if(invalid_option) {
            display_options(config, ERROR_INVALID_OPTION);
            invalid_option = 0;
        }
        else display_options(config, "");
    }
}


void render_ingame(State *state, Config *config){
    char c_row, c_col;
    int row, col, turn, valid, total_marks, max_marks, on_input = 1;

    // configuracoes iniciais do jogo
    // limpa tabuleiro
    for (int i = 0; i < config->N; i++)
        for (int j = 0; j < config->N; j++)
            config->board[i][j] = ' '; 

    total_marks = 0;                   // quantidade de marcas durante o jogo
    max_marks = config->N * config->N; // maximo de marcas possiveis
    config->winner = 0;                // reseta vencedor
    reset_array(config->winner_marks); // reseta marcas do ultimo vencedor

    // define aleatoriamente quem comeca primeiro
    turn = random_int(1, config->num_players); // gera int de 1 ate a quantidade de jogadores


    // loop do jogo, encerra se alguem vencer ou se todas as celulas forem preenchidas
    while(state->ingame && total_marks < max_marks){

        // mostra o tabuleiro com mensagem direcionada ao jogador do turno e feedback vazio
	display_board(config, turn, "");
        
        // input do jogador
        while(on_input){

            // vez da maquina jogar (selecionar a linha e a coluna) se estiver ligada e for seu turno
            if(turn == PLAYER_2 && config->player_2 == PLAYER_MACHINE) machine_play(&row, &col, config);
            // vez do jogador humano jogar
            else {
                scanf(" %c %c", &c_row, &c_col); getchar();

                valid = is_valid_input(c_row, c_col);
                // cast para int se o input for numerico
                if(valid == INPUT_VALID){
		    row = (int) c_row - '0';
                    col = (int) c_col - '0';
                }
                // sai do jogo se o jogador digitar 'exit'
                else if(valid == INPUT_EXIT){
                    set_state(STATE_GAMEOVER, state);
                    break;
                }
                // input invalido
                else{
                    display_board(config, turn, ERROR_NON_NUMERIC_VALUE MESSAGE_TYPE_AGAIN);
                    continue;
                }
            }
 

            valid = is_valid_mark(row, col, config);
            // marcacao valida
            if(valid == MARK_VALID){
                // insere marcacao no tabuleiro
                insert_mark(row, col, turn, config);

                // verifica apos 2*N-1 jogadas se alguem venceu para terminar o jogo
                if(total_marks >= 2*config->N - 1)
                    if(is_gameover(config))
                        set_state(STATE_GAMEOVER, state);
                
                break;
            }
            // marcacao ja escolhida por outro jogador
	    else if (valid == MARK_TAKEN){
                display_board(config, turn, ERROR_MARK_TAKEN MESSAGE_TYPE_AGAIN);
                continue;
            }
            // marcacao invalida, fora do limite do tabuleiro
            else{
                display_board(config, turn, ERROR_MARK_INVALID MESSAGE_TYPE_AGAIN);
                continue;
            }
        }
       
        // incrementa o numero de marcas no jogo depois da jogada
        total_marks += 1;
        
        // alterna turno entre os jogadores
        turn += 1; 

        // retorna o turno ao primeiro jogador quando todos jogarem
        if(turn == config->num_players + 1)
            turn = PLAYER_1;
    }
 
    set_state(STATE_GAMEOVER, state);
    
}


void render_gameover(State *state, Config *config){
    char key;

    display_gameover(config, "");

    // loop da tela de gameover
    while(state->gameover){
        scanf(" %c", &key); getchar();

        if (key == '1') set_state(STATE_INGAME, state);
        else if (key == '2') set_state(STATE_MENU, state);
        else if (key == '3') exit_game(state);
        else display_gameover(config, ERROR_INVALID_OPTION);
    }
}


void exit_game(State *state){
    puts(MESSAGE_GAME_END);
    set_state(STATE_EXIT, state);
}

