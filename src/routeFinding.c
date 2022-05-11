#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/routeFinding.h"

Node *nodes = NULL; // convert nodes to index
int nodeCnt = 0; // number of edgesHead
long double *dist = NULL; // distance from source
int *path = NULL; // the shortest path
int *queue = NULL; // queue
long double maxLat = -1e8; // max latitude
long double maxLon = -1e8; // max longitude
long double minLat = 1e8; // min latitude
long double minLon = 1e8; // min longitude
int edgeCnt = 0;

int dijInit(char *filename) {

    int N = getNodesCnt(filename);
    if (N == 0) {
        fprintf(stderr, "Error: No nodes found\n");
        return 0;
    } else if (N == -1) {
        return -1;
    }
    nodeCnt = 0;
    N = N * 4;
    dist = (long double *) malloc(N * sizeof(long double));
    path = (int *) malloc(N * sizeof(int));
    nodes = (Node *) malloc(N * sizeof(Node));
    queue = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        dist[i] = (long double) 10000000.0;
        path[i] = -1;
    }
    return 1;
}


int insertEdge(int index, int to, long double weight) {
    Node *p = &nodes[index];
    if (p == NULL) {
        fprintf(stderr, "Error: Node not found\n");
        return 0;
    }
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
    return 1;
}

int getNodesCnt(char *filename) {
    int tmpCnt = 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File %s open error\n", filename);
        return -1;
    }
    int NodeCnt = 0;
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        if (strstr(line, "<node id=") != NULL) {
            tmpCnt++;
        }
    }
    fclose(fp);
    return tmpCnt;
}

int readNode(char *filename) {
    int init = dijInit(filename);
    if (init == -1) {
        return -1;
    }
    if (init == 0) {
        return 0;
    }
    FILE *fp = fopen(filename, "r");
    char buf[1024];
    while (fgets(buf, 1024, fp) != NULL) {
        if (strstr(buf, "<node id=") != NULL) {
            char *p = strstr(buf, "id=");
            nodes[nodeCnt].id = atoi(p + 3);
            p = strstr(buf, "lat=");
            nodes[nodeCnt].lat = atof(p + 4);
            p = strstr(buf, "lon=");
            nodes[nodeCnt].lon = atof(p + 4);
            nodeCnt++;
            if (nodes[nodeCnt].lat > maxLat) maxLat = nodes[nodeCnt].lat;
            if (nodes[nodeCnt].lat < minLat) minLat = nodes[nodeCnt].lat;
            if (nodes[nodeCnt].lon > maxLon) maxLon = nodes[nodeCnt].lon;
            if (nodes[nodeCnt].lon < minLon) minLon = nodes[nodeCnt].lon;
        }
    }
    fclose(fp);
    return nodeCnt;
}

int findNodeByName(int n) {
    for (int i = 0; i < nodeCnt; i++) {
        if (nodes[i].id == n) {
            return i;
        }
    }
    return -1;
}

int findNodeByIndex(int idx) { return nodes[idx].id; }

void displayNode() {
    for (int i = 0; i < nodeCnt; i++) {
        fprintf(stdout, "%d ", nodes[i].id);
    }
    fprintf(stdout, "\n");
}

void displayMap() {
    for (int i = 0; i < nodeCnt; i++) {
        fprintf(stdout, "%d ", nodes[i].id);
        Edge *p = nodes[i].head;
        while (p != NULL) {
            fprintf(stdout, "%d ", p->to);
            p = p->next;
        }

        printf("\n");
    }
}


int readLink(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found\n");
        return -1;
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
            long double len1 = atof(len);
//            printf("%Lf\n", len1);
            int insertRes1 = insertEdge(node1Idx, node2Idx, len1);
            int insertRes2 = insertEdge(node2Idx, node1Idx, len1);
            if (insertRes1 == 0 || insertRes2 == 0) {
                fprintf(stderr, "insert error\n");
                exit(1);
            }
            edgeCnt++;
        }
    }
    fclose(fp);
    return edgeCnt;

}

long double *dijkstra(int startPoint) {
    if (startPoint < 0) {
        return NULL;
    }
    dist[startPoint] = 0;

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
            long double len = e->len;
            if (dist[next] > dist[cur] + len) {
                path[next] = cur;
                dist[next] = dist[cur] + len;
                queue[tail] = next;
                tail++;
            }
            e = e->next;
        }
    }
//    for (int i = 0; i < nodeCnt; i++) {
//        printf("%Lf ", dist[i]);
//    }
    return dist;
}

long double *bellman(int startPoint) {
    if (startPoint < 0) {
        return NULL;
    }
    dist[startPoint] = 0;
    int flag = 0;

    for (int i = 0; i < edgeCnt; i++) {
        flag = 0;
        for (int j = 0; j < nodeCnt; j++) {
            Edge *p = nodes[j].head;
            while (p != NULL) {
                int next = p->to;
                long double len = p->len;
                if (dist[next] > dist[j] + len) {
                    dist[next] = dist[j] + len;
                    path[next] = j;
                    flag = 1;
                }
                p = p->next;
            }

        }
        if (flag == 0) break;
    }
    return dist;
}

void showPath(int endPoint) {
    int cur = endPoint;
    while (cur != -1) {
        fprintf(stdout, "%d ", nodes[cur].id);
        cur = path[cur];
    }
    printf("\n");
}

int *getPath() {
    return path;
}

Node *getNodes() {
    return nodes;
}

int getNodeCnt() {
    return nodeCnt;
}

long double *getDist() {
    return dist;
}