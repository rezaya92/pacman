#include <stdio.h>
#include "game.h"
#include "map.h"
#include "physics.h"
#include <math.h>
#include <time.h>
void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    int i,j;
    FILE *data;
    outGame->cheeses = 0;
    outGame->cherries = 0;
    outGame->cheeses = 0;
    outPacman->speed= PACMAN_DEFAULT_SPEED;
    outGame->ghosts = 4;
    data = fopen(filename,"r");
    fscanf(data,"%d %d", &outMap->height, &outMap->width );
    for ( i = 0; i < outMap->height; ++i) {
        fscanf(data, "%*c");
        for (j = 0; j < outMap->width; ++j) {
            fscanf(data, "%c", &outMap->cells[j][i]);
            switch (outMap->cells[j][i]){
                case '*':
                    outGame->cheeses++;
                    break;
                case 'O':
                    outGame->pineapples++;
                    break;
                case '^':
                    outGame->cheeses++;
                    break;
            }
        }
    }
    fscanf(data,"%d", &outGame->score);
    fscanf(data,"%*s %d %d (%d,%d) (%lf,%lf)" ,&outPacman->dir, &outPacman->health, &outPacman->startY, &outPacman->startX, &outPacman->y, &outPacman->x);
    for (i = 0; i < 4; ++i) {
        outGhosts[i].speed = GHOST_DEFAULT_SPEED;
        fscanf(data,"%*s %d %d", &outGhosts[i].dir, &outGhosts[i].blue);
        outGhosts[i].blue = 1 - outGhosts[i].blue;
        outGhosts[i].blueCounterDown=0;
        if (outGhosts[i].blue == 1) fscanf(data,"%lld", &outGhosts[i].blueCounterDown);
        outGhosts[i].blueCounterDown *= CYCLES_PER_SEC;
        fscanf(data," ");
        fscanf(data,"(%d,%d) (%lf,%lf)", &outGhosts[i].startY, &outGhosts[i].startX, &outGhosts[i].y, &outGhosts[i].x);
        outGhosts[i].type = i;
    }
}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    double distance;
    int destin_x,destin_y,i;
    switch (outPacman->dir){
        case -1:
            destin_x = (int)outPacman->x;
            destin_y = (int)outPacman->y;
            distance = 0;
            break;
        case 1:
            destin_x = (int)outPacman->x;
            destin_y = (int)outPacman->y;
            distance = outPacman->y - destin_y;
            break;
        case 2:
            destin_x = (int)outPacman->x + 1;
            destin_y = (int)outPacman->y;
            distance = destin_x - outPacman->x;
            break;
        case 3:
            destin_x = (int)outPacman->x;
            destin_y = (int)outPacman->y + 1;
            distance = destin_y - outPacman->y;
            break;
        case 4:
            destin_x = (int)outPacman->x;
            destin_y = (int)outPacman->y;
            distance = outPacman->x - destin_x;
            break;
    }
    if (distance < 0.5){
        switch (map->cells[destin_x][destin_y]){
            case CELL_CHEESE:
                outGame->score += CHEESE_SCORE;
                map->cells[destin_x][destin_y] = CELL_EMPTY;
                break;
            case CELL_CHERRY:
                outGame->score += CHERRY_SCORE;
                map->cells[destin_x][destin_y] = CELL_EMPTY;
                break;
            case CELL_PINEAPPLE:
                map->cells[destin_x][destin_y] = CELL_EMPTY;
                outGame->score += PINEAPPLE_SCORE;
                for ( i = 0; i < 4 ; ++i) {
                    outGhosts[i].blue = 1;
                    outGhosts[i].blueCounterDown = BLUE_DURATION;
                }
                break;
        }
    }
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    // fill me
}

bool isGameFinished(Game* game, Pacman* pacman) {
    // fill me
}

void checkGhostState(Ghost* ghost) {
    // fill me


}
