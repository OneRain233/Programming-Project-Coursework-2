//
// Created by onerain233 on 4/24/22.
//

#include "visualization.h"
#include "routeFinding.h"
#include "SDL2/SDL.h"

void calcPosition(long double x, long double y, long double *x_pos, long double *y_pos, long double baseX,
                  long double baseY) {
    long double x_pos_temp = x - baseX;
    long double y_pos_temp = y - baseY;
    *x_pos = x_pos_temp * 1e6 / 10;
    *y_pos = y_pos_temp * 1e6 / 10;
}

int visualize(SDL_Window *window, SDL_Renderer *renderer,
              Node *nodes, int *path, int node_cnt, long double baseX,
              long double baseY, int endPoint) {
    int quit = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              2560, 1080, SDL_WINDOW_SHOWN);
//    SDL_SetWindowResizable(window, 1)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderClear(renderer); // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
//    SDL_Rect rect1 = {0, 0, 192, 108};
//    SDL_RenderFillRect(renderer, &rect1);
//    SDL_RenderPresent(renderer);


    for (int i = 0; i < node_cnt; i++) {
//        printf("%d: %Lf, %Lf\n", i, nodes[i].lat, nodes[i].lon);
        long double *x_pos = malloc(sizeof(long double));
        long double *y_pos = malloc(sizeof(long double));
        calcPosition(nodes[i].lat, nodes[i].lon, x_pos, y_pos, baseX, baseY);

        printf("%Lf, %Lf\n", *x_pos, *y_pos);
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
//        SDL_RenderDrawPoint(renderer, *x_pos, *y_pos);
        int x = (int) *x_pos;
        int y = (int) *y_pos;
        SDL_Rect rect = {y, x, 5, 5};
        SDL_RenderFillRect(renderer, &rect);

        free(x_pos);
        free(y_pos);

        // edge
        Edge *cur = nodes[i].head;
        while (cur != NULL) {
            long double x_pos_next;
            long double y_pos_next;
            calcPosition(nodes[cur->to].lat, nodes[cur->to].lon, &x_pos_next, &y_pos_next, baseX, baseY);
            int x_next = (int) x_pos_next;
            int y_next = (int) y_pos_next;
            SDL_RenderDrawLine(renderer, y, x, y_next, x_next);

            cur = cur->next;
        }

    }


    printf("%Lf, %Lf\n", baseX, baseY);
    int cur = endPoint;
    int prev = cur;
    while(cur != -1) {
        long double cur_x;
        long double cur_y;
        calcPosition(nodes[cur].lat, nodes[cur].lon, &cur_x, &cur_y, baseX, baseY);
        int x_cur = (int) cur_x;
        int y_cur = (int) cur_y;
        long double prev_x;
        long double prev_y;
        calcPosition(nodes[prev].lat, nodes[prev].lon, &prev_x, &prev_y, baseX, baseY);
        int x_prev = (int) prev_x;
        int y_prev = (int) prev_y;
        // red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderDrawLine(renderer, y_cur, x_cur, y_prev, x_prev);
        printf("%d, %d -> %d, %d\n", x_cur, y_cur, x_prev, y_prev);

        prev = cur;
        cur = path[cur];
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
