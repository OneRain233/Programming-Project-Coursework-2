//
// Created by onerain233 on 4/24/22.
//

#ifndef CWK2_VISUALIZATION_H
#define CWK2_VISUALIZATION_H

#include <SDL_render.h>
#include "routeFinding.h"

void draw_graph(Node *nodes, SDL_Renderer *renderer, int node_cnt);

int visualize(SDL_Window *window, SDL_Renderer *renderer, Node *nodes, int *path, int node_cnt, long double baseX,
              long double baseY, int endPoint);

#endif //CWK2_VISUALIZATION_H
