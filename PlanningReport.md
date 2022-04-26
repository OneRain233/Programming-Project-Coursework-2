# Route Finding Project

Name: Liu Zhe

Student Number: 2020110019

# Summary

### Introduction

This project aims at finding the shortest route between the two given points. The project I choose it the first project which is *Route finding*. This project should implement that find the shortest way between the two given points. First, the project should read the given map file into the data structure. Then, it should build the graph first using adjacent list and then use Dijkstra algorithm to find the shortest way. The graph data structure will be la strut which have the attribute `id, to, len`, which are the `id` is the node id and `to` is the destination of the node and  `len` is the weight of the edge. Then the node structure of node will be like `id, lat, lon, edges`, while `id ` is the  id of the node, `lat` and `lon` is the latitude and longitude of the node, `edges` is the head of linked list that contains all the edges of the nodes.   Then it should record the `path` of the shortest way and at last, it should visualize the graph and the found shortest way using the given information about nodes and links. 

### Modules

#### Main

Used to call other modules.

| Name | Description                   |
| ---- | ----------------------------- |
| main | The main logic of the project |

#### Route finding

Used to find the shortest way of the graph

| Name       | Description                     |
| ---------- | ------------------------------- |
| dij_init() | Used to initialize the Dijkstra |
| readNode() | Used to read nodes from the map |
| readLink() | Used to read links from the map |
| dij()      | Used to find the shortest route |

#### Visualization

Used to display the map and the shortest way between two given points.



# Test Plan

### Testing methodology

I use **Functional testing** and **Non-function testing** to test my project. Functional testing include **Unit testing, Integration testing, System testing and Acceptance testing**. 

For the unit testing, I will test all the functions in different test cases including some valid cases and some invalid cases and then monitor whether it performs in its expected way.

For the Integration testing, it will test the logic of some functions, which means that I should test a group of functions and monitor the group whether it perform in its expected way.

For the system testing, it means that I should test the complete system which means that a map file is given to the system and it will output the specific shortest route based on the input of users including the start point and the end point. Then test if the system will display the graph correctly.

### Tests cases

**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `void readNode(char *filename);`

<u>Expected behaviour:</u>

   				1. Read the nodes from the given file whose file name is `filename` to the variable which stores the nodes.

<u>Assertions:</u>

1. The file name pointer `filename` is not NULL

<u>Test cases:</u>

​	C1:

​			Input: A normal file name 

​			Expected result: All the nodes will be stored to the variable.

​	C2: 

​			Input: A NULL file name

​			Expect result: Display an error message and exit with status 1			





**Function** : `void readLink(char *filename);`

<u>Expected behaviour:</u>

   				1. Read the links from the given file whose file name is `filename` to the variable that stores the edges.

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;





**Function** : `int dij_init();`

<u>Expected behaviour:</u>

   				1. The value of `dist` array is set to `0`;
   				2. the value of `path` array is set to `-1`;

<u>Assertions:</u>

1. No input

<u>Test cases:</u>

​	C1:

​			Input: No input

​			Expected result: The value of element of dist is set to `0` and the value oe 			elements of path is set to `-1`;

