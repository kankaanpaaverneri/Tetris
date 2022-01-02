#include "tetromino.h"

void init_tetrominos(struct tetromino array[TETROMINO_TYPES])
{
    char first[TETROMINO_HEIGHT][TETROMINO_WIDTH] =
    {
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', '#', ' '}
    };

    array[0].width = 3;
    array[0].height = 4;
    array[0].rotation = 0;
    array[0].move = 0;
    array[0].x = 0;
    array[0].y = 0;
    array[0].input_received = false;
    array[0].dropped = false;
    array[0].wall_collision = 0;
    copy_matrix(&array[0], first);

    char second[TETROMINO_HEIGHT][TETROMINO_WIDTH] = 
    {
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '}
    };

    array[1].width = 3;
    array[1].height = 4;
    array[1].rotation = 0;
    array[1].move = 0;
    array[1].x = 0;
    array[1].y = 0;
    array[1].input_received = false;
    array[1].dropped = false;
    array[1].wall_collision = 0;
    copy_matrix(&array[1], second);

    char third[TETROMINO_HEIGHT][TETROMINO_WIDTH] =
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', '#', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', '#', ' '}
    };

    array[2].width = 3;
    array[2].height = 4;
    array[2].rotation = 0;
    array[2].move = 0;
    array[2].x = 0;
    array[2].y = 0;
    array[2].input_received = false;
    array[2].dropped = false;
    array[2].wall_collision = 0;
    copy_matrix(&array[2], third);

    char fourth[TETROMINO_HEIGHT][TETROMINO_WIDTH] = 
    {
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', '#', ' '}
    };

    array[3].width = 3;
    array[3].height = 4;
    array[3].rotation = 0;
    array[3].move = 0;
    array[3].x = 0;
    array[3].y = 0;
    array[3].input_received = false;
    array[3].dropped = false;
    array[3].wall_collision = 0;
    copy_matrix(&array[3], fourth);

    char fifth[TETROMINO_HEIGHT][TETROMINO_WIDTH] =
    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', '#', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', ' ', ' '}
    };
    array[4].width = 3;
    array[4].height = 4;
    array[4].rotation = 0;
    array[4].move = 0;
    array[4].x = 0;
    array[4].y = 0;
    array[4].input_received = false;
    array[4].dropped = false;
    array[4].wall_collision = 0;
    copy_matrix(&array[4], fifth);

    char sixth[TETROMINO_HEIGHT][TETROMINO_WIDTH] = 
    {
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    };

    array[5].width = 3;
    array[5].height = 3;
    array[5].rotation = 0;
    array[5].move = 0;
    array[5].x = 0;
    array[5].y = 0;
    array[5].input_received = false;
    array[5].dropped = false;
    array[5].wall_collision = 0;
    copy_matrix(&array[5], sixth);

    char seventh[TETROMINO_HEIGHT][TETROMINO_WIDTH] =
    {
        {'#', ' ', ' ', ' '},
        {'#', ' ', ' ', ' '},
        {'#', ' ', ' ', ' '},
        {'#', ' ', ' ', ' '}
    };

    array[6].width = 1;
    array[6].height = 4;
    array[6].rotation = 0;
    array[6].move = 0;
    array[6].x = 0;
    array[6].y = 0;
    array[6].input_received = false;
    array[6].dropped = false;
    array[6].wall_collision = 0;
    copy_matrix(&array[6], seventh);
}

void clear_tetromino(struct tetromino *tetro)
{
    for(int i = 0; i < TETROMINO_HEIGHT; i++)
    {
        for(int j = 0; j < TETROMINO_WIDTH; j++)
        {
            tetro->matrix[i][j] = EMPTY;
        }
    }
}

void copy_matrix(struct tetromino *tetro, char src[TETROMINO_HEIGHT][TETROMINO_WIDTH])
{
    for(int i = 0; i < TETROMINO_HEIGHT; i++)
    {
        for(int j = 0; j < TETROMINO_WIDTH; j++)
        {
            tetro->matrix[i][j] = src[i][j];
        }
    }
}

void display_tetromino(const struct tetromino tetro)
{
    int i = 0, j = 0; 
    for(i = 0; i < tetro.height; i++)
    {
        for(j = 0; j < tetro.width; j++)
        {
            if(tetro.matrix[i][j] == HASHTAG)
                printf("%c ", tetro.matrix[i][j]);
        }
        printf("\n");
    }
}