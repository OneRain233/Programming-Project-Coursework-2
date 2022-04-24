#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routeFinding.h"

Node name[5000]; // convert name to index
int cnt = 0; // number of edges
Edge edges[5000]; // adjacency list
int edgeCnt[5000]; // number of edges
float dist[5000]; // distance from source
int path[5000]; // the shortest path


void dij_init() {
    for (int i = 0; i < 5000; i++) {
        edgeCnt[i] = 0;
        dist[i] = 0;
        path[i] = -1;
    }
}

void insertEdge(int index, int from, int to, float weight) {
    Edge *cur = &edges[index];
    Edge *new = malloc(sizeof(Edge));
    new->to = to;
    new->len = weight;
    new->next = NULL;
    new->id = from;
    if (cur->next == NULL) {
        cur->next = new;
    } else {
        Edge *tmp = cur->next;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    edgeCnt[index]++;
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
        Edge *cur = &edges[i];
        while (cur != NULL) {
            printf("%d ", cur->to);
            cur = cur->next;
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
        Edge *tmp = &edges[cur];
        while (tmp != NULL) {
            if (dist[tmp->to] > dist[cur] + tmp->len) {
                path[tmp->to] = cur;
                dist[tmp->to] = dist[cur] + tmp->len;
                queue[tail] = tmp->to;
                tail++;
            }
            tmp = tmp->next;
        }

//        for (int i = 0; i < edgeCnt[cur]; i++) {
//            int next = edges[cur][i].to;
//            float len = edges[cur][i].len;
//
//            if (dist[next] > dist[cur] + len) {
//                path[next] = cur;
//                dist[next] = dist[cur] + len;
//                queue[tail] = next;
//                tail++;
//            }
//        }
    }
    for (int i = 0; i < cnt; i++) {
        printf("%d %f\n", name[i].id, dist[i]);
    }
}

//void floyd(int startPoint) {
//    for (int i = 0; i < 5000; i++) {
//        dist[i] = 10000000;
//    }
//    dist[startPoint] = 0;
//
//    for (int i = 0; i < cnt; i++) {
//        for (int j = 0; j < cnt; j++) {
//            for (int k = 0; k < edgeCnt[j]; k++) {
//                if (dist[j] + edges[j][k].len < dist[k]) {
//                    dist[k] = dist[j] + edges[j][k].len;
//                    path[k] = j;
//                }
//            }
//        }
//    }
//}

float getLen(int endPoint) { return dist[endPoint]; }

void showPath(int endPoint) {
    int cur = endPoint;
    while (cur != -1) {
        printf("%d ", name[cur].id);
        cur = path[cur];
    }
    printf("\n");
}

Node* getNodes() {
    return name;
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