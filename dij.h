typedef struct _Node {
    int id;
    int to;
    float len;
} Node;

int name[5000]; // convert name to index
int cnt = 0; // number of nodes
Node nodes[5000][5000]; // adjacency list
int edgeCnt[5000]; // number of edges
float dist[5000]; // distance from source
int path[5000]; // the shortest path


void readNode(char *filename);
int findNodeByName(int n);
int findNodeByIndex(int idx);
void displayMap();
void readLink(char *filename);
void dij(int startPoint);
float getLen(int endPoint);
