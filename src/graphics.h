#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include "game.h"
#include "map.h"
#include "SDL2_gfxPrimitives.h"

void InitiateGraphics(Pacman pacman,Game game, double time, SDL_Renderer *renderer);
void DrawMap(Map *map, SDL_Renderer * renderer);
void DrawBots(Ghost *ghost, Pacman *pacman, SDL_Renderer *renderer, Map *map);
void DrawExtras(SDL_Renderer * renderer, Map *map,Game *game, Pacman *pacman, int time);
void pause(SDL_Renderer *renderer, int *quit, Map * map);
int menu(SDL_Renderer *rederer, Map * map, Pacman* pacman, Game*game);



#endif
