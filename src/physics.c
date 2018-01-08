#include <stdlib.h>
#include <time.h>
#include "physics.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "game.h"
#include "map.h"

Direction NearestPath(Map *map, int origin_x, int origin_y, int destin_x, int destin_y){
    if (origin_x == destin_x && origin_y == destin_y)   return rand();
    else {
        int front = 0;
        int rear = 0;
        int level = 1;
        int queue[10000][3];
        queue[rear][0] = origin_x; // first parameter is x of the block.
        queue[rear][1] = origin_y; // second parameter is y of the block.
        queue[rear++][2] = 0; //third parameter is the initial direction which got us here;
        while( rear > front ){

        }
    }
}

Direction decideGhost(const Map* map, Ghost *ghost, Pacman *pacman, Ghost *blinky) {
    int dir;
    int destin_x,destin_y;
    int flag = 0;
    while (flag == 0){
        dir = rand() % 4 + 1;
        destin_x = (int)ghost->x - (dir != 0) * ((dir - 3) % 2); //an innovative way of movement
        destin_y = (int)ghost->y + (dir != 0) * ((dir - 2) % 2); //very innovative
        Standardize(destin_x,map->width);
        Standardize(destin_y,map->height);
        if (map->cells[destin_x][destin_y] != CELL_BLOCK) flag = 1;
    }
    return dir;
}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    int dir = pacman->dir;
    int destin_y = pacman->y, destin_x =pacman->x;
    if (action & MOVE_ACTION_MASK) {
        switch (action) {
            case ACTION_UP:
                destin_y = (int) pacman->y - 1;
                dir = 1;
                break;
            case ACTION_RIGHT:
                destin_x = (int) pacman->x + 1;
                dir = 2;
                break;
            case ACTION_DOWN:
                destin_y = (int) pacman->y + 1;
                dir = 3;
                break;
            case ACTION_LEFT:
                destin_x = (int) pacman->x - 1;
                dir = 4;
                break;
        }
        Standardize(destin_x,map->width);
        Standardize(destin_y,map->height);
        if (map->cells[destin_x][destin_y] != CELL_BLOCK) {
            return dir;
        }
    }
    destin_x = (int)pacman->x - (pacman->dir != -1) * ((pacman->dir - 3) % 2);
    destin_y = (int)pacman->y + (pacman->dir != -1) * ((pacman->dir - 2) % 2);
    Standardize(destin_x,map->width);
    Standardize(destin_y,map->height);
    if (map->cells[destin_x][destin_y] != CELL_BLOCK) return pacman->dir;
    else return -1;
}