#include <stdio.h>
#include <game.h>
#include "SDL2_gfxPrimitives.h"
#include "map.h"
#include "physics.h"
#include "game.h"
#include "graphics.h"

int main(int argc, char* argv[]) {
    Map map;
    Game game;
    Pacman pacman;
    Ghost ghost[4];
    initiateGame("res/map.txt", &map, &game, &pacman, ghost);
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, map.width * MAP_MAX_SIZE + 20, map.height * MAP_MAX_SIZE + 100, SDL_WINDOW_OPENGL);
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
    int quit = 0, i;
    while (!quit)
    {
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
                    default:
                        continue;
                }
                pacman.dir = decidePacman( &map, &pacman, action);
            } else continue;
            SDL_FlushEvent(SDL_KEYDOWN);
        }
        checkEatables(&map, &game, &pacman, ghost);
        for (i = 0; i < 4; ++i) {
            checkGhostState(ghost + i);
            ghost[i].dir = decideGhost(&map, ghost + i, &pacman, ghost);
            checkGhostCollision(&pacman, ghost +i);
        }
        InitiateGraphics(pacman,game,5,renderer);
        DrawMap(&map,renderer);
        DrawBots(ghost,&pacman,renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(6000 / CYCLES_PER_SEC);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
