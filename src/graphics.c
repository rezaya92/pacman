#include <time.h>
#include "game.h"
#include "map.h"
#include "SDL2_gfxPrimitives.h"
#include <../main.h>

void InitiateGraphics(Pacman pacman,Game game, double time, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
}


void DrawMap(Map *map, SDL_Renderer *renderer){
    int i,j;
    rectangleColor(renderer, 11, 71 , map->width * SCALE + 10, map->height * SCALE + 70, 0xFFFF8888);
    for (i = 0; i < map->height; ++i) {
        for (j = 0; j < map->width; ++j) {
            Sint16 vx[6] = {10 + (j + 0.37) * SCALE, 10 + (j + 0.63) * SCALE, 10 + (j + 0.8) * SCALE, 10 + (j + 0.63) * SCALE, 10 + (j + 0.37) * SCALE, 10 + (j + 0.2) * SCALE};
            Sint16 vy[6] = {70 + (i + 0.25) *SCALE, 70 + (i + 0.25) * SCALE, 70 + (i + 0.5) * SCALE, 70 + (i + 0.75) * SCALE, 70 + (i + 0.75) * SCALE, 70 + (i + 0.5) * SCALE};
            switch (map->cells[j][i]){
                case CELL_BLOCK:
                    boxColor(renderer, 10 + j*SCALE, 70 + i*SCALE, 10 + (j + 1)*SCALE, 70 + (i + 1) * SCALE, 0xFF999999);
                    //characterColor(renderer,10 + (j +0.5) * SCALE, 70 + (i + 0.5) * SCALE, 'ح', 0XFFFFFFFF);
                    break;
                case CELL_PINEAPPLE:
                    filledPolygonColor(renderer, vx,vy,6,0XFF77FFFF);
                    break;
                case CELL_CHERRY:
                    filledCircleColor(renderer,10 + (j + 0.3) *SCALE, 70 + (i + 0.8) * SCALE, 0.1 * SCALE, 0xFF0000FF);
                    filledCircleColor(renderer,10 + (j + 0.7) *SCALE, 70 + (i + 0.8) * SCALE, 0.1 * SCALE, 0xFF0000FF);
                    thickLineColor(renderer, 10 + (j + 0.7) * SCALE, 70 + (i + 0.7) * SCALE, 10 + (j + 0.5) * SCALE, 70 + (i + 0.2) * SCALE, 0.05 * SCALE, 0XFF055E8E);
                    thickLineColor(renderer, 10 + (j + 0.3) * SCALE, 70 + (i + 0.7) * SCALE, 10 + (j + 0.5) * SCALE, 70 + (i + 0.2) * SCALE, 0.05 * SCALE, 0XFF055E8E);
                    break;
                case CELL_CHEESE:
                    filledTrigonColor(renderer,10 + (j + 0.4) * SCALE, 70 + (i + 0.3) * SCALE, 10 + (j + 0.2) * SCALE, 70 + (i + 0.7) * SCALE, 10 + (j + 0.8) * SCALE, 70 + (i + 0.7) * SCALE, 0XFF00FFEE);
                    break;
            }
        }
    }
}


void DrawBots(Ghost *ghost, Pacman *pacman, SDL_Renderer *renderer , Map * map){
    static int dir = 1;
    static  double tt = 0;
    int i,j,color[4] = {0XFF0000FF,0XFFB791FF,0XFF0099FF,0XFFFFD907};
    for (i = 0; i < 4; ++i) {
        if (ghost[i].blue == 1) color[i] = 0XFFE22016;
    }
    tt += 0.077;
    if (pacman->dir != -1)  dir = pacman->dir;
    filledPieColor(renderer,10 + pacman->x * SCALE + SCALE/2, 70 + pacman->y * SCALE + SCALE / 2, SCALE/2,90 * dir + 180 + 45 * fabs(sin(tt)), 90 * dir + 180 - 45 * fabs(sin(tt)),0XFF00FFFF);
    filledPieColor(renderer,10 + (pacman->x - map->width) * SCALE + SCALE/2, 70 + pacman->y * SCALE + SCALE / 2, SCALE/2,90 * dir + 180 + 45 * fabs(sin(tt)), 90 * dir + 180 - 45 * fabs(sin(tt)),0XFF00FFFF);
    filledPieColor(renderer,10 + pacman->x * SCALE + SCALE/2, 70 + (pacman->y - map->height) * SCALE + SCALE / 2, SCALE/2,90 * dir + 180 + 45 * fabs(sin(tt)), 90 * dir + 180 - 45 * fabs(sin(tt)),0XFF00FFFF);
    for (i = 0; i < 4; ++i) {
        Sint16 vx[7] = {10 + (ghost[i].x + 0.15) * SCALE , 10 + (ghost[i].x + 0.15) * SCALE, 10 + (ghost[i].x + 0.25) * SCALE, 10 + (ghost[i].x + 0.5) * SCALE, 10 + (ghost[i].x + 0.75) * SCALE, 10 + (ghost[i].x + 0.85) * SCALE, 10 + (ghost[i].x + 0.85) * SCALE};
        Sint16 vy[7] = {70 + (ghost[i].y + 0.45) * SCALE, 70 + (ghost[i].y + 1) * SCALE, 70 + (ghost[i].y + 0.8) * SCALE, 70 + (ghost[i].y + 1) * SCALE, 70 + (ghost[i].y + 0.8) * SCALE, 70 + (ghost[i].y + 1) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE};
        filledPolygonColor(renderer, vx, vy, 7, color[i]);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.5) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE,0.35 * SCALE,color[i]);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.33) * SCALE, 70 + (ghost[i].y + 0.45 - (ghost[i].dir - 2) % 2 / 20.0) * SCALE,0.1 * SCALE,0XFFFFFFFF);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.66) * SCALE, 70 + (ghost[i].y + 0.45 - (ghost[i].dir - 2) % 2 / 20.0) * SCALE,0.1 * SCALE,0XFFFFFFFF);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.33 - (ghost[i].dir - 3) % 2 / 20.0 ) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE,0.05 * SCALE,0XFF000000);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.66 - (ghost[i].dir - 3) % 2 / 20.0 ) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE,0.05 * SCALE,0XFF000000);
        for (j = 0; j < 7; ++j) {
            vx[j] -= map->width * SCALE;
        }
        filledPolygonColor(renderer, vx, vy, 7, color[i]);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.5 - map->width) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE,0.35 * SCALE,color[i]);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.33 - map->width) * SCALE, 70 + (ghost[i].y + 0.45 - (ghost[i].dir - 2) % 2 / 20.0) * SCALE,0.1 * SCALE,0XFFFFFFFF);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.66 - map->width) * SCALE, 70 + (ghost[i].y + 0.45 - (ghost[i].dir - 2) % 2 / 20.0) * SCALE,0.1 * SCALE,0XFFFFFFFF);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.33 - map->width - (ghost[i].dir - 3) % 2 / 20.0 ) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE,0.05 * SCALE,0XFF000000);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.66 - map->width - (ghost[i].dir - 3) % 2 / 20.0 ) * SCALE, 70 + (ghost[i].y + 0.45) * SCALE,0.05 * SCALE,0XFF000000);
        for (j = 0; j < 7; ++j) {
            vx[j] += map->width * SCALE;
            vy[j] -= map->height * SCALE;
        }
        filledPolygonColor(renderer, vx, vy, 7, color[i]);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.5) * SCALE, 70 + (ghost[i].y + 0.45 - map->height) * SCALE,0.35 * SCALE,color[i]);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.33) * SCALE, 70 + (ghost[i].y + 0.45 - map->height - (ghost[i].dir - 2) % 2 / 20.0) * SCALE,0.1 * SCALE,0XFFFFFFFF);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.66) * SCALE, 70 + (ghost[i].y + 0.45 - map->height - (ghost[i].dir - 2) % 2 / 20.0) * SCALE,0.1 * SCALE,0XFFFFFFFF);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.33 - (ghost[i].dir - 3) % 2 / 20.0 ) * SCALE, 70 + (ghost[i].y + 0.45 - map->height) * SCALE,0.05 * SCALE,0XFF000000);
        filledCircleColor(renderer,10 + (ghost[i].x + 0.66 - (ghost[i].dir - 3) % 2 / 20.0 ) * SCALE, 70 + (ghost[i].y + 0.45 - map->height) * SCALE,0.05 * SCALE,0XFF000000);

    }
}

void DrawExtras(SDL_Renderer * renderer, Map *map,Game *game, Pacman *pacman, int time){
    char times[30], scores[30];
    int i;
    sprintf(times,"TIME: %d",time);
    sprintf(scores,"SCORE: %d",game->score);
    boxColor(renderer,0,0,100 + map->width * SCALE, 70, 0XFF000000);
    boxColor(renderer,0,0,10,100 + map->height * SCALE, 0XFF000000);
    boxColor(renderer,0,70 + map->height * SCALE,20 + map->width * SCALE,100 + map->height * SCALE, 0XFF000000);
    boxColor(renderer,10 + map->width * SCALE, 0, 20 + map->width * SCALE, 100 + map->height * SCALE, 0XFF000000);
    SDL_RenderSetScale(renderer,2.0,2.0);
    stringColor(renderer,10,5,times,0XFFFFFFFF);
    stringColor(renderer,map->width * SCALE / 2 - 80, 5,scores,0XFFFFFFFF);
    stringColor(renderer,map->width * SCALE / 4 - 140,37 + map->height * SCALE/2, "P: PAUSE      Q: QUIT     ARROWS: MOVE",0XFFFFFFFF);
    SDL_RenderSetScale(renderer,1,1);
    for (i = 0; i < pacman->health; ++i) {
        filledPieColor(renderer,35 + i * 40 , 50, 17, 45, -45, 0XFF00FFFF);
    }
}

void pause(SDL_Renderer *renderer, int *quit, Map * map){
    int resume = 0;
    SDL_Event e;
    while (!resume){
        if (SDL_PollEvent(&e)){
            if (e.type ==  SDL_QUIT){
                *quit = 1;
                resume = 1;
            }
            else if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_p:
                        resume = 1;
                        break;
                    case SDLK_q:
                        *quit = 1;
                        resume = 1;
                        break;
                    default:
                        continue;
                }
            } else continue;
            SDL_FlushEvent(SDL_KEYDOWN);
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,0XFF);
        SDL_RenderSetScale(renderer,4,4);
        SDL_RenderClear(renderer);
        stringColor(renderer,map->width * SCALE / 8 - 15,map->height * SCALE / 8 - 20, "PAUSE", 0XFFFFFFFF);
        SDL_RenderSetScale(renderer,2,2);
        stringColor(renderer,map->width * SCALE /4 - 60,50 + map->height * SCALE/4, "PRESS P TO RESUME",0XFFFFFFFF);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    SDL_RenderSetScale(renderer,1,1);
}

int menu(SDL_Renderer *renderer, Map *map, Pacman *pacman, Game *game){
    SDL_Event e;
    SDL_RenderSetScale(renderer, 4, 4);
    while (1) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return 1;
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.x > map->width * SCALE/2 - 100 && e.button.x < map->width * SCALE/2 + 120 && e.button.y > 160 && e.button.y < 240)    return 0;
                else if (e.button.x > map->width * SCALE/2 - 100 && e.button.x < map->width * SCALE/2 + 120 && e.button.y > 320 && e.button.y < 400) return 1;
            } else continue;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);
        static double tt =0;
        tt +=0.77;
        filledPieColor(renderer, map->width * SCALE/8 - 50, 50, SCALE/2, 45 * fabs(sin(tt)), - 45 * fabs(sin(tt)),0XFF00FFFF);
        if (game->cheeses == 0 && game->pineapples == 0) stringColor(renderer, map->width *SCALE/8 - 20, 10, "WON", 0XFF00FFFF);
        else if (pacman->health == 0) stringColor(renderer, map->width *SCALE/8 - 10, 10, "LOST", 0XFF0000FF);
        else stringColor(renderer, map->width *SCALE/8 - 20, 10, "PACMAN", 0XFF00FFFF);
        if (isGameFinished(game,pacman)) {
            char scores[30];
            sprintf(scores,"SCORE:%d",game->score);
            stringColor(renderer, map->width *SCALE/8 - 25, 22, scores, 0XFF00FFFF);
        }
        boxColor(renderer,map->width *SCALE/8 - 25,40,map->width * SCALE/8 + 30, 60,0XFF00FF00);
        rectangleColor(renderer,map->width *SCALE/8 - 25,40,map->width * SCALE/8 + 31, 61,0XFFFFFFFF);
        stringColor(renderer,map->width * SCALE/8 - 12, 45, "PLAY", 0XFFFFFFFF);
        boxColor(renderer,map->width *SCALE/8 - 25,80,map->width * SCALE/8 + 30, 100,0XFF0000FF);
        rectangleColor(renderer,map->width *SCALE/8 - 25,80,map->width * SCALE/8 + 31, 101,0XFFFFFFFF);
        stringColor(renderer,map->width * SCALE/8 - 12, 85, "QUIT", 0XFFFFFFFF);
        stringColor(renderer, map->width *SCALE/8 - 80, 140, "DEVELOPED BY: REZA.YB", 0XFF00FFFF);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
}