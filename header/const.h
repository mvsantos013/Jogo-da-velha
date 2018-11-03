// cores do terminal
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


// estados de jogo
#define STATE_GAMEOVER 1
#define STATE_MENU     2
#define STATE_RULES    3
#define STATE_OPTIONS  4
#define STATE_INGAME   5
#define STATE_EXIT     6


// identificacoes
#define PLAYER_1 1
#define PLAYER_2 2
#define PLAYER_3 3

#define PLAYER_1_SYMBOL 'X'
#define PLAYER_2_SYMBOL 'O'
#define PLAYER_3_SYMBOL 'I'

#define PLAYER_HUMAN   1
#define PLAYER_MACHINE 2

#define DIFFICULTY_EASY   1
#define DIFFICULTY_NORMAL 2
#define DIFFICULTY_HARD   3


// opcoes
#define MIN_PLAYERS 2
#define MAX_PLAYERS 3
#define MIN_DIM 4
#define MAX_DIM 9


// validacoes
#define MARK_VALID    1
#define MARK_INVALID  2
#define MARK_TAKEN    3
#define INPUT_VALID   4
#define INPUT_INVALID 5
#define INPUT_EXIT    6


// erros
#define ERROR_INVALID_OPTION    COLOR_RED "\nOpção inválida, tente novamente.\n" COLOR_RESET
#define ERROR_MARK_TAKEN        COLOR_RED "\nEsta posição já está marcada!\n" COLOR_RESET
#define ERROR_MARK_INVALID      COLOR_RED "\nPosição inválida!\n" COLOR_RESET
#define ERROR_NON_NUMERIC_VALUE COLOR_RED "\nDigite valores numéricos\n" COLOR_RESET


// mensagens
#define MESSAGE_TYPE_AGAIN "Digite novamente: \n"
#define MESSAGE_GAME_END   COLOR_GREEN "\nFim de jogo!\n" COLOR_RESET

