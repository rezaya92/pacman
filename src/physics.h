#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "input.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

// TO WRITE
Direction decidePacman(const Map* map, Pacman* pacman, Action action);

// TO WRITE
Direction decideGhost(const Map* map, Ghost *ghost, Pacman *pacman, Ghost *blinky);

int valid_direction(int x,int y, int dir, Map *map);

void NearestEmptyBlock (const Map *map, int x, int y, int answer[2]);

Direction NearestPath(const Map *map, int origin_x, int origin_y, int destin_x, int destin_y);

#endif
