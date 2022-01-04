#include "tetromino.h"
#include "game_control.h"

int nanosleep(const struct timespec *req, struct timespec *rem);

void *user_input(void *arguments);

int main()
{
    //Initializing tetrominos
    struct tetromino tetromino_array[TETROMINO_TYPES];
    init_tetrominos(tetromino_array);

    //Initializing game field
    struct controller field;
    init_field(&field);

    //Giving a seed to the random number generator
    srand(time(NULL));

    //Initializing variables for handling time
    const long start_time = 999999999;
    const long subtract_time = 111111111;
    struct timespec ts = {0, start_time};

    //Starting the game
    while(1)
    {
        struct controller copy_field = field; //Copying the field for later use

        int random = rand() % (TETROMINO_TYPES); //Defines which tetromino is spawned
        struct tetromino tetro = tetromino_array[random]; //Assigning the selected tetromino to a single struct

        //Creating the initial thread
        pthread_t thread = 0;
        if(pthread_create(&thread, NULL, user_input, (void*)&tetro) != 0)
        {
            fprintf(stderr, "Error creating a thread\n");
            exit(EXIT_FAILURE);
        }

        //Spawning tetromino to the starting position in the field
        init_tetromino_to_field(tetro, &field);
        while(tetro.dropped != true)
        {
            //If thread function is called. Join the thread and create new one
            if(tetro.input_received == true)
            {
                pthread_join(thread, NULL);
                if(pthread_create(&thread, NULL, user_input, (void*)&tetro) != 0)
                {
                    fprintf(stderr, "Error creating a thread\n");
                    exit(EXIT_FAILURE);
                }
                tetro.input_received = false;
            }

            //If rotation value is changed. Then rotate tetromino
            if(tetro.rotation == 1)
            {
                tetro = rotate_tetromino(tetro);
                tetro.rotation = 0;
            }
            system("clear"); //Clears screen
            clear_field(field.matrix, copy_field.matrix); //Copies copy_field.matrix to field.matrix
            move_tetromino(&tetro, &field); //Handles sideway movement of the tetromino
            draw_tetromino(&tetro, &field); //Draws the tetromino to field.matrix
            display_field(field.matrix, field.points); //Displays the field
            nanosleep(&ts, NULL); //Waits for 999999999 nanoseconds
        }
        
        //After the loop join the current thread
        pthread_join(thread, NULL);
        if(row_complete(field.matrix)) //Checks if row is complete
        {
            //Reduces the time by subtract_time
            printf("ts.tv_nsec: %ld\n", (long)ts.tv_nsec);
            if(ts.tv_nsec > subtract_time)
                ts.tv_nsec -= subtract_time;
                
            field.points++;
        }
        display_field(field.matrix, field.points);
        tetro.dropped = false;
        if(fail_game(field)) //Checks for fail_game condition
            break;
    }

    system("clear");
    printf("GAME OVER\n");
    sleep(2);
    display_field(field.matrix, field.points);
    return 0;
}

//This is the thread function that handles user_input
void *user_input(void *arguments)
{
    char input = ' ';
    scanf("%c", &input);
    if(input == 'r')
    {
        (*(struct tetromino*)arguments).rotation = 1;
    }
    else if(input == 'a')
    {
        (*(struct tetromino*)arguments).move = LEFT;
    }
    else if(input == 'd')
    {
        (*(struct tetromino*)arguments).move = RIGHT;
    }
    (*(struct tetromino*)arguments).input_received = true;
    return NULL;
}