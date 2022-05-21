//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <time.h>
#include "../include/routeFinding.h"
#include "../include/visualization.h"
#include <ui.h>

int startPoint = -1;
int endPoint = -1;
int algo = 0;
uiEntry *e1;
uiEntry *e2;
uiLabel *len;
uiLabel *info;
char *fileName;
long double length;


void run(char *filename, int flag) {
    printf("startPoint: %d\n", startPoint);
    printf("endPoint: %d\n", endPoint);
    long double *dist;
    if (algo == 0) {
        printf("algo: Dijkstra\n");
        dist = dijkstra(startPoint);
    } else if (algo == 1) {
        printf("algo: bellman\n");
        dist = bellman(startPoint);
    }
    printf("test");
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    long double maxLat = -1e6;
    long double maxLon = -1e6;
    long double minLat = 1e6;
    long double minLon = 1e6;
    Node *nodes = getNodes();
    int *path = getPath();
    length = dist[endPoint];
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
    if (flag) {
        visualize(window, renderer, nodes, path, getNodeCnt(), minLat, minLon, endPoint);
    }

}

void on_submit(uiButton *b, void *data) {

    startPoint = atoi(uiEntryText(e1));
    endPoint = atoi(uiEntryText(e2));

    startPoint = findNodeByName(startPoint);
    endPoint = findNodeByName(endPoint);

    if (startPoint == -1 || endPoint == -1) {
        uiLabelSetText(info, "Invalid start or end point");
        return;
    } else {
        uiLabelSetText(info, "Started");
    }

    run(fileName, 0);

    char *lenStr = malloc(sizeof(char) * 100);
    sprintf(lenStr, "%.2Lf", length);

    uiLabelSetText(len, "Length: ");
    uiLabelSetText(len, lenStr);
}

void show_map(uiButton *b, void *data) {
    startPoint = atoi(uiEntryText(e1));
    endPoint = atoi(uiEntryText(e2));

    startPoint = findNodeByName(startPoint);
    endPoint = findNodeByName(endPoint);

    if (startPoint == -1 || endPoint == -1) {
        startPoint = 0;
        endPoint = 0;
    }

    run(fileName, 1);


    uiQuit();
    uiControlDestroy(data);
}

void on_select(uiRadioButtons *r, void *data) {
    algo = uiRadioButtonsSelected(r);
    printf("algo: %d\n", algo);
}

int on_close(uiWindow *w, void *data) {
    uiQuit();
    exit(0);
}

void promptInput() {
    uiInitOptions o;
    const char *err;
    uiWindow *w;
    uiGrid *g;
    uiLabel *l;
    uiButton *b;
    uiButton *b2;

    memset(&o, 0, sizeof(uiInitOptions));
    uiInit(&o);
    w = uiNewWindow("Route Finding", 320, 240, 0);
    uiWindowSetMargined(w, 1);

    g = uiNewGrid();
    uiGridSetPadded(g, 1);

    // input box
    l = uiNewLabel("Start Point");
    uiGridAppend(g, uiControl(l), 0, 0, 1, 1,
                 1, 1,
                 0, 0);

    //input box
    e1 = uiNewEntry();
    uiEntrySetText(e1, "");
    uiGridAppend(g, uiControl(e1), 1, 0, 1, 1,
                 1, 1,
                 0, 0);
//    uiEntryOnChanged(e1, on_change_startPoint, NULL);
    l = uiNewLabel("End Point");
    uiGridAppend(g, uiControl(l), 0, 1, 1, 1,
                 1, 1,
                 0, 0);
    //input box
    e2 = uiNewEntry();
    uiEntrySetText(e2, "");
    uiGridAppend(g, uiControl(e2), 1, 1, 1, 1,
                 1, 1,
                 0, 0);
//    uiEntryOnChanged(e2, on_change_endPoint, NULL);

    // algorithm selection
    l = uiNewLabel("Algorithm");
    uiGridAppend(g, uiControl(l), 0, 2, 1, 1,
                 1, 1,
                 0, 0);

    //input box
    uiRadioButtons *rb = uiNewRadioButtons();
    uiRadioButtonsAppend(rb, "Dijkstra");
    uiRadioButtonsAppend(rb, "Bellman");
    uiGridAppend(g, uiControl(rb), 1, 2, 1, 1,
                 1, 1,
                 0, 0);
    uiRadioButtonsOnSelected(rb, on_select, NULL);

    // submit button
    b = uiNewButton("Submit");
    void **entry = malloc(sizeof(void *) * 2);
    for (int i = 0; i < 2; ++i) {
        entry[i] = malloc(sizeof(void *) * 2);
    }


    uiButtonOnClicked(b, on_submit, w);
    uiGridAppend(g, uiControl(b), 0, 3, 2, 1,
                 1, 1,
                 0, 0);

    b2 = uiNewButton("Select From Map");
    uiButtonOnClicked(b2, show_map, w);
    uiGridAppend(g, uiControl(b2), 0, 4, 2, 1,
                 1, 1,
                 0, 0);

    l = uiNewLabel("Length");
    uiGridAppend(g, uiControl(l), 0, 30, 1, 1,
                 1, 1,
                 0, 0);
    len = uiNewLabel("");
    uiGridAppend(g, uiControl(len), 1, 30, 1, 1,
                 1, 1,
                 0, 0);

    l = uiNewLabel("Info:");
    uiGridAppend(g, uiControl(l), 0, 5, 2, 1,
                 1, 1,
                 0, 0);
    info = uiNewLabel("");
    uiGridAppend(g, uiControl(info), 0, 6, 2, 1,
                 1, 1,
                 0, 0);


    uiWindowSetChild(w, uiControl(g));
    uiControlShow(uiControl(w));

    uiWindowOnClosing(w, on_close, NULL);
    uiMain();
}


int main(int argc, char *argv[]) {
    fileName = "bin/Final_Map.map";
    if (argc == 1) {
        fprintf(stdout, "Use default file: bin/Final_Map.map\n");
    } else if (argc == 2) {
        fileName = argv[1];
    } else {
        fprintf(stderr, "Usage: ./RouteFinding <fileName>\n");
        exit(1);
    }
    FILE *check = fopen(fileName, "r");
    if (check == NULL) {
        fprintf(stderr, "File \"%s\" Not found\n", fileName);
        exit(1);
    }

    dijInit(fileName);
    readNode(fileName);
    readLink(fileName);

    promptInput();
//    run(fileName, 1);
    return 0;
}