//
// Created by onerain233 on 4/24/22.
//

#include "visualization.h"
#include "routeFinding.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void visual_init(SDL_Renderer* renderer){
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

    atexit(SDL_Quit); // set for clean-up on exit
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    SDL_SetWindowTitle( window, "SDL2 Window" );
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void render_nodes(SDL_Renderer* renderer, const Node* nodes, int size){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(int i = 0; i < size; i++){
        printf("%d\n", nodes[i].id);
        SDL_RenderDrawPoint(renderer, nodes[i].lat % 800, nodes[i].lon / 800);
    }
    SDL_RenderPresent(renderer);
}