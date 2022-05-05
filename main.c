//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "routeFinding.h"
#include "visualization.h"

void runningTime(int x){
    double Total_time;
    if(x == 1) {
        clock_t start, end;
        start = clock();
        for(int i = 1; i<= 100 ;++i){
            for(int j = 1200; j<=1400; ++j){
                dij(10);
            }
        }
        end = clock();
        Total_time = (double)(end - start) / CLOCKS_PER_SEC; //单位换算成秒
        printf("%f seconds\n", Total_time);
    }
    else if(x == 2){
        clock_t start, end;
        start = clock();
        for(int i = 1; i<= 100 ;++i){
            for(int j = 1200; j<=1400; ++j){
                bellman(10);
            }
        }
        end = clock();
        Total_time = (double)(end - start) / CLOCKS_PER_SEC; //单位换算成秒
        printf("%f seconds\n", Total_time);
    }
}

int main() {
    dijInit("Final_Map.map");
    readNode("Final_Map.map");
    readLink("Final_Map.map");

    // displayMap();
    bellman(1090);

    int endPoint = findNodeByName(-8849);
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