// libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// utils
#include "sys_utils.h"
#include "dbg_utils.h"

// vars
#define FIELD_SIZE 9
#define STATS_COUNT 4
char field[FIELD_SIZE] = "         ";
int stats[STATS_COUNT];
bool is_win = false;
bool is_drawn = false;
bool is_usr_first;
bool is_usr_win;
char enemy_sym;
char usr_sym;
char data_file[] = ".game_usr_data.txt\0";
char usr_data_path[128] = "\0";

// headers
bool check_win(char cur_field[]);
bool check_drawn(char cur_field[]);
bool menu(void);
int inp_usr_step(void);
int calc_enemy_step(char cur_field[]);
void draw_field(void);
void update(void);
void start_session(void);
void mk_usr_step(void);
void mk_enemy_step(void);
void clear_data(void);
void check_result(void);
void game_circle(void);
void game(void);
void main_menu(void);
void menu_liest(void);
void menu_info(void);
void save_stats(const char *file_name);
bool get_stats(const char *file_name);

// funcs
void draw_field() {
    printf("┌───┬───┬───┐\n│ %c │ %c │ %c │\n├───┼───┼───┤\n│ %c │ %c │ %c │\n├───┼───┼───┤\n│ %c │ %c │ %c │\n└───┴───┴───┘\n",
        field[0], field[1], field[2],
	field[3], field[4], field[5],
	field[6], field[7], field[8]);
}

void update() {
    sys_console_clear();
    draw_field();
}

bool check_win(char cur_field[]) {
    if (((cur_field[0] == cur_field[1]) && (cur_field[1] == cur_field[2]) && (cur_field[1] != ' ')) || // 012
        ((cur_field[3] == cur_field[4]) && (cur_field[4] == cur_field[5]) && (cur_field[4] != ' ')) || // 345
        ((cur_field[6] == cur_field[7]) && (cur_field[7] == cur_field[8]) && (cur_field[7] != ' ')) || // 678
        ((cur_field[0] == cur_field[3]) && (cur_field[3] == cur_field[6]) && (cur_field[3] != ' ')) || // 036
        ((cur_field[1] == cur_field[4]) && (cur_field[4] == cur_field[7]) && (cur_field[4] != ' ')) || // 147
        ((cur_field[2] == cur_field[5]) && (cur_field[5] == cur_field[8]) && (cur_field[5] != ' ')) || // 258
        ((cur_field[0] == cur_field[4]) && (cur_field[4] == cur_field[8]) && (cur_field[4] != ' ')) || // 048
        ((cur_field[2] == cur_field[4]) && (cur_field[4] == cur_field[6]) && (cur_field[4] != ' ')) /* 246*/ ) {
        return true;
    } else {
        return false;
    }
}

bool check_drawn(char cur_field[]) {
    int k = 0;
    for (int i = 0; i < FIELD_SIZE; ++i) {
        if (cur_field[i] == ' ') ++k;
    }
    if (k == 0) {
        return true;
    } else {
        return false;
    }
}

void start_session() {
    again_select: ;
    sys_console_clear();
    printf("Select the symbol 'X' or '0'.\n");
    char input_sym = getchar();
    if ((input_sym == 'X') || (input_sym == 'x')) {
        usr_sym = 'X';
        enemy_sym = '0';
        is_usr_first = true;
    } else if ((input_sym == '0') || (input_sym == 'o') || (input_sym == 'O')) {
        usr_sym = '0';
        enemy_sym = 'X';
        is_usr_first = false;
    } else {
        goto again_select;
    }
}

int inp_usr_step() {
    int step_val;
    printf("\nEnter your step [1;9] - ");
    scanf("%i", &step_val);
    return step_val;
}

void mk_usr_step() {
    again: ;
    int step_val = inp_usr_step() - 1;
    if ((step_val < 0) || (step_val > 8)) {
        update();
        goto again;
    } else if (field[step_val] == ' ') {
        field[step_val] = usr_sym;
        update();
    } else {
        update();
        goto again;
    }
}

int calc_enemy_step(char cur_field[]) {
    // attack
    for (int cell = 0; cell < FIELD_SIZE; ++cell) {
        if (cur_field[cell] == ' ') {
            cur_field[cell] = enemy_sym;
            if (check_win(cur_field))
                 return cell;
            cur_field[cell] = ' ';
        }
    }
    // defense
    for (int cell = 0; cell < FIELD_SIZE; ++cell) {
        if (cur_field[cell] == ' ') {
            cur_field[cell] = usr_sym;
            if (check_win(cur_field))
                return cell;
            cur_field[cell] = ' ';
        }
    }
    // freedom step
    int free_size = 0;
    for (int cell = 0; cell < FIELD_SIZE; ++cell) {
        if (cur_field[cell] == ' ') ++free_size;
    }
    int free_cells[free_size];
    int index = 0;
    for (int cell = 0; cell < FIELD_SIZE; ++cell) {
        if (cur_field[cell] == ' ') {
            free_cells[index] = cell;
            ++index;
        }
    }
    srand(time(NULL));
    return free_cells[(rand() % free_size)];
}

void mk_enemy_step() {
    field[calc_enemy_step(field)] = enemy_sym;
}

bool menu() {
    menu: ;
    sys_console_clear();
    printf("Enter symbol:\n\t's' or '1' to play\n\t'l' or '2' to view statistics\n\t'i' or '3' to view info\n\t'q' or '0' to quit\n");
    char symbol = getchar();
    if ((symbol == 's') || (symbol == 'S') || (symbol == '1')) {
        return false;
    } else if ((symbol == 'l') || (symbol == 'L') || (symbol == '2')) {
        sys_console_clear();
        menu_liest();
        goto menu;
    } else if ((symbol == 'i') || (symbol == 'I') || (symbol == '3')) {
        sys_console_clear();
        menu_info();
        goto menu;
    } else if ((symbol == 'q') || (symbol == 'Q') || (symbol == '0')) {
        sys_console_clear();
        return true;
    } else {
        goto menu;
    }
}

void menu_liest() {
    if (get_stats(usr_data_path)) save_stats(usr_data_path);
    printf("Liest statistics.\n");
    sys_print_file(usr_data_path);
    printf("\nPress 'Enter' to close.\n");
    getchar();
    getchar();
}

void menu_info() {
    printf("Info about this project.\n\nGithub repository: https://github.com/roman62b/game.git\n\nPress 'Enter' to close.\n");
    getchar();
    getchar();
}

void clear_data() {
    is_win = false;
    is_drawn = false;
    for (int i = 0; i < FIELD_SIZE; ++i) { field[i] = ' '; }
}

void check_result() {
    update();
    if (is_win) {
        if (is_usr_win) {
            printf("\nYou win!\n");
            ++stats[1];
        } else {
            printf("\nYou lose!\n");
            ++stats[2];
        }
    } else {
        printf("\nThe game ended in a draw!\n");
        ++stats[3];
    }
    ++stats[0];
    getchar();
    getchar();
}

bool get_stats(const char *file_name) {
    char buffer[128];
    int k = 0;
    FILE *file = fopen(file_name, "r");
    if (file) {
        while (fgets(buffer, 128, file) != NULL) {
            char *ptr = &buffer[0];
            for (int i = 0; i < 128; ++i) {
                if (buffer[i] == '\t') {
                    ptr += i;
                    stats[k] = atoi(ptr);
                    ++k;
                } else if (buffer[i] == '\n') break;
            }
        }
        fclose(file);
        return false;
    } else {
        for (int i = 0; i < STATS_COUNT; ++i) { stats[i] = 0; }
        return true;
    }
}

void save_stats(const char *file_name) {
    char message[128];
    snprintf(message, sizeof message,
            "\nGames Count:\n\t%d\nWins:\n\t%d\nDefeats:\n\t%d\nDrawns:\n\t%d\n",
            stats[0], stats[1], stats[2], stats[3]);
    FILE *file = fopen(file_name, "w");
    if (file) {
        fputs(message, file);
        fclose(file);
    }
}

void game_circle() { // too fat
    while (true) {
        update();
        if (is_usr_first) {
            mk_usr_step();
            update();
            is_win = check_win(field);
            is_drawn = check_drawn(field);
            if ((!is_win) && (!is_drawn)) {
                mk_enemy_step();
                is_win = check_win(field);
                is_drawn = check_drawn(field);
                if (!((!is_win) && (!is_drawn))) {
                    is_usr_win = false;
                    break;
                }
            } else {
                is_usr_win = true;
                break;
            }
        } else {
            mk_enemy_step();
            update();
            is_win = check_win(field);
            is_drawn = check_drawn(field);
            if ((!is_win) && (!is_drawn)) {
                mk_usr_step();
                is_win = check_win(field);
                is_drawn = check_drawn(field);
                if (!((!is_win) && (!is_drawn))) {
                    is_usr_win = true;
                    break;
                }
            } else {
                is_usr_win = false;
                break;
            }
        }
    }
}

void game() {
    clear_data();
    start_session();
    game_circle();
    if (get_stats(usr_data_path)) save_stats(usr_data_path);
    check_result();
    save_stats(usr_data_path);
    main_menu();
}

void main_menu() {
    if (menu()) {
        exit(0);
    } else {
        game();
    }
}

int main(void) {
    // initialization path to usr home dir
    sys_get_data_path(usr_data_path, data_file);

    printf("Tic-Tac-Toe is running...\n");
    sleep(1);
    main_menu();
}
