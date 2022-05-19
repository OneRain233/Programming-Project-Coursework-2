//
// Created by onerain233 on 4/24/22.
//
#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "../include/routeFinding.h"
#include "../include/visualization.h"
#include <ui.h>

int startPoint = -8847;
int endPoint = -8849;
int algo = 0;

void run(char *filename) {
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
}

void on_submit(uiButton *b, void *data) {
    if (startPoint == -1 || endPoint == -1) {
        return;
    }
    startPoint = findNodeByName(startPoint);
    endPoint = findNodeByName(endPoint);
    uiQuit();
    uiControlDestroy(data);

}

void on_change_startPoint(uiEntry *e, void *data) {
    // get the start and end point
    startPoint = atoi(uiEntryText(e));
    printf("startPoint: %d\n", startPoint);
}

void on_change_endPoint(uiEntry *e, void *data) {
    // get the start and end point
    endPoint = atoi(uiEntryText(e));
    printf("endPoint: %d\n", endPoint);
}

void on_select(uiRadioButtons *r, void *data) {
    algo = uiRadioButtonsSelected(r);
    printf("algo: %d\n", algo);
}

int on_close(uiWindow *w, void *data) {
    uiQuit();
    exit(0);
    return 1;
}

void promptInput() {
    uiInitOptions o;
    const char *err;
    uiWindow *w;
    uiGrid *g;
    uiLabel *l;
    uiButton *b;

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
    uiEntry *e = uiNewEntry();
    uiEntrySetText(e, "");
    uiGridAppend(g, uiControl(e), 1, 0, 1, 1,
                 1, 1,
                 0, 0);
    uiEntryOnChanged(e, on_change_startPoint, NULL);
    l = uiNewLabel("End Point");
    uiGridAppend(g, uiControl(l), 0, 1, 1, 1,
                 1, 1,
                 0, 0);
    //input box
    uiEntry *e2 = uiNewEntry();
    uiEntrySetText(e2, "");
    uiGridAppend(g, uiControl(e2), 1, 1, 1, 1,
                 1, 1,
                 0, 0);
    uiEntryOnChanged(e2, on_change_endPoint, NULL);

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


    uiWindowSetChild(w, uiControl(g));
    uiControlShow(uiControl(w));

    uiWindowOnClosing(w, on_close, NULL);
    uiMain();
}


int main(int argc, char *argv[]) {
    char *filename = "bin/Final_Map.map";
//    promptInput();
    if (argc == 1) {
        fprintf(stdout, "Use default file: bin/Final_Map.map\n");
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        fprintf(stderr, "Usage: ./RouteFinding <filename>");
        exit(1);
    }
    FILE *check = fopen(filename, "r");
    if(check == NULL) {
        fprintf(stderr, "File \"%s\" Not found\n", filename);
        exit(1);
    }


    dijInit(filename);
    readNode(filename);
    readLink(filename);

    promptInput();
    run(filename);
    return 0;
}