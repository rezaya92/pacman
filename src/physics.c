#include <stdlib.h>
#include <time.h>
#include "physics.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "game.h"
#include "map.h"

Direction decideGhost(const Map* map, Ghost* ghost) {
    int dir;
    int destin_x,destin_y;
    int flag = 0;
    srand(clock());
    while (flag == 0){
        destin_x = (int) ghost->x;
        destin_y = (int) ghost->y;
        dir = rand() % 5;
        switch (dir) {
            case 1:
                destin_y = (int)ghost->y - 1;
                break;
            case 2:
                destin_x = (int)ghost->x + 1;
                break;
            case 3:
                destin_y = (int)ghost->y + 1;
                break;
            case 4:
                destin_x = (int)ghost->x - 1;
                break;
        }
        destin_x = destin_x < 0 ? destin_x % map->width + map->width : destin_x % map->width;
        destin_y = destin_y < 0 ? destin_y % map->height + map->height : destin_y % map->height;
        if (map->cells[destin_x][destin_y] != CELL_BLOCK) flag = 1;
    }
    dir = dir == 0 ? -1 : dir;
    return dir;
}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    int dir = pacman->dir;
    int destin_y = pacman->y, destin_x =pacman->x;
    printf("\n%d %d\n",action,MOVE_ACTION_MASK);
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
        destin_x = destin_x < 0 ? destin_x % map->width + map->width : destin_x % map->width;
        destin_y = destin_y < 0 ? destin_y % map->height + map->height : destin_y % map->height;
        if (map->cells[destin_x][destin_y] != CELL_BLOCK) return dir;
    }

    destin_y = pacman->y;
    destin_x = pacman->x;
    switch (pacman->dir){
        case 1:
            destin_y = (int)pacman->y - 1;
            break;
        case 2:
            destin_x = (int)pacman->x + 1;
            break;
        case 3:
            destin_y = (int)pacman->y + 1;
            break;
        case 4:
            destin_x = (int)pacman->x - 1;
            break;
    }
    destin_x = destin_x < 0 ? destin_x % map->width + map->width : destin_x % map->width;
    destin_y = destin_y < 0 ? destin_y % map->height + map->height : destin_y % map->height;
    if (map->cells[destin_x][destin_y] != CELL_BLOCK) return pacman->dir;
    else return -1;
}