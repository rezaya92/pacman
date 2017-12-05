#include <stdio.h>
#include "game.h"
#include "map.h"
#include "physics.h"
//TODO change speed
void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    int i,j;
    FILE *initiate;
    outGame->cheeses = 0;
    outGame->cherries = 0;
    outGame->cheeses = 0;
    outPacman->speed= 0;
    outGame->ghosts = 4;
    initiate = fopen(filename,"r");
    fscanf(initiate,"%d %d", &outMap->height, &outMap->width );
    for ( i = 0; i < outMap->height; ++i) {
        fscanf(initiate, "%*c");
        for (j = 0; j < outMap->width; ++j) {
            fscanf(initiate, "%c", &outMap->cells[j][i]);
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

    fscanf(initiate,"%d", &outGame->score);
    fscanf(initiate,"%*s %d %d (%d,%d) (%lf,%lf)" ,&outPacman->dir, &outPacman->health, &outPacman->startY, &outPacman->startX, &outPacman->y, &outPacman->x);
    for (i = 0; i < 4; ++i) {
        outGhosts[i].speed = 0;
        fscanf(initiate,"%*s %d %d", &outGhosts[i].dir, &outGhosts[i].blue);
        outGhosts[i].blue = 1 - outGhosts[i].blue;
        outGhosts[i].blueCounterDown=0;
        if (outGhosts[i].blue == 1) fscanf(initiate,"%lld", &outGhosts[i].blueCounterDown);
        outGhosts[i].blueCounterDown *= CYCLES_PER_SEC;
        fscanf(initiate," ");
        fscanf(initiate,"(%d,%d) (%lf,%lf)", &outGhosts[i].startY, &outGhosts[i].startX, &outGhosts[i].y, &outGhosts[i].x);
        outGhosts[i].type = i;
    }
    return;
}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    // fill me
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
