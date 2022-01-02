#include "game_control.h"

void init_field(struct controller *field)
{
    for(int i = 0; i < FIELD_HEIGHT; i++)
    {
        for(int j = 0; j < FIELD_WIDTH; j++)
        {
            field->matrix[i][j] = ' ';
        }
    }
    field->x = 5;
    field->y = 0;
    field->points = 0;
}

void clear_field(char original_matrix[FIELD_HEIGHT][FIELD_WIDTH], char copy_matrix[FIELD_HEIGHT][FIELD_WIDTH])
{
    for(int i = 0; i < FIELD_HEIGHT; i++)
    {
        for(int j = 0; j < FIELD_WIDTH; j++)
        {
            original_matrix[i][j] = copy_matrix[i][j];
        }
    }
}

void display_field(const char matrix[FIELD_HEIGHT][FIELD_WIDTH], const int points)
{
    for(int i = 4; i < FIELD_HEIGHT; i++)
    {
        for(int j = 0; j < FIELD_WIDTH; j++)
        {
            if(i == 4)
                write(1, "- ", 2);
            else if(i == FIELD_HEIGHT-1)
                write(1, "# ", 3);
            else if(j == 0 || j == FIELD_WIDTH-1)
                write(1, "|", 1);
            else
            {
                char ch[] = {matrix[i][j]};
                write(1, ch, 1);
                write(1, " ", 1);
            }
        }
        write(1, "\n", 1);
    }
    printf("POINTS: %d\n", points);
}

void init_tetromino_to_field(struct tetromino tetro, struct controller *field)
{
    field->x = 5;
    field->y = 0;

    for(int i = 0; i < tetro.height; i++)
    {
        for(int j = 0; j < tetro.width; j++)
        {
            if(tetro.matrix[i][j] == HASHTAG)
                field->matrix[i+field->y][j+field->x] = tetro.matrix[i][j];
        }
    }
}

struct tetromino rotate_tetromino(const struct tetromino current_tetromino)
{
    struct tetromino rotated_tetromino = current_tetromino;
    clear_tetromino(&rotated_tetromino);

    if(current_tetromino.width == 1 && current_tetromino.height == 4)
    {
        //Rotates 90 degrees back and forth
        for(int i = 0; i < TETROMINO_HEIGHT; i++)
        {
            for(int j = 0; j < TETROMINO_WIDTH; j++)
            {
                if(current_tetromino.matrix[i][j] == HASHTAG)
                    rotated_tetromino.matrix[j][i] = current_tetromino.matrix[i][j];
            }
        }
        return rotated_tetromino;
    }
    else if(current_tetromino.width == 2 && current_tetromino.height == 2) //Doesn´t rotate
        return current_tetromino;

    //Reading values from the current_tetromino up to down and left to right
    //And writing values to rotated_tetromino up to down and right to left 
    //Rotates 360 around
    for(int i = 0, k = 0; k < TETROMINO_HEIGHT; i++, k++)
    {
        for(int j = 0, l = TETROMINO_WIDTH-1; l >= 0; j++, l--)
        {
            if(current_tetromino.matrix[j][i] == HASHTAG)
            {
                rotated_tetromino.matrix[k][l] = current_tetromino.matrix[j][i];
            }
        }
    }
    return rotated_tetromino;
}

void move_tetromino(struct tetromino *tetro, struct controller *field)
{
    //Moves tetromino sideways if it doesn´t collide with any walls
    if(tetro->move == RIGHT && tetro->wall_collision != RIGHT)
    {
        field->x += RIGHT;
    }
    else if(tetro->move == LEFT && tetro->wall_collision != LEFT)
    {
        field->x += LEFT;
    }
    tetro->wall_collision = 0;
    tetro->move = 0;
}

void draw_tetromino(struct tetromino *tetro, struct controller *field)
{
    field->y++; //Drops tetromino by one

    for(int i = 0; i < TETROMINO_HEIGHT; i++)
    {
        for(int j = 0; j < TETROMINO_WIDTH; j++)
        {
            if(tetro->matrix[i][j] == HASHTAG)
            {
                tetro->y = i;
                tetro->x = j;

                //Draws tetromino HASHTAG to the field->matrix
                field->matrix[tetro->y+field->y][tetro->x+field->x] = tetro->matrix[i][j];

                //Checks collision with the side walls
                if(tetro->x+field->x == FIELD_WIDTH-2)
                    tetro->wall_collision = RIGHT;
                else if(tetro->x+field->x == 1)
                    tetro->wall_collision = LEFT;

                //Checks collision after the draw
                collision_detection(tetro, *field);
                
            }
        }
    }
}

void collision_detection(struct tetromino *tetro, const struct controller field)
{
    //Check if tetromino collides with bottom
    if(tetro->y+field.y+1 == FIELD_HEIGHT-1)
        tetro->dropped = true;

    //Check if tetromino collides with other tetrominos
    const char current_position = field.matrix[tetro->y+field.y][tetro->x+field.x];
    const char next_position = field.matrix[tetro->y+field.y+1][tetro->x+field.x];

    if(current_position == HASHTAG && next_position == HASHTAG)
        tetro->dropped = true;
    
    return;
}

bool row_complete(char field[FIELD_HEIGHT][FIELD_WIDTH])
{
    for(int i = FIELD_HEIGHT-1; i > 0; i--)
    {
        int counter = 0;
        for(int j = 0; j < FIELD_WIDTH; j++)
        {
            if(field[i][j] == HASHTAG)
                counter++;
        }
        if(counter >= FIELD_WIDTH-2)
        {
            delete_row(field, i);
            return true;
        }
    }
    return false;
}

void delete_row(char field[FIELD_HEIGHT][FIELD_WIDTH], const int row)
{
    for(int i = row; i > 2; i--)
    {
        for(int j = 0; j < FIELD_WIDTH; j++)
        {
            field[i][j] = field[i-1][j];
        }
    }
}

bool fail_game(const struct controller field)
{
    for(int i = 0; i < FIELD_WIDTH; i++)
    {
        if(field.matrix[5][i] == HASHTAG)
            return true;
    }
    return false;
}