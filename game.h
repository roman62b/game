/*

*/

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/*  */
bool check_win(char cur_field[]);

/*  */
bool check_drawn(char cur_field[]);

/* main_menu component */
bool menu(void);

/*  */
int inp_usr_step(void);

/*  */
int calc_enemy_step(char cur_field[]);

/*  */
void draw_field(void);

/*  */
void update(void);

/*  */
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

#endif // GAME_H_INCLUDED