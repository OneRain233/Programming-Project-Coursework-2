#ifndef CWK_DIJ_H
#define CWK_DIJ_H

typedef struct _Edge {
    int id;
    int to;
    long double len;
    struct _Edge *next;
} Edge;

typedef struct _Node {
    int id;
    long double lat;
    long double lon;
    struct _Edge *head;
} Node;


int dijInit(char *filename);
int insertEdge(int index, int to, long double weight);
int getNodesCnt(char *filename);
int readNode(char *filename);
int findNodeByName(int n);
int findNodeByIndex(int idx);
void displayMap();
int readLink(char *filename);
long double *dij(int startPoint);
long double getLen(int endPoint);
void showPath(int endPoint);
Node* getNodes();
void floyd();
int getNodeCnt();
int *getPath();
long double *bellman(int startPoint);
long double *getDist();

#endif //CWK_DIJ_H