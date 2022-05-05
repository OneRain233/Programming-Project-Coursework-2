//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <SDL.h>
#include "routeFinding.h"
#include "visualization.h"

int main() {
    dijInit("Final_Map.map");
    readNode("Final_Map.map");
    readLink("Final_Map.map");
    // displayMap();
    dij(1);
    printf("start:%d end: %d\n", findNodeByIndex(10), findNodeByIndex(888));
    printf("%Lf\n", getLen(findNodeByName(985084880)));
    showPath(findNodeByName(985084880));
    int endPoint = findNodeByName(985084880);
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
//    long double *info = getInfo();

//    return 0;
    long double maxLat = -1e6;
    long double maxLon = -1e6;
    long double minLat = 1e6;
    long double minLon = 1e6;
    Node *nodes = getNodes();
    int *path = getPath();
    for (int i = 0; i < getNodeCnt(); i++) {
        if (nodes[i].lat > maxLat) {
            maxLat = nodes[i].lat;
        }
        if (nodes[i].lat < minLat) {
            minLat = nodes[i].lat;
        }
        if (nodes[i].lon > maxLon) {
            maxLon = nodes[i].lon;
        }
        if (nodes[i].lon < minLon) {
            minLon = nodes[i].lon;
        }
    }
    printf("%Lf\n", maxLat);
    printf("%Lf\n", maxLon);
    printf("%Lf\n", minLat);
    printf("%Lf\n", minLon);
//    return 0;
    visualize(window, renderer, nodes, path, getNodeCnt(), minLat, minLon, endPoint);


    return 0;
}