// estrutura de estados do jogo
typedef struct {
    int menu,
	rules,
        options,
        ingame,
        gameover,
        exit;
} State;

// estrutura com configuracoes do jogo
typedef struct {
    int num_players,
        player_2,
        difficulty,
        winner,
        N,
        winner_marks[9][9];
    char board[9][9];
} Config;

// funcao auxiliar para trocar estado de jogo
void set_state(int state_id, State *state);

// funcoes uteis
void insert_mark(int row, int col, int player, Config *config);
void reset_array(int array[9][9]);
int random_int(int min, int max);
