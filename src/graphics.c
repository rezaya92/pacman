#include "game.h"
#include "map.h"
#include "SDL2_gfxPrimitives.h"

void InitiateGraphics(Pacman pacman,Game game, double time, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
}


void DrawMap(Map *map, SDL_Renderer *renderer){
    int i,j;
    boxColor(renderer, 10, 70 , map->width * MAP_MAX_SIZE + 10, map->height * MAP_MAX_SIZE + 70, 0xFFFF0000);
    for (i = 0; i < map->height; ++i) {
        for (j = 0; j < map->width; ++j) {
            switch (map->cells[j][i]){
                case CELL_BLOCK:
                    boxColor(renderer, 10 + j*MAP_MAX_SIZE, 70 + i*MAP_MAX_SIZE, 10 + (j + 1)*MAP_MAX_SIZE, 70 + (i + 1) * MAP_MAX_SIZE, 0xFF00FF00);
                case CELL_PINEAPPLE:
                    break;
                case CELL_CHERRY:
                    break;
                case CELL_CHEESE:
                    break;
            }
        }
    }
}


void DrawBots(Ghost *ghost, Pacman *pacman, SDL_Renderer *renderer){
    filledPieColor(renderer,10 + pacman->x * MAP_MAX_SIZE + MAP_MAX_SIZE/2, 70 + pacman->y * MAP_MAX_SIZE + MAP_MAX_SIZE / 2, MAP_MAX_SIZE/2,45,-45,0XFF0FF000);
    for (int i = 0; i < 4; ++i) {
        filledPieColor(renderer, 10 + ghost[i].x * MAP_MAX_SIZE + MAP_MAX_SIZE / 2, 70 + ghost[i].y * MAP_MAX_SIZE + MAP_MAX_SIZE / 2, MAP_MAX_SIZE / 2, 45, -45, 0XFF0FF000);
    }
}

