#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routeFinding.h"

Node nodes[5000]; // convert nodes to index
int cnt = 0; // number of edgesHead
float dist[5000]; // distance from source
int path[5000]; // the shortest path


void dij_init() {
    for (int i = 0; i < 5000; i++) {
        dist[i] = 0;
        path[i] = -1;
    }
}


void insertEdge(int index, int from, int to, float weight) {
    Node *p = &nodes[index];
    Edge *e = (Edge *) malloc(sizeof(Edge));
    e->to = to;
    e->len = weight;
    e->next = NULL;
    if (p->head == NULL) {
        p->head = e;
    } else {
        Edge *q = p->head;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = e;
    }
}

void readNode(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("open file error\n");
        return;
    }
    char buf[1024];
    while (fgets(buf, 1024, fp) != NULL) {
        if (strstr(buf, "<node id=") != NULL) {
            // puts(buf);
            char *p = strstr(buf, "id=");
            nodes[cnt].id = atoi(p + 3);
            p = strstr(buf, "lat=");
            nodes[cnt].lat = atof(p + 4);
            p = strstr(buf, "lon=");
            nodes[cnt].lon = atof(p + 4);
            cnt++;
        }
    }
//    printf("%d", cnt);
    fclose(fp);
}

int findNodeByName(int n) {
    for (int i = 0; i < cnt; i++) {
        if (nodes[i].id == n) {
            return i;
        }
    }
    return -1;
}

int findNodeByIndex(int idx) { return nodes[idx].id; }

void displayNode() {
    for (int i = 0; i < cnt; i++) {
        printf("%d ", nodes[i].id);
    }
    printf("\n");
}

void displayMap() {
    for (int i = 0; i < cnt; i++) {
        printf("%d ", nodes[i].id);
        Edge *p = nodes[i].head;
        while (p != NULL) {
            printf("%d ", p->to);
            p = p->next;
        }

        printf("\n");
    }
}


void readLink(char *filename) {
    int nodeCnt = 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found\n");
        exit(1);
    }
    while (!feof(fp)) {
        char id[20] = {0};
        char node1[20] = {0};
        char node2[20] = {0};
        char way[20] = {0};
        char len[20] = {0};
        char veg[20] = {0};
        char arch[20] = {0};
        char land[20] = {0};
        char poi[20] = {0};
        char buffer[100] = {0};
        fgets(buffer, 100, fp);
        if (strstr(buffer, "<link")) {
            sscanf(buffer,
                   "<link id=%s node=%s node=%s way=%s length=%s veg=%s arch=%s "
                   "land=%s POI=%s;/link>",
                   &id, &node1, &node2, &way, &len, &veg, &arch, &land, &poi);
            int node1Idx = findNodeByName(atoi(node1));
            int node2Idx = findNodeByName(atoi(node2));
            float len1 = atof(len);
            insertEdge(node1Idx, node1Idx, node2Idx, len1);
            insertEdge(node2Idx, node2Idx, node1Idx, len1);
            nodeCnt++;

        }
    }

}

void dij(int startPoint) {
    for (int i = 0; i < 5000; i++) {
        dist[i] = 10000000;
    }
    dist[startPoint] = 0;

    int queue[5000 * 2];
    int head = 0;
    int tail = 0;
    queue[tail] = startPoint;
    tail++;

    while (head < tail) {
        int cur = queue[head];
        head++;
        Node *p = &nodes[cur];
        Edge *e = p->head;
        while (e != NULL) {
            int next = e->to;
            float len = e->len;
            if (dist[next] > dist[cur] + len) {
                path[next] = cur;
                dist[next] = dist[cur] + len;
                queue[tail] = next;
                tail++;
            }
            e = e->next;
        }

    }
    for (int i = 0; i < cnt; i++) {
        printf("%d %f\n", nodes[i].id, dist[i]);
    }
}

//void floyd() {
//    float map1[cnt + 1][cnt + 1];
//    for (int i = 0; i < cnt; i++) {
//        for (int j = 0; j < cnt; j++) {
//            map1[i][j] = 1000;
//        }
//    }
//    for (int i = 0; i < cnt; i++) {
//        Edge *cur = edgesHead[i].next;
//        while (cur != NULL) {
//            map1[i][cur->to] = cur->len;
//            cur = cur->next;
//        }
//    }
//
//    for (int k = 0; k < cnt; k++) {
//        for (int i = 0; i < cnt; i++) {
//            for (int j = 0; j < cnt; j++) {
//                if (map1[i][k] + map1[k][j] < map1[i][j]) {
//                    map1[i][j] = map1[i][k] + map1[k][j];
//                }
//            }
//        }
//    }
//
//    // display
//    for (int i = 0; i < cnt; i++) {
//        for (int j = 0; j < cnt; j++) {
//            printf("%f ", map1[i][j]);
//        }
//        printf("\n");
//    }
//
//
//}

float getLen(int endPoint) { return dist[endPoint]; }

void showPath(int endPoint) {
    int cur = endPoint;
    while (cur != -1) {
        printf("%d ", nodes[cur].id);
        cur = path[cur];
    }
    printf("\n");
}

Node *getNodes() {
    return nodes;
}