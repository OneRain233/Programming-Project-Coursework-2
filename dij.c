#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dij.h"

Node name[5000]; // convert name to index
int cnt = 0; // number of nodes
Edge nodes[5000][5000]; // adjacency list
int edgeCnt[5000]; // number of edges
float dist[5000]; // distance from source
int path[5000]; // the shortest path

void dij_init(){
    for(int i = 0; i < 5000; i++){
        edgeCnt[i] = 0;
        dist[i] = 0;
        path[i] = -1;
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
            name[cnt].id = atoi(p + 3);
            p = strstr(buf, "lat=");
            name[cnt].lat = atof(p + 4);
            p = strstr(buf, "lon=");
            name[cnt].lon = atof(p + 4);
            cnt++;
        }
    }
    printf("%d", cnt);
    fclose(fp);
}

int findNodeByName(int n) {
    for (int i = 0; i < cnt; i++) {
        if (name[i].id == n) {
            return i;
        }
    }
    return -1;
}

int findNodeByIndex(int idx) { return name[idx].id; }

void displayNode() {
    for (int i = 0; i < cnt; i++) {
        printf("%d ", name[i].id);
    }
    printf("\n");
}

void displayMap() {
    for (int i = 0; i < cnt; i++) {
        printf("%d: ", findNodeByIndex(i));
        for (int j = 0; j < edgeCnt[i]; j++) {
            printf("%d ", findNodeByIndex(nodes[i][j].to));
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
            nodes[node1Idx][edgeCnt[node1Idx]].to = node2Idx;
            nodes[node1Idx][edgeCnt[node1Idx]].len = len1;
            nodes[node1Idx][edgeCnt[node1Idx]].id = atoi(id);
            edgeCnt[node1Idx]++;
            nodes[node2Idx][edgeCnt[node2Idx]].to = node1Idx;
            nodes[node2Idx][edgeCnt[node2Idx]].len = len1;
            nodes[node2Idx][edgeCnt[node2Idx]].id = atoi(id);
            edgeCnt[node2Idx]++;
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
        for (int i = 0; i < edgeCnt[cur]; i++) {
            int next = nodes[cur][i].to;
            float len = nodes[cur][i].len;

            if (dist[next] > dist[cur] + len) {
                path[next] = cur;
                dist[next] = dist[cur] + len;
                queue[tail] = next;
                tail++;
            }
        }
    }
    for (int i = 0; i < cnt; i++) {
        printf("%d %f\n", name[i], dist[i]);
    }
}

float getLen(int endPoint) { return dist[endPoint]; }

void showPath(int endPoint) {
    int cur = endPoint;
    while (cur != -1) {
        printf("%d ", name[cur]);
        cur = path[cur];
    }
    printf("\n");
}

//int main() {
//    readNode("Final_Map.map");
//    for (int i = 0; i < 5000; i++) {
//        path[i] = -1;
//    }
//    readLink("Final_Map.map");
//    // displayMap();
//    dij(10);
//    printf("start:%d end: %d\n", name[10], name[888]);
//    printf("%f\n", getLen(888));
//    showPath(888);
//    return 0;
//}