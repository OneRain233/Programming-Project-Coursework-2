# Route Finding Project

Name: Liu Zhe

Student Number: 2020110019

# Summary

### Introduction

This project aims at finding the shortest route between the two given points. The project I choose it the first project which is *Route finding*. This project should implement that find the shortest way between the two given points. First, the project should read the given map file into the data structure. Then, it should build the graph first using adjacent list and then use Dijkstra and Bellman Ford algorithm to find the shortest way. The graph data structure will be la strut which have the attribute `id, to, len`, which are the `id` is the node id and `to` is the destination of the node and  `len` is the weight of the edge. Then the node structure of node will be like `id, lat, lon, edges`, while `id ` is the  id of the node, `lat` and `lon` is the latitude and longitude of the node, `edges` is the head of linked list that contains all the edges of the nodes.   Then it should record the `path` of the shortest way and at last, it should visualize the graph and the found shortest way using the given information about nodes and links. 

### Modules

#### Main

Used to call other modules.

| Name               | Description                          |
| ------------------ | ------------------------------------ |
| int main()         | The main logic of the project        |
| void run()         | Run the route finding algorithm      |
| void promptInput() | Prompt the input of user in GUI mode |

#### Route finding

Used to find the shortest way of the graph

| Name                                                  | Description                            |
| ----------------------------------------------------- | -------------------------------------- |
| int dijInit(char *fileName)                           | Used to initialize the Dijkstra        |
| int readNode(char *fileName)                          | Used to read nodes from the map        |
| int readLink(char *fileName);                         | Used to read links from the map        |
| int insertEdge(int index, int to, long double weight) | Used to add edges to the adjacent list |
| long double *dijkstra(int startPoint);                | Used to find the shortest route        |
| long double *bellman(int startPoint);                 | Used to find the shortest route        |

#### Visualization

Used to display the map and the shortest way between two given points.

| Name              | Description                                               |
| :---------------- | --------------------------------------------------------- |
| void calcPosition | Used to calculate the position of the point in the window |
| void draw    | Used to draw all the point and edges of the map          |
| void update       | Used to update the view when user want to drag or zoom |
| int visualize     | Main logic of the visualization |

# Test Plan

### Testing methodology

I use **Functional testing** and **Non-function testing** to test my project. Functional testing include **Unit testing, Integration testing, System testing and Acceptance testing**. 

For the unit testing, I will test all the functions in different test cases including some valid cases and some invalid cases and then monitor whether it performs in its expected way.

For the Integration testing, it will test the logic of some functions, which means that I should test a group of functions and monitor the group whether it perform in its expected way.

For the system testing, it means that I should test the complete system which means that a map file is given to the system and it will output the specific shortest route based on the input of users including the start point and the end point. Then test if the system will display the graph correctly.

### Tests cases

**Function** : `int dijInit(char *fileName);`

<u>Expected behavior:</u>

1. The value of `dist` array is set to `0`;
2. the value of `path` array is set to `-1`;
3. The variables `dist`, `path`, `nodes` and `queue` should be allocated.

<u>Assertions:</u>

1. A valid file name is given;

<u>Test cases:</u>

​		C1:

​				Input: A valid file name;

​				Expected result: The value of element of dist is set to `0` and the value of elements of path is set to `-1`; The variables 				should be allocated

​		C2:

​				Input: A invalid file name (not exist);

​				Expected result: It will return `-1`;



**Function** : `int readNode(char *fileName);`

<u>Expected behavior:</u>

1. Read the nodes from the given file whose file name is fileName to the variable which stores the nodes.
2. If success, return `the number of the nodes`, if fail, return `-1`;

<u>Assertions:</u>

1. The file name pointer `fileName` is not NULL and the file exists.

<u>Test cases:</u>

​	C1:

​			Input: A normal file name with some nodes

​			Expected result: All the nodes will be stored to the variable and return the number of nodes

​	C2: 

​			Input: A NULL file name

​			Expect result: Display an error message and return `-1`

​	C3:

​			Input: A valid file name with 0 node in;

​			Expected result: It will return `0`;



**Function** : `int readLink(char *fileName);`

<u>Expected behavior:</u>

1. Read the links from the given file whose file name is `fileName` to the variable that stores the edges.
1. Convert the given node id to a small id which will be used to find the shortest route.
1. If success return `the number of edges`, if fail return `-1`

<u>Assertions:</u>

1. The file name pointer `fileName` is not NULL

<u>Test cases:</u>

​	C1:

​			Input: A valid file name with some edges;

​			Expected result: The links are stored to the struct and return the number of edges.

​	C2:

​			Input: A NULL file name

​			Expected result: Display an error message and return `-1`;

​	C3:

​			Input: A valid file name with no edge;

​			Expected result: It will return `0`;



**Function**: `int getNodesCnt(char *fileName);`

<u>Expected behavior:</u>

1. Read the file and count the number of nodes;
2. Return the number of the nodes.

<u>Assertions:</u>

1. The file name pointer `fileName` is not NULL

<u>Test cases:</u>

​	C1:

​		Input: A normal file name;

​		Expected result: Count the number of nodes and return the count;

​	C2:

​		Input: A NULL file name:

​		Expected result: Display an error message and return `-1`



**Function**: `int insertEdge(int index, int to, long double weight) `

<u>Expected behavior:</u>

1. Insert the edge from `index`  to `to` with the length `weigth`;
2. Return `1` if success and `0` fail

<u>Assertions:</u>

1. The `index` is valid

<u>Test cases:</u>

​	C1:

​		Input: A valid `index, to, weight`

​		Expected result: Add the edge from `index` to `to` with length `weigth`;

​	C2:

​		Input: An invalid `index`

​		Expected result: Display an error message and return `0`



**Function**: `long double *dijkstra(int startPoint)`

<u>Expected behavior:</u>

1. Find the shortest route from the start point;
2. Record the path of shortest route
3. Calculate the shortest way to each point from the start point;

<u>Assertions:</u>

1. The start point is valid.

<u>Test cases:</u>

​	C1: 

​		Input: A valid start point like `10`;

​		Expected result:  The program should compute the shortest route from the start point and store it in the `dist` variable. The 		path to each point should be record to the `path` variable.

​	C2:

​		Input: An invalid start  point `-1`;

​		Expect result: Display an error message and return



**Function**: `long double *bellman(int startPoint)`

<u>Expected behavior:</u>

1. Find the shortest route from the start point;
2. Record the path of shortest route
3. Calculate the shortest way to each point from the start point;

<u>Assertions:</u>

1. The start point is valid.

<u>Test cases:</u>

​	C1: 

​		Input: A valid start point like `10`;

​		Expected result:  The program should compute the shortest route from the start point and store it in the `dist` variable. The path to each point should be record to the `path` variable.

​	C2:

​		Input: An invalid start  point `-1`;

​		Expected result: Display an error message and return



**Function:** `void calcPosition(long double x, long double y, long double *x_pos, long double *y_pos, long double baseX,long double baseY, long double offsetX, long double offsetY, long double scale)`

<u>Expected behavior:</u>

1. Calculate the position of the point in the window;
2. Store the relative position of the given `x` and `y` in `x_pos` and `y_pos`;

<u>Assertions:</u>

1. All the arguments are valid;

<u>Test cases:</u>

​	C1:

​		Input: Valid arguments;

​		Expected result: The `x_pos` and `y_pos` store the relative position.



**Function: ** `void draw(SDL_Renderer *renderer, Node *nodes, const int *path, int node_cnt, long double baseX, long double baseY, int endPoint, long double offsetX, long double offsetY, long double scale, long double pointSize) `

<u>Expected behavior:</u>

1. Draw the map in the given `renderer` according to the arguments, includes the `nodes`, `edges` and the found `shortest path`.

<u>Assertions:</u>

1. All the arguments are valid;

<u>Test cases:</u>

​	C1:

​			Input: Valid arguments;

​			Expected results: The renderer has been draw.



**Function:** `int visualize(SDL_Window *window, SDL_Renderer *renderer, Node *nodes, int *path, int node_cnt, long double baseX, long double baseY, int endPoint)`

<u>Expected behavior:</u>

1. Initialize the window and renderer;
2. Call other functions to draw the nodes and edges;
3. Monitor user's event include Quit, Mouse wheel scroll, Mouse motion, Mouse button press, and some key down; 
4. Update the view when user prompt to zoom in and out, drag. 

<u>Assertions:</u>

1. All the arguments are valid;

<u>Test cases:</u>

​	C1:

​			Input: Valid arguments;

​			Expected result: The map was draw on the window, and user can zoom in and out, drag to move, and quit.

# Schedule

| Date                  | What should I do                                  |
| --------------------- | ------------------------------------------------- |
| 2022.4.21 - 2022.4.25 | Implement the read and store of the map.          |
| 2022.4.26 - 2022.4.29 | Implement the Dijkstra and Bellman Ford algorithm |
| 2022.4.30 - 2022.5.4  | International Work's Day                          |
| 2022.5.5 - 2022.5.10  | Implement the visualization part                  |
| 2022.5.11 - 2022.5.15 | Test the program                                  |
