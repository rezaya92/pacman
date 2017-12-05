
//test needed

#include <stdio.h>
#include <string.h>


struct player {
    int initial_x;
    int initial_y;
    int direction;
    int health;
    int points;
    int x;
    int y;
} pacman;


struct bots {
    int direction;
    int initial_x;
    int initial_y;
    int x;
    int y;
    int aggression;
    int defense_time;
} bot[4];
/* bot[0] = blinky
 * bot[1] = pinky
 * bot[2] = clyde
 * bot[3] = inky*/


int row,column,minutes_elapsed,seconds_elapsed,map[100][100];


int main() {
    initiate();
    scan();
    move();
    printf ("(%d,%d)\n", pacman.y,pacman.x);
    printf("%d\n",pacman.points);
    if (win() == 0) printf("Yes");
    else printf("No");
    return 0;
}

void initiate(){
    int i;
    for ( i = 0; i < 4 ; ++i) {
        bot[i].defense_time = 0;
    }
    return;
}

void scan(){
    int i,j;
    scanf("%d %d", &row, &column);
    for ( i = 0; i < row; ++i) {
        scanf("%*c");
        for ( j = 0; j < column; ++j) {
            scanf("%c", &map[i][j]);
        }
    }
    scanf("%d:%d %d", &minutes_elapsed , &seconds_elapsed, &pacman.points);
    scanf("%*s %d %d (%d,%d) (%d,%d)", &pacman.direction, &pacman.health, &pacman.initial_y, &pacman.initial_x, &pacman.y, &pacman.x);
    for (i = 0; i < 4; ++i) {
        scanf("%*s %d %d", &bot[i].direction, &bot[i].aggression);
        if (bot[i].aggression == 0) scanf("%d", &bot[i].defense_time);
        scanf(" ");
        scanf("(%d,%d) (%d,%d)", &bot[i].initial_y, &bot[i].initial_x, &bot[i].y, &bot[i].x);
    }
    return;
}


void evaluate( int destin_y, int destin_x){
    int eaten = 0,i;
    switch (map[destin_y][destin_x]){
        case '#':
            return;
        case '*':
            pacman.x = destin_x;
            pacman.y = destin_y;
            pacman.points += 1;
            map[destin_y][destin_x] = '_';
            break;
        case '_':
            pacman.x = destin_x;
            pacman.y = destin_y;
            break;
        case '^':
            pacman.x = destin_x;
            pacman.y = destin_y;
            pacman.points += 20;
            map[destin_y][destin_x] = '_';
            break;
        case 'O':
            pacman.x = destin_x;
            pacman.y = destin_y;
            map[destin_y][destin_x] = '_';
            pineapple();
            break;
    }
    for (i = 0; i < 4 ; ++i) {
        if (pacman.x == bot[i].x && pacman.y == bot[i].y && bot[i].aggression == 0) bot_collision(i);
    }
    for (i = 0; i < 4; ++i) {
        if (pacman.x == bot[i].x && pacman.y == bot[i].y && eaten == 0 && bot[i].aggression == 1) {
            bot_collision(i);
            eaten = 1;
        }
    }
    return;
}


void move(){
    int destin_y = pacman.y, destin_x =pacman.x;
    switch (pacman.direction){
        case 1:
            destin_y = pacman.y - 1;
            break;
        case 2:
            destin_x = pacman.x + 1;
            break;
        case 3:
            destin_y = pacman.y + 1;
            break;
        case 4:
            destin_x = pacman.x - 1;
            break;
    }
    destin_x = destin_x < 0 ? destin_x % column + column : destin_x % column;
    destin_y = destin_y < 0 ? destin_y % row + row : destin_y % row;
    time();
    evaluate( destin_y, destin_x);
    return;
}


void bot_collision(int i){

    if ( bot[i].aggression == 1){
        pacman.health -= 1;
        if (pacman.health > 0) {
            pacman.x = pacman.initial_x;
            pacman.y = pacman.initial_y;
            evaluate(pacman.y,pacman.x);
        }
        else lose();
    }
    else {
        pacman.points += 50;
    }
    return;
}





void time(){
    int i;
    seconds_elapsed += 1;
    minutes_elapsed += seconds_elapsed / 60;
    seconds_elapsed %= 60;
    for (i = 0; i < 4; ++i) {
        if (bot[i].aggression == 0){
            bot[i].defense_time -= 1;
            if (bot[i].defense_time < 0) {
                bot[i].aggression = 1;
                bot[i].defense_time = 0;
            }
        }
    }
    return;
}

void pineapple(){
    int i;
    for ( i = 0; i < 4 ; ++i) {
        bot[i].aggression = 0;
        bot[i].defense_time = 10;
    }
    return;
}


void lose(){
    return;
}




int win(){
    int i,j,sum = 0;
    for ( i = 0; i < row; ++i) {
        for ( j = 0; j < column; ++j) {
            switch (map[i][j]){
                case '*':
                    sum += 1;
                    break;
                case 'O':
                    sum += 1;
                    break;
                default:
                    break;
            }
        }
    }
    return sum;
}




