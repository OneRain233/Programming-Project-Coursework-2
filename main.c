//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <SDL.h>
#include "routeFinding.h"
#include "visualization.h"

int main(){
    dijInit("Final_Map.map");
    readNode("Final_Map.map");
    readLink("Final_Map.map");
    // displayMap();
    dij(10);
    printf("start:%d end: %d\n", findNodeByIndex(10), findNodeByIndex(888));
    printf("%Lf\n", getLen(findNodeByName(985084880)));
    showPath(findNodeByName(985084880));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    visualize(window, renderer, getNodes(), getNodeCnt());

    
    return 0;
}