//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include "main.h"
#include "dij.h"
#include "visualization.h"

int main(){
    dij_init();
    readNode("Final_Map.map");
    readLink("Final_Map.map");
    // displayMap();
    dij(10);
    printf("start:%d end: %d\n", findNodeByIndex(10), findNodeByIndex(888));
    printf("%f\n", getLen(888));
    showPath(888);
    return 0;
}