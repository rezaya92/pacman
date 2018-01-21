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

Direction NearestPath(Map *map, int origin_x, int origin_y, int destin_x, int destin_y){
    if (origin_x == destin_x && origin_y == destin_y)   {
        while (1){
            int dir = rand() % 4 + 1;
            if (valid_direction(origin_x,origin_y,dir,map)){
                return dir;
            }
        }
    }
    else {
        int i, front = 0, rear = 0, queue[10000][4], choices[4] = {0,0,0,0}, flag = 0, answer;
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
                //return queue[front][2];
            }
            else if (map->cells[queue[front][0]][queue[front][1]] != CELL_BLOCK) {
                for ( i = 1; i <= 4; ++i) {
                    int j,IsInQueue = 0;
                    int next_x= Standardize(queue[front][0] - ((i - 3) % 2), map->width);
                    int next_y= Standardize(queue[front][1] + ((i - 2) % 2), map->height);
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
            front++;
        }
        answer = rand() % (choices[0] + choices[1] + choices[2] + choices[3]);
        if (answer < choices[0]) return 1;
        else if (answer < choices[0] + choices[1]) return 2;
        else if (answer < choices[0] + choices[1] + choices[2]) return 3;
        else return 4;
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
    return NearestPath(map,(int)ghost->x,(int)ghost->y, Standardize((int)round(pacman->x),map->width),Standardize((int)round(pacman->y),map->height));
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