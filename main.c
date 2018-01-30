#include <stdio.h>
#include <game.h>
#include <map.h>
#include <time.h>
#include "SDL2_gfxPrimitives.h"
#include "map.h"
#include "physics.h"
#include "game.h"
#include "graphics.h"

int main(int argc, char* argv[]) {
    int start =time(NULL) , now;
    Map map;
    Game game;
    Pacman pacman;
    Ghost ghost[4];
    initiateGame("res/reality.txt", &map, &game, &pacman, ghost);
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, map.width * SCALE + 20, map.height * SCALE + 100, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    Action action = ACTION_IDLE;
    SDL_Event e;
    int quit = menu(renderer,&map,&pacman,&game), i;
    while (!quit)
    {
        if (isGameFinished(&game,&pacman)) {
            quit = menu(renderer,&map,&pacman,&game);
            game.cherries= 0;
            game.cheeses = 0;
            game.pineapples = 0;
            initiateGame("res/reality.txt", &map, &game, &pacman, ghost);
        }
        now = time(NULL) - start;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
            else if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        action = ACTION_UP;
                        break;
                    case SDLK_DOWN:
                        action = ACTION_DOWN;
                        break;
                    case SDLK_LEFT:
                        action = ACTION_LEFT;
                        break;
                    case SDLK_RIGHT:
                        action = ACTION_RIGHT;
                        break;
                    case SDLK_q:
                        quit = 1;
                        break;
                    case SDLK_p:
                        pause(renderer, &quit, &map);
                        continue;
                    default:
                        continue;
                }
            } else continue;
            SDL_FlushEvent(SDL_KEYDOWN);
        }
        if ( round(pacman.x) == pacman.x &&  round(pacman.y) == pacman.y)   pacman.dir = decidePacman(&map, &pacman, action);
        pacman.x = Standardize((int)round((SCALE * pacman.x - (pacman.speed * (pacman.dir != -1) * ((pacman.dir - 3) % 2)))),SCALE * map.width) / (double) SCALE;
        pacman.y = Standardize((int)round((SCALE * pacman.y + (pacman.speed * (pacman.dir != -1) * ((pacman.dir - 2) % 2)))),SCALE * map.height) / (double) SCALE;
        checkEatables(&map, &game, &pacman, ghost);
        for (i = 0; i < 4; ++i) {
            checkGhostState(ghost + i);
            if ( round(ghost[i].x) == ghost[i].x && round(ghost[i].y) == ghost[i].y)  ghost[i].dir = decideGhost(&map, ghost + i, &pacman, ghost);
            ghost[i].x = Standardize((int)round((SCALE * ghost[i].x - (ghost[i].speed * (ghost[i].dir != -1) * ((ghost[i].dir - 3) % 2)))),SCALE * map.width) / (double) SCALE;
            ghost[i].y = Standardize((int)round((SCALE * ghost[i].y + (ghost[i].speed * (ghost[i].dir != -1) * ((ghost[i].dir - 2) % 2)))),SCALE * map.height) / (double) SCALE;
            checkGhostCollision(&pacman, ghost +i);
        }
        InitiateGraphics(pacman,game,5,renderer);
        DrawMap(&map,renderer);
        DrawBots(ghost,&pacman,renderer, &map);
        DrawExtras(renderer,&map,&game,&pacman,now);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / CYCLES_PER_SEC);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
