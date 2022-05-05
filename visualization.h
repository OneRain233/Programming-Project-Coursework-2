//
// Created by onerain233 on 4/24/22.
//

#ifndef CWK2_VISUALIZATION_H
#define CWK2_VISUALIZATION_H

#include <SDL_render.h>
#include "routeFinding.h"

void draw_graph(Node *nodes, SDL_Renderer *renderer, int node_cnt);

int visualize(SDL_Window *window, SDL_Renderer *renderer, Node *nodes, int node_cnt);

#endif //CWK2_VISUALIZATION_H
