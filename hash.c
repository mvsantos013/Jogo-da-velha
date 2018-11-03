#include <stdio.h>
#include <stdlib.h>
#include "header/const.h"        // constantes
#include "header/utils.h"        // funcoes e estruturas uteis
#include "header/render.h"       // funcoes de cada estado de jogo
//#include "header/interface.h"  // funcoes que imprimem na tela
//#include "header/valid.h"      // funcoes de validacoes
//#include "header/machine.h"    // funcoes do jogador maquina


int main(void){

    // estrutura de estados do jogo
    State *state = (State *) malloc(sizeof(State));
    // altera o estado do jogo para tela de menu
    set_state(STATE_MENU, state);


    // estrutura com configuracoes do jogo
    Config *config = (Config *) malloc(sizeof(Config));
    // configuracao inicial padrao (pode ser alterada dentro do jogo na tela de opcoes)
    config->num_players = 2;                // numero de jogadores
    config->N = 4;                          // dimensoes
    config->player_2 = PLAYER_MACHINE;      // tipo do jogador2
    config->difficulty = DIFFICULTY_NORMAL; // dificuldade


    // loop de jogo, verifica qual estado o jogo se encontra e 'renderiza' o equivalente
    while(!state->exit){

        if (state->menu) render_menu(state, config);
        else if (state->rules) render_rules(state, config);
        else if (state->options) render_options(state, config);
        else if (state->ingame) render_ingame(state, config);
        else if (state->gameover) render_gameover(state, config); 
        else exit_game(state);

    }

    return 0;
}
