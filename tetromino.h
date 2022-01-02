#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdio.h>
#include <stdbool.h>

#define TETROMINO_WIDTH 4
#define TETROMINO_HEIGHT 4

#define TETROMINO_TYPES 7

#define HASHTAG '#'
#define EMPTY ' '

#define LEFT -1
#define RIGHT 1

struct tetromino
{
    int width, height;
    char matrix[TETROMINO_HEIGHT][TETROMINO_WIDTH];
    int x, y;
    int rotation;
    int move;
    int wall_collision;
    bool dropped;
    bool input_received;
};

void init_tetrominos(struct tetromino array[TETROMINO_TYPES]);
void clear_tetromino(struct tetromino *tetro);
void copy_matrix(struct tetromino *tetro, char src[TETROMINO_HEIGHT][TETROMINO_WIDTH]);
void display_tetromino(const struct tetromino tetro);
#endif //TETROMINO_H