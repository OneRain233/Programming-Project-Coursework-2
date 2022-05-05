//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "routeFinding.h"
#include "visualization.h"
//
//void runningTime(int x){
//    double Total_time;
//    if(x == 1) {
//        clock_t start, end;
//        start = clock();
//        for(int i = 1; i<= 100 ;++i){
//            for(int j = 1200; j<=1400; ++j){
//                dij(i);
//            }
//        }
//        end = clock();
//        Total_time = (double)(end - start) / CLOCKS_PER_SEC; //单位换算成秒
//        printf("%f seconds\n", Total_time);
//    }
//    else if(x == 2){
//        clock_t start, end;
//        start = clock();
//        for(int i = 1; i<= 100 ;++i){
//            for(int j = 1200; j<=1400; ++j){
//                bellman(i);
//            }
//        }
//        end = clock();
//        Total_time = (double)(end - start) / CLOCKS_PER_SEC; //单位换算成秒
//        printf("%f seconds\n", Total_time);
//    }
//}

int main() {
    dijInit("Final_Map.map");
    readNode("Final_Map.map");
    readLink("Final_Map.map");
//    bellman(1090);
    char *buffer = (char *) malloc(sizeof(char) * 100);
    int endPoint = 0;
    int startPoint = 0;
    // get start point
    fprintf(stdout, "Please input start point: ");
    fgets(buffer, 100, stdin);
    startPoint = atoi(buffer);
    startPoint = findNodeByName(startPoint);
    // get end point
    fprintf(stdout, "Please input end point: ");
    fgets(buffer, 100, stdin);
    endPoint = atoi(buffer);
    endPoint = findNodeByName(endPoint);

    dij(startPoint);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
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
    visualize(window, renderer, nodes, path, getNodeCnt(), minLat, minLon, endPoint);


    return 0;
}