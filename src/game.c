#include <stdio.h>
#include "game.h"
#include "map.h"
#include "physics.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    int i,j;
    FILE *data;
    outGame->cheeses = 0;
    outGame->cherries = 0;
    outGame->cheeses = 0;
    outPacman->speed = PACMAN_DEFAULT_SPEED;
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
                    outGame->cherries++;
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
    srand(time(NULL));
}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    double distance;
    int destin_x,destin_y,i;
    destin_x = (int)outPacman->x + (outPacman->dir == 2);
    destin_y = (int)outPacman->y + (outPacman->dir == 3);
    distance = fabs(destin_x + destin_y - outPacman->x - outPacman->y);
    if (distance < 0.624){
        Standardize(destin_x,map->width);
        Standardize(destin_y,map->height);
        switch (map->cells[destin_x][destin_y]){
            case CELL_CHEESE:
                outGame->score += CHEESE_SCORE;
                outGame->cheeses -= 1;
                map->cells[destin_x][destin_y] = CELL_EMPTY;
                break;
            case CELL_CHERRY:
                outGame->score += CHERRY_SCORE;
                outGame->cherries -= 1;
                map->cells[destin_x][destin_y] = CELL_EMPTY;
                break;
            case CELL_PINEAPPLE:
                outGame->score += PINEAPPLE_SCORE;
                outGame->pineapples -= 1;
                map->cells[destin_x][destin_y] = CELL_EMPTY;
                for ( i = 0; i < 4 ; ++i) {
                    outGhosts[i].blue = 1;
                    outGhosts[i].blueCounterDown = BLUE_DURATION;
                }
                break;
        }
    }
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    double distance = sqrt ( pow (outGhost->y - outPacman->y , 2 ) + pow ( outGhost->x - outPacman->x , 2 ) );
    if ( distance < 0.5){
        if (outGhost->blue == 1){
            outGhost->blue = 0;
            outGhost->blueCounterDown = 0;
            outGhost->x = outGhost->startX;
            outGhost->y = outGhost->startY;
        }
        else{
            outPacman->x = outPacman->startX;
            outPacman->y = outPacman->startY;
            outPacman->health -= 1;
        }
    }
}

bool isGameFinished(Game* game, Pacman* pacman) {
    if (pacman->health <= 0 || (game->cheeses == 0 && game->pineapples == 0))return true;
    else return false;
}

void checkGhostState(Ghost* ghost) {
    if (ghost->blue == 1){
        ghost->blueCounterDown -= 1;
        if (ghost->blueCounterDown == 0) ghost->blue = 0;
    }
}