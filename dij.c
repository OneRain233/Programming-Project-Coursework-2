#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
  int id;
  int to;
  float len;
} Node;

int name[5000];          // name[i] is the name of i
int cnt = 0;             // number of nodes
Node nodes[5000][5000];  // nodes[i][j] is a node
int edgeCnt[5000];       // edgeCnt[i] is the number of edges of i
float dist[5000];        // dist[i] is the distance from start to i

void readNode(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("open file error\n");
    return;
  }
  char buf[1024];
  //<node id=250857408 lat=53.801851 lon=-1.549185 /node>
  while (fgets(buf, 1024, fp) != NULL) {
    if (strstr(buf, "<node id=") != NULL) {
      // puts(buf);
      char *p = strstr(buf, "id=");
      name[cnt] = atoi(p + 3);
      cnt++;
    }
  }
  printf("%d", cnt);
  fclose(fp);
}

int findNodeByName(int n) {
  for (int i = 0; i < cnt; i++) {
    if (name[i] == n) {
      // printf("%d\n", i);
      return i;
    }
  }
  return -1;
}

int findNodeByIndex(int idx) { return name[idx]; }

void readLink(char *filename) {
  int nodeCnt = 0;
  FILE *fp = fopen(filename, "r");
  int nodeIdx = 0;
  if (fp == NULL) {
    printf("File not found\n");
    exit(1);
  }
  char buf[100];
  // <link id=-2143392624 node=-2562 node=-2558 way=-7726 length=2.297085
  // veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>
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
      //             printf("%s %s %s\n", node1, node2, len);
      int node1Idx = findNodeByName(atoi(node1));
      int node2Idx = findNodeByName(atoi(node2));
      float len1 = atof(len);
      // printf("%d %d %f\n", node1Idx, node2Idx, len1);
      nodes[node1Idx][edgeCnt[node1Idx]].to = node2Idx;
      nodes[node1Idx][edgeCnt[node1Idx]].len = len1;
      nodes[node1Idx][edgeCnt[node1Idx]].id = atoi(id);
      edgeCnt[node1Idx]++;
      nodes[node2Idx][edgeCnt[node2Idx]].to = node1Idx;
      nodes[node2Idx][edgeCnt[node2Idx]].len = len1;
      nodes[node2Idx][edgeCnt[node2Idx]].id = atoi(id);
      edgeCnt[node2Idx]++;
      nodeCnt++;

      //            printf("%d\n", cnt);
    }
  }

  // printf("%d", nodeCnt);
}

void dij(int startPoint) {
  for (int i = 0; i < 5000; i++) {
    dist[i] = 10000000;
  }
  dist[startPoint] = 0;

  int queue[MAX_CNT];
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
      // printf("%d %d %f\n", cur, next, len);
      // printf("%f %f\n", dist[cur], dist[next]);
      if (dist[next] > dist[cur] + len) {
        // printf("%d %d %f\n", cur, next, dist[cur] + len);
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

int main() {
  readNode("Final_Map.map");
  // displayNode();
  printf("\n%d", findNodeByName(-2143395366));
  readLink("Final_Map.map");
  displayMap();
  // dij(0);
  // printf("%f\n", getLen(1));
  return 0;
}