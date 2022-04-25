#ifndef CWK_DIJ_H
#define CWK_DIJ_H

typedef struct _Edge {
    int id;
    int to;
    float len;
    struct _Edge *next;
} Edge;

typedef struct _Node {
    int id;
    int lat;
    int lon;
    struct _Edge *head;
} Node;


void dij_init();
void readNode(char *filename);
int findNodeByName(int n);
int findNodeByIndex(int idx);
void displayMap();
void readLink(char *filename);
void dij(int startPoint);
float getLen(int endPoint);
void showPath(int endPoint);
Node* getNodes();
void floyd();

#endif //CWK_DIJ_H