#include <stdlib.h>
#include <time.h>
#include "physics.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "game.h"
#include "map.h"

Direction NearestPath(Map *map, int origin_x, int origin_y, int destin_x, int destin_y){
    int choices[4] = {0,0,0,0};
    if (origin_x == destin_x && origin_y == destin_y)   return rand()%4 + 1;
    else {
        int i;
        int front = 0;
        int rear = 0;
        int distance = 1;
        int queue[10000][4];
        for ( i = 1; i <= 4; ++i,rear++) {
            queue[rear][0] = origin_x - ((i - 3) % 2); // first parameter is x of the block.
            queue[rear][1] = origin_y + ((i - 2) % 2); // second parameter is y of the block.
            queue[rear][2] = i; //third parameter is the initial direction which got us here.
            queue[rear][3] = distance; //fourth parameter is distance
            Standardize(queue[rear][0],map->width);
            Standardize(queue[rear][1],map->height);
        }
        while( rear > front ){
            if (queue[front][0] == destin_x && queue[front][1] == destin_y) return queue[front][2];
            else if (map->cells[queue[front][0]][queue[front][1]] != CELL_BLOCK) {
                //printf("\n%d %d\n",queue[front][0],queue[front][1]);
                //sleep(1);
                for ( i = 1, distance++; i <= 4; ++i,rear++) {
                    queue[rear][0] = queue[front][0] - ((i - 3) % 2);
                    queue[rear][1] = queue[front][1] + ((i - 2) % 2);
                    queue[rear][2] = queue[front][2];
                    queue[rear][3] = queue[front][3] + 1;
                    Standardize(queue[rear][0],map->width);
                    Standardize(queue[rear][1],map->height);
                }
            }
            front++;
        }
    }
}

Direction decideGhost(const Map* map, Ghost *ghost, Pacman *pacman, Ghost *blinky) {
    /*printf("\n%d\n",NearestPath(map,1,0,4,3));
    sleep(1);
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
    }*/
    //printf("\n%d\n",NearestPath(map,ghost->x,ghost->y,pacman->x,pacman->y));
    //sleep(1);
    return NearestPath(map,ghost->x,ghost->y,pacman->x,pacman->y);
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