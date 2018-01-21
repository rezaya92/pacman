#include <stdlib.h>
#include <time.h>
#include "physics.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "game.h"
#include "map.h"


int valid_direction(int x,int y, int dir, Map *map){
    x = Standardize(x - (dir != -1) * ((dir - 3) % 2),map->width);
    y = Standardize(y + (dir != -1) * ((dir - 2) % 2),map->height);
    if (map->cells[x][y] != CELL_BLOCK) return 1;
    else return 0;
}

void NearestEmptyBlock (const Map *map, int x, int y, int answer[2]){
    int i, j, front = 0, rear = 0, queue[10000][3], choices[100][2], random, flag = 0, next_x, next_y, IsInQueue, count = 0;
    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear++][2] = 0;
    while( rear > front ){
        if (map->cells[queue[front][0]][queue[front][1]] != CELL_BLOCK){
            choices[count][0] = queue[front][0];
            choices[count++][1] = queue[front][1];
            flag = 1;
        }
        else {
            for ( i = 1; i <= 4; ++i) {
                IsInQueue = 0;
                next_x= Standardize(queue[front][0] - ((i - 3) % 2), map->width);
                next_y= Standardize(queue[front][1] + ((i - 2) % 2), map->height);
                for ( j = 0; j < rear; ++j) {
                    if ( queue[j][0] == next_x && queue[j][1] == next_y ){
                        IsInQueue = 1;
                        break;
                    }
                }
                if (!IsInQueue) {
                    queue[rear][0] = next_x;
                    queue[rear][1] = next_y;
                    queue[rear++][2] = queue[front][2] + 1;
                }
            }
        }
        if (flag == 1 && queue[front][2] != queue[front + 1][2]) break;
        else front++;
    }
    random = rand() % count;
    answer[0] = choices[0][0];
    answer[1] = choices[0][1];
    //not random
}

Direction NearestPath(const Map *map, int origin_x, int origin_y, int destin_x, int destin_y){
    int i, j, front = 0, rear = 0, queue[10000][4], choices[4] = {0,0,0,0}, flag = 0, answer, next_x, next_y, IsInQueue;
    for ( i = 1; i <= 4; ++i,rear++) {
        queue[rear][0] = Standardize(origin_x - ((i - 3) % 2),map->width); // first parameter is x of the block.
        queue[rear][1] = Standardize(origin_y + ((i - 2) % 2),map->height); // second parameter is y of the block.
        queue[rear][2] = i; //third parameter is the initial direction which got us here.
        queue[rear][3] = 1; //fourth parameter is distance
    }
    while( rear > front ){
        if (queue[front][0] == destin_x && queue[front][1] == destin_y){
            choices[ queue[front][2] - 1 ]++;
            flag = 1;
        }
        else if (map->cells[queue[front][0]][queue[front][1]] != CELL_BLOCK) {
            for ( i = 1; i <= 4; ++i) {
                IsInQueue = 0;
                next_x= Standardize(queue[front][0] - ((i - 3) % 2), map->width);
                next_y= Standardize(queue[front][1] + ((i - 2) % 2), map->height);
                for ( j = 0; j < rear; ++j) {
                    if ( queue[j][0] == next_x && queue[j][1] == next_y && queue[j][3] < queue[front][3] + 1 ){
                        IsInQueue = 1;
                        break;
                    }
                }
                if (!IsInQueue) {
                    queue[rear][0] = next_x;
                    queue[rear][1] = next_y;
                    queue[rear][2] = queue[front][2];
                    queue[rear++][3] = queue[front][3] + 1;
                }
            }
        }
        if (flag == 1 && queue[front][3] != queue[front + 1][3]) break;
        else front++;
    }
    answer = rand() % (choices[0] + choices[1] + choices[2] + choices[3]);
    if (answer < choices[0]) return 1;
    else if (answer < choices[0] + choices[1]) return 2;
    else if (answer < choices[0] + choices[1] + choices[2]) return 3;
    else return 4;
}

Direction decideGhost(const Map* map, Ghost *ghost, Pacman *pacman, Ghost *blinky) {
    int i, j, pacman_x_fix, pacman_y_fix, flag, destin_x, destin_y, check_x, check_y, symmetry_x, symmetry_y, blinky_x_fix, blinky_y_fix, nearestblock[2];
    double distance;
    if (ghost->blue == 1) return NearestPath(map,(int)ghost->x,(int)ghost->y, ghost->startX, ghost->startY );
    else {
        pacman_x_fix = Standardize((int)round(pacman->x),map->width);
        pacman_y_fix = Standardize((int)round(pacman->y),map->height);
        blinky_x_fix = Standardize((int)round(blinky->x),map->width);
        blinky_y_fix = Standardize((int)round(blinky->y),map->height);
        if (ghost->type == 0) return NearestPath(map,(int)ghost->x,(int)ghost->y, pacman_x_fix, pacman_y_fix);
        if (ghost->type == 1) {
            for (i = 4; i >= 0; --i) {
                flag = 0;
                destin_x = Standardize(pacman_x_fix - i * (pacman->dir != -1) * ((pacman->dir - 3) % 2),map->width);
                destin_y = Standardize(pacman_y_fix + i * (pacman->dir != -1) * ((pacman->dir - 2) % 2),map->height);
                for (j = i; j >= 0 ; --j) {
                    check_x = Standardize(destin_x + j * (pacman->dir != -1) * ((pacman->dir - 3) % 2),map->width);
                    check_y = Standardize(destin_y - j * (pacman->dir != -1) * ((pacman->dir - 2) % 2),map->height);
                    if (map->cells[check_x][check_y] == CELL_BLOCK) flag = 1;
                }
                if (flag == 0) return NearestPath(map,(int)ghost->x,(int)ghost->y, destin_x, destin_y);
            }
        }
        if (ghost->type == 2) {
            distance = sqrt ( pow (ghost->y - pacman->y , 2 ) + pow ( ghost->x - pacman->x , 2 ) );
            //TODO minimum not calculated
            NearestEmptyBlock(map,0,map->height - 1, nearestblock);
            if (distance > 8) return NearestPath(map,(int)ghost->x,(int)ghost->y, pacman_x_fix, pacman_y_fix);
            else return NearestPath(map,(int)ghost->x,(int)ghost->y, nearestblock[0], nearestblock[1]);
        }
        if (ghost->type == 3) {
            symmetry_x = pacman_x_fix - 2 * (pacman->dir != -1) * ((pacman->dir - 3) % 2);
            symmetry_y = pacman_y_fix + 2 * (pacman->dir != -1) * ((pacman->dir - 2) % 2);
            destin_x = Standardize(blinky_x_fix + 2 * (symmetry_x - blinky_x_fix),map->width);
            destin_y = Standardize(blinky_y_fix + 2 * (symmetry_y - blinky_y_fix),map->height);
            NearestEmptyBlock(map, destin_x, destin_y, nearestblock);
            return NearestPath( map, (int)ghost->x, (int)ghost->y, nearestblock[0], nearestblock[1]);
        }
    }
    //return -1;
}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    int dir;
    if (action & MOVE_ACTION_MASK) {
        switch (action) {
            case ACTION_UP:
                dir = 1;
                break;
            case ACTION_RIGHT:
                dir = 2;
                break;
            case ACTION_DOWN:
                dir = 3;
                break;
            case ACTION_LEFT:
                dir = 4;
                break;
        }
        if (valid_direction((int)pacman->x,(int)pacman->y,dir,map)) return dir;
    }
    if ( valid_direction((int)pacman->x, (int)pacman->y, pacman->dir, map)) return pacman->dir;
    else return -1;
}