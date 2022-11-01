#include <tron.h>
#include <syscallsAPI.h>
#include <stdioAPI.h>
#include <beeper.h>
#include <color.h>

// Start of the game
// Awaits for the user to press the space bar to start the game
void tron(){
    tronMenu();
    char c = 0;
    int found = 0;
    while (!found){
        while ((c = getChar()) != ' '){
            if (c == 'q'){
                return;
            }
        }
        found = 1;
    }
    tronGame();
    
}

// Prints the menu of the game
void tronMenu(){
    clearScreen();
    printfColor("Welcome to Tron!\n",white);
    printfColor("Press spacebar start the game\n",white);
    printfColor("Press q to exit the game\n\n",white);
    printfColor("Player 1: W A S D\n",white);
    printfColor("Player 2: I J K L\n",white);

}

// Runs the game
// Sets the initial position of the players and the initial direction
// Waits for the user to press a key to change the direction of the players
// Checks if the players have collided with the walls or with each other
// Prints the new position of the players
// When it ends, it prints the winner and makes a beep
void tronGame(){
    sys_print_asm(CLEAR_SCREEN,0,0);
    player_position player1 = {300,500,BLOCK_SIZE,0};
    player_position player2 = {500,300,-BLOCK_SIZE,0};

    sys_print_asm(PLAYER_ONE, player1.x, player1.y);
    sys_print_asm(PLAYER_TWO, player2.x, player2.y);
    int c = 0;

    char player1_direction = 'd';
    char player2_direction = 'j';

    int player1_status = 0;
    int player2_status = 0;

    int time_length = BASE_SPEED;
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

            player1_status = sys_print_asm(PLAYER_ONE, player1.x, player1.y);
            player2_status = sys_print_asm(PLAYER_TWO, player2.x, player2.y);
            
            if (speed_cycles == SPEED_CYCLES){
                time_length <= MAX_SPEED ? time_length : time_length--;
                speed_cycles = 0;
            }
        }
    
    }
    sys_print_asm(CLEAR_SCREEN,0,0);
    if (player1_status == 1){
        printfColor("Player BLUE wins!\n",white);
        beep();
    }
    if (player2_status == 1){
        printfColor("Player RED wins!\n",white);
        beep();
    }

}

