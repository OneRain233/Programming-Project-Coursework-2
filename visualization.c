//
// Created by onerain233 on 4/24/22.
//

#include "visualization.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void init(){
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

    atexit(SDL_Quit); // set for clean-up on exit
    SDL_Renderer* renderer = NULL;
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    SDL_SetWindowTitle( window, "SDL2 Window" );
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

