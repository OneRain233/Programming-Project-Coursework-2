//
// Created by onerain233 on 4/24/22.
//

#include "../include/visualization.h"
#include "../include/routeFinding.h"
#include "SDL2/SDL.h"


#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

int begin;
int end;
int *route;

/* void calcPosition(long double x, long double y, long double *x_pos, long double *y_pos, long double baseX,
 *                  long double baseY, long double offsetX, long double offsetY, long double scale)
 *
 * ---------------------------------------------------------------------------------------------------------------------
 * This function calculates the position of the point on the screen based on the base position, the offset, and the
 * scale.
 *
 * x: The x coordinate of the point
 * y: The y coordinate of the point
 * x_pos: The x position of the point on the screen
 * y_pos: The y position of the point on the screen
 * baseX: The x coordinate of the base point
 * baseY: The y coordinate of the base point
 * offsetX: The x offset of the base point
 * offsetY: The y offset of the base point
 * scale: The scale of the base point
 *
 * return: void
*/
void calcPosition(long double x, long double y, long double *x_pos, long double *y_pos, long double baseX,
                  long double baseY, long double offsetX, long double offsetY, long double scale) {
    long double x_pos_temp = x - baseX;
    long double y_pos_temp = y - baseY;
    *x_pos = x_pos_temp * 1e6 / scale + offsetX;
    *y_pos = y_pos_temp * 1e6 / scale + offsetY;
}

/* void draw(SDL_Renderer *renderer, Node *nodes, const int *path, int node_cnt, long double baseX, long double baseY,
 *          int endPoint, long double offsetX, long double offsetY, long double scale, long double pointSize)
 * ---------------------------------------------------------------------------------------------------------------------
 * This function draws the nodes and the path on the screen.
 *
 * renderer: The renderer of the screen
 * nodes: The array of nodes
 * path: The array of path
 * node_cnt: The number of nodes
 * baseX: The x coordinate of the base point
 * baseY: The y coordinate of the base point
 * endPoint: The index of the end point
 * offsetX: The x offset of the base point
 * offsetY: The y offset of the base point
 * scale: The scale of the base point
 * pointSize: The size of the point
 *
 * return: void
 * */
void draw(SDL_Renderer *renderer, Node *nodes, const int *path, int node_cnt, long double baseX, long double baseY,
          int endPoint, long double offsetX, long double offsetY, long double scale, long double pointSize) {
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

    int cur = end;
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


/* void update(SDL_Window *window, SDL_Renderer *renderer,
 *           Node *nodes, int *path, int node_cnt, long double baseX,
 *           long double baseY, int endPoint, long double offsetX, long double offsetY, long double scale,
 *           long double pointSize)
 * ---------------------------------------------------------------------------------------------------------------------
 * Description:
 * This function updates the screen with the new path
 *
 * window: The window to draw on
 * renderer: The renderer to draw on
 * nodes: The nodes to draw
 * path: The path to draw
 * node_cnt: The number of nodes
 * baseX: The base x coordinate
 * baseY: The base y coordinate
 * endPoint: The end point
 * offsetX: The offset x coordinate
 * offsetY: The offset y coordinate
 * scale: The scale of the map
 * pointSize: The size of the points
 *
 * return: void
 */
void update(SDL_Window *window, SDL_Renderer *renderer,
            Node *nodes, int *path, int node_cnt, long double baseX,
            long double baseY, int endPoint, long double offsetX, long double offsetY, long double scale,
            long double pointSize) {
    draw(renderer, nodes, route, node_cnt, baseX, baseY, end, offsetX, offsetY, scale, pointSize);

    SDL_RenderPresent(renderer);
}

/* int findPoint(int x, int y, Node *nodes, int node_cnt, long double baseX, long double baseY, long double offsetX,
 *             long double offsetY, long double scale, long double pointSize)
 * ---------------------------------------------------------------------------------------------------------------------
 * Description:
 * This function finds the point that is clicked on
 *
 * x: The x coordinate of the click
 * y: The y coordinate of the click
 * nodes: The nodes to draw
 * node_cnt: The number of nodes
 * baseX: The base x coordinate
 * baseY: The base y coordinate
 * offsetX: The offset x coordinate
 * offsetY: The offset y coordinate
 * scale: The scale of the map
 * pointSize: The size of the points
 *
 * return: The point that is clicked on
 */
int findPoint(int x, int y, Node *nodes, int node_cnt, long double baseX, long double baseY, long double offsetX,
              long double offsetY, long double scale, long double pointSize) {
    for (int i = 0; i < node_cnt; i++) {
        long double *x_pos = malloc(sizeof(long double));
        long double *y_pos = malloc(sizeof(long double));
        calcPosition(nodes[i].lat, nodes[i].lon, x_pos, y_pos, baseX, baseY, offsetX, offsetY, scale);
        int x_cur = (int) *x_pos;
        int y_cur = (int) *y_pos;
        free(x_pos);
        free(y_pos);
        if (abs(x_cur - y) <= (int) (pointSize) && abs(x - y_cur) <= (int) (pointSize) / 2) {
            return i;
        }
    }
}

/* void highlight(SDL_Window *window, SDL_Renderer *renderer, int NodeIndex, Node *nodes, long double baseX, long double baseY,
 long double offsetX, long double offsetY, long double scale, long double pointSize)
 * ---------------------------------------------------------------------------------------------------------------------
 * Description:
 * This function highlights the point that is clicked on
 *
 * window: The window to draw on
 * renderer: The renderer to draw on
 * NodeIndex: The index of the point that is clicked on
 * nodes: The nodes to draw
 * baseX: The base x coordinate
 * baseY: The base y coordinate
 * offsetX: The offset x coordinate
 * offsetY: The offset y coordinate
 * scale: The scale of the map
 * pointSize: The size of the points
 *
 * return: void
 */
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
    SDL_Rect rect = {y, x, (int) pointSize + 10, (int) pointSize + 10};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    free(x_pos_temp);
    free(y_pos_temp);

}

/* int visualize(SDL_Window *window, SDL_Renderer *renderer,
              Node *nodes, int *path, int node_cnt, long double baseX,
              long double baseY, int endPoint)
 * ---------------------------------------------------------------------------------------------------------------------
 * Description:
 * This function visualizes the path
 *
 * window: The window to draw on
 * renderer: The renderer to draw on
 * nodes: The nodes to draw
 * path: The path to draw
 * node_cnt: The number of nodes
 * baseX: The base x coordinate
 * baseY: The base y coordinate
 * endPoint: The end point of the path
 *
 * return: 1 if the user wants to quit, 0 otherwise
 */
int visualize(SDL_Window *window, SDL_Renderer *renderer,
              Node *nodes, int *path, int node_cnt, long double baseX,
              long double baseY, int endPoint) {
    int quit = 0;
    long double offsetX = -200;
    long double offsetY = -200;
    long double scale = 10;
    long double pointSize = 5;
    end = endPoint;
    route = path;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    drawACharacter(window, renderer, 100, 100, "Hello World");
    update(window, renderer, nodes, route, node_cnt, baseX, baseY, end, offsetX, offsetY, scale, pointSize);
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
                update(window, renderer, nodes, route, node_cnt, baseX, baseY, end, offsetX, offsetY, scale,
                       pointSize);
            }


            if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_PRESSED) {
                offsetY += event.motion.xrel;
                offsetX += event.motion.yrel;
                update(window, renderer, nodes, route, node_cnt, baseX, baseY, end, offsetX, offsetY, scale,
                       pointSize);

            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int index = findPoint(event.button.x, event.button.y, nodes, node_cnt, baseX, baseY, offsetX, offsetY,
                                      scale, pointSize);
                if (index != -1) {
                    highlight(window, renderer, index, nodes, baseX, baseY, offsetX, offsetY, scale, pointSize);
                    begin = index;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
                int index = findPoint(event.button.x, event.button.y, nodes, node_cnt, baseX, baseY, offsetX, offsetY,
                                      scale, pointSize);
                if (index != -1) {
                    highlight(window, renderer, index, nodes, baseX, baseY, offsetX, offsetY, scale, pointSize);
                    end = index;

                    updatePath(begin);
                    route = getPath();
                    update(window, renderer, nodes, route, node_cnt, baseX, baseY, end, offsetX, offsetY, scale,
                           pointSize);


                }
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
                update(window, renderer, nodes, route, node_cnt, baseX, baseY, end, offsetX, offsetY, scale,
                       pointSize);
            }
        }

    }
}
