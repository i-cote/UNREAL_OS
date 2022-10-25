#ifndef TRON_H_
#define TRON_H_

#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define CLEAR_SCREEN 3
#define BLOCK_SIZE 10

typedef struct {
    int x;
    int y;
    int x_dir;
    int y_dir;
} player_position;

void tron();
void tronMenu();
void tronGame();

#endif