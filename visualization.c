//
// Created by onerain233 on 4/24/22.
//

#include "visualization.h"
#include "routeFinding.h"
#include "SDL2/SDL.h"



int visualize(SDL_Window *window, SDL_Renderer *renderer, Node *nodes, int node_cnt) {


    int quit = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1920, 1080, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderClear(renderer); // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
//    SDL_Rect rect = {0, 0, 192, 108};
//    SDL_RenderFillRect(renderer, &rect);
//    SDL_RenderPresent(renderer);


    for (int i = 0; i < node_cnt; i++) {
        printf("%d: %Lf, %Lf\n", i, nodes[i].lat, nodes[i].lon);
        long double x = 1;
        long double y = nodes[i].lon * (1080 / 180);
        if(x < 0) x = -x;
        if(y < 0) y = -y;


        int x_pos = (int) x;
        int y_pos = (int) y;
        printf("%d: %d, %d\n", i, x_pos, y_pos);
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_Rect rect = {x_pos, y_pos, 10, 10};
        SDL_RenderFillRect(renderer, &rect);

    }

    SDL_RenderPresent(renderer);

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }


        SDL_Delay(1);
    }


}
