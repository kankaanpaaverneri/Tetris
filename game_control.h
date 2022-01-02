#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#include "tetromino.h"

#define FIELD_HEIGHT 28
#define FIELD_WIDTH 13

struct controller
{
    char matrix[FIELD_HEIGHT][FIELD_WIDTH];
    int x, y;
    int points;
};

void init_field(struct controller *field);
void clear_field(char original_matrix[FIELD_HEIGHT][FIELD_WIDTH], char copy_matrix[FIELD_HEIGHT][FIELD_WIDTH]);
void display_field(const char matrix[FIELD_HEIGHT][FIELD_WIDTH], const int points);
void init_tetromino_to_field(struct tetromino tetro, struct controller *field);
struct tetromino rotate_tetromino(const struct tetromino current_tetromino);
void move_tetromino(struct tetromino *tetro, struct controller *field);
void draw_tetromino(struct tetromino *tetro, struct controller *field);
void collision_detection(struct tetromino *tetro, const struct controller field);

bool row_complete(char field[FIELD_HEIGHT][FIELD_WIDTH]);
void delete_row(char field[FIELD_HEIGHT][FIELD_WIDTH], const int row);
bool fail_game(const struct controller field);

#endif //GAME_CONTROL_H