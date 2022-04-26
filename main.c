//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <SDL_timer.h>
#include "main.h"
#include "routeFinding.h"
#include "visualization.h"

int main(){
    dij_init("Final_Map.map");
    readNode("Final_Map.map");
    readLink("Final_Map.map");
    // displayMap();
    dij(10);
    printf("start:%d end: %d\n", findNodeByIndex(10), findNodeByIndex(888));
    printf("%f\n", getLen(888));
    showPath(888);
    const Node *n = getNodes();
//
//    SDL_Renderer *renderer = NULL;
//    while(1) {
//        visual_init(renderer);
//        render_nodes(renderer, n, 5000);
//
//        SDL_RenderPresent(renderer);
//        SDL_Delay(1000);
//    }

    return 0;
}