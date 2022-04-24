//
// Created by onerain233 on 4/24/22.
//

#ifndef CWK2_VISUALIZATION_H
#define CWK2_VISUALIZATION_H

#include <SDL_render.h>
#include "routeFinding.h"

void visual_init(SDL_Renderer* renderer);

void render_nodes(SDL_Renderer *renderer, const Node *nodes, int size);

#endif //CWK2_VISUALIZATION_H
