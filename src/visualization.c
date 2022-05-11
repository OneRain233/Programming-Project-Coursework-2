//
// Created by onerain233 on 4/24/22.
//

#include "../include/visualization.h"
#include "../include/routeFinding.h"
#include "SDL2/SDL.h"


#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

void calcPosition(long double x, long double y, long double *x_pos, long double *y_pos, long double baseX,
                  long double baseY, long double offsetX, long double offsetY, long double scale) {
    long double x_pos_temp = x - baseX;
    long double y_pos_temp = y - baseY;
    *x_pos = x_pos_temp * 1e6 / scale + offsetX;
    *y_pos = y_pos_temp * 1e6 / scale + offsetY;
}

void draw(SDL_Window *window, SDL_Renderer *renderer,
          Node *nodes, const int *path, int node_cnt, long double baseX,
          long double baseY, int endPoint, long double offsetX, long double offsetY, long double scale,
          long double pointSize) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderClear(renderer); // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black

    for (int i = 0; i < node_cnt; i++) {
        long double *x_pos = malloc(sizeof(long double));
        long double *y_pos = malloc(sizeof(long double));
        calcPosition(nodes[i].lat, nodes[i].lon, x_pos, y_pos, baseX, baseY, offsetX, offsetY, scale);
        int x = (int) *x_pos;
        int y = (int) *y_pos;
        SDL_Rect rect = {y, x, (int) pointSize, (int) pointSize};
        SDL_RenderFillRect(renderer, &rect);

        free(x_pos);
        free(y_pos);

        // edge
        Edge *cur = nodes[i].head;
        while (cur != NULL) {
            long double x_pos_next;
            long double y_pos_next;
            calcPosition(nodes[cur->to].lat, nodes[cur->to].lon, &x_pos_next, &y_pos_next, baseX, baseY, offsetX,
                         offsetY, scale);
            int x_next = (int) x_pos_next;
            int y_next = (int) y_pos_next;
            SDL_RenderDrawLine(renderer, y + (int) (pointSize) / 2, x + (int) (pointSize) / 2,
                               y_next + (int) (pointSize) / 2, x_next + (int) (pointSize) / 2);
            cur = cur->next;
        }
    }

    int cur = endPoint;
    int prev = cur;
    while (cur != -1) {
        long double cur_x;
        long double cur_y;
        calcPosition(nodes[cur].lat, nodes[cur].lon, &cur_x, &cur_y, baseX, baseY, offsetX, offsetY, scale);
        int x_cur = (int) cur_x;
        int y_cur = (int) cur_y;
        long double prev_x;
        long double prev_y;
        calcPosition(nodes[prev].lat, nodes[prev].lon, &prev_x, &prev_y, baseX, baseY, offsetX, offsetY, scale);
        int x_prev = (int) prev_x;
        int y_prev = (int) prev_y;
        // red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderDrawLine(renderer, y_cur + (int) (pointSize) / 2, x_cur + (int) (pointSize) / 2,
                           y_prev + (int) (pointSize) / 2,
                           x_prev + (int) (pointSize) / 2);
        prev = cur;
        cur = path[cur];
    }
}

void update(SDL_Window *window, SDL_Renderer *renderer,
            Node *nodes, int *path, int node_cnt, long double baseX,
            long double baseY, int endPoint, long double offsetX, long double offsetY, long double scale,
            long double pointSize) {
    draw(window, renderer, nodes, path, node_cnt, baseX, baseY, endPoint, offsetX, offsetY, scale, pointSize);

    SDL_RenderPresent(renderer);
}

int findPoint(int x, int y, Node *nodes, int node_cnt, long double baseX, long double baseY, long double offsetX,
              long double offsetY, long double scale) {
    long double x_original = (x * scale - offsetX) / 1e6 + baseX;
    long double y_original = (y * scale - offsetY) / 1e6 + baseY;
    printf("%Lf, %Lf\n", x_original, y_original);
    for (int i = 0; i < node_cnt; i++) {
        // range 0.0010 ~ 0.0020
        if (fabsl(nodes[i].lat - x_original) < 0.01 && fabsl(nodes[i].lon - y_original) < 0.01) {
            return i;
        }

    }
    return -1;
}

void
highlight(SDL_Window *window, SDL_Renderer *renderer, int NodeIndex, Node *nodes, long double baseX, long double baseY,
          long double offsetX, long double offsetY, long double scale, long double pointSize) {
    long double x_pos = nodes[NodeIndex].lat;
    long double y_pos = nodes[NodeIndex].lon;
    long double *x_pos_temp = malloc(sizeof(long double));
    long double *y_pos_temp = malloc(sizeof(long double));
    calcPosition(x_pos, y_pos, x_pos_temp, y_pos_temp, baseX, baseY, offsetX, offsetY, scale);
    int x = (int) *x_pos_temp;
    int y = (int) *y_pos_temp;
    SDL_Rect rect = {y, x, (int) pointSize + 10, (int) pointSize};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    free(x_pos_temp);
    free(y_pos_temp);

}

int visualize(SDL_Window *window, SDL_Renderer *renderer,
              Node *nodes, int *path, int node_cnt, long double baseX,
              long double baseY, int endPoint) {
    int quit = 0;
    long double offsetX = -200;
    long double offsetY = -200;
    long double scale = 10;
    long double pointSize = 3;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    drawACharacter(window, renderer, 100, 100, "Hello World");
    update(window, renderer, nodes, path, node_cnt, baseX, baseY, endPoint, offsetX, offsetY, scale, pointSize);
    int nowInput = 0;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }

            if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y > 0) {
                    scale -= 0.3;
                    pointSize += 0.2;
                } else if (event.wheel.y < 0) {
                    scale += 0.3;
                    pointSize -= 0.2;

                }
                update(window, renderer, nodes, path, node_cnt, baseX, baseY, endPoint, offsetX, offsetY, scale,
                       pointSize);
            }


            if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_PRESSED) {
                offsetY += event.motion.xrel;
                offsetX += event.motion.yrel;
                update(window, renderer, nodes, path, node_cnt, baseX, baseY, endPoint, offsetX, offsetY, scale,
                       pointSize);

            }


            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    offsetY += 100;
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    offsetY -= 100;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    offsetX += 100;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    offsetX -= 100;
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
                if (event.key.keysym.sym == SDLK_F1) {
                    scale += 1;
                }
                if (event.key.keysym.sym == SDLK_F2) {
                    scale -= 1;
                }
                update(window, renderer, nodes, path, node_cnt, baseX, baseY, endPoint, offsetX, offsetY, scale,
                       pointSize);
            }
        }

    }
}