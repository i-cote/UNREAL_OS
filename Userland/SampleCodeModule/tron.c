#include <tron.h>
#include <syscallsAPI.h>
#include <stdioAPI.h>

void tron(){
    tronMenu();
    char c = 0;
    tronGame();
    
}

void tronMenu(){
    clearScreen();
    printf("Welcome to Tron!\n");
    printf("Press any key to start the game\n");
    printf("Press q to go back to the main menu\n");
    printf("Press backspace to exit the game\n\n");
    printf("Player 1: W A S D\n");
    printf("Player 2: I J K L\n");

}

void tronGame(){
    sys_print_asm(CLEAR_SCREEN,"",0,0);
    player_position player1 = {300,500,BLOCK_SIZE,0};
    player_position player2 = {500,300,-BLOCK_SIZE,0};

    sys_print_asm(PLAYER_ONE, "", player1.x, player1.y);
    sys_print_asm(PLAYER_TWO, "", player2.x, player2.y);
    int c = 0;

    char player1_direction = 'd';
    char player2_direction = 'a';

    int player1_status = 0;
    int player2_status = 0;

    int time_length = 9;
    int speed_cycles = 0;
    int time = sys_ticker_asm(GET_TIME, time_length);
    

    while ((c = getChar()) != '\b' && !player1_status && !player2_status)
    {

        if (c == 'q')
        {
            break;
        }
        if (c == 'w' && player1_direction != 's')
        {
            player1_direction = 'w';
            player1.x_dir = 0;
            player1.y_dir = -BLOCK_SIZE;
        }
        if (c == 's' && player1_direction != 'w')
        {
            player1_direction = 's';
            player1.x_dir = 0;
            player1.y_dir = BLOCK_SIZE;
        }
        if (c == 'a' && player1_direction != 'd')
        {
            player1_direction = 'a';
            player1.x_dir = -BLOCK_SIZE;
            player1.y_dir = 0;
        }
        if (c == 'd' && player1_direction != 'a')
        {
            player1_direction = 'd';
            player1.x_dir = BLOCK_SIZE;
            player1.y_dir = 0;
        }
        if (c == 'i' && player2_direction != 'k')
        {
            player2_direction = 'i';
            player2.x_dir = 0;
            player2.y_dir = -BLOCK_SIZE;
        }
        if (c == 'k' && player2_direction != 'i')
        {
            player2_direction = 'k';
            player2.x_dir = 0;
            player2.y_dir = BLOCK_SIZE;
        }
        if (c == 'j' && player2_direction != 'l')
        {
            player2_direction = 'j';
            player2.x_dir = -BLOCK_SIZE;
            player2.y_dir = 0;
        }
        if (c == 'l' && player2_direction != 'j')
        {
            player2_direction = 'l';
            player2.x_dir = BLOCK_SIZE;
            player2.y_dir = 0;
        }


        if (sys_ticker_asm(GET_TIME,time_length) != time)
        {
            speed_cycles++;
            
            time = sys_ticker_asm(GET_TIME,time_length);
            player1.x += player1.x_dir;
            player1.y += player1.y_dir;
            player2.x += player2.x_dir;
            player2.y += player2.y_dir;

            player1_status = sys_print_asm(PLAYER_ONE, "", player1.x, player1.y);
            player2_status = sys_print_asm(PLAYER_TWO, "", player2.x, player2.y);
            
            if (speed_cycles == SPEED_CYCLES){
                time_length < MAX_SPEED ? time_length : time_length--;
                speed_cycles = 0;
            }
        }
    
    }
    sys_print_asm(CLEAR_SCREEN,"",0,0);
    if (player1_status == 1)
    {
        printf("Player BLUE wins!\n");
        return 1;
    }
    if (player2_status == 1)
    {
        printf("Player RED wins!\n");
        return 2;
    }

}

