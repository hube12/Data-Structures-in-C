#ifndef GRAPH_H
#define GRAPH_H

//we defined Example as a Basic Node
struct Example {
	int id;
	int actualId;
	char *name;
	double latitude;
	double longitude;
};
typedef struct Example *Node;

// We defined a NodeList to use inside the adjacency list
// The NodeList refer to the node n+1 and the weight between the node n and n+1
// Meaning we can have all the weights in a chain without creating a needless extra node
// The position inside an AdjacencyList array refer to the node to which the adjacencyList start of
// The first node of the AdjacencyList[i] is the one following the node Vertices[i]
struct NodeList {
	Node current;
	int weight;
	struct NodeList *next;
};
typedef struct NodeList *AdjacencyList;

//we defined a graph as an array of vertices holding the object datas
// then an adjacency list array as defined previously
// ofc we need to know the current numbers of vertices
struct Graph_ {
	Node *vertices;
	int nbrVertices;
	AdjacencyList *adjacencyList;
};
typedef struct Graph_ *Graph;

Node newNode(int id, int actualId, char *name, double latitude, double longitude);

Graph createGraph(int nbrVertices, ...);

void addVertices(Graph graph, int nbr, ...);

void addVertex(Graph graph, Node vertex);

void destroyGraph(Graph *graph);

void destroyNode(Node *node);

void addLink(Graph graph, int vertexId, Node vertex, int weight);

int getWeight(Graph graph,Node vertex1, Node vertex2);

int** getPaths(Graph graph,Node start,Node end);

void printPaths(int **arrayPaths,int nbrVertices);

void destroyPathArray(int **array,int nbrVertices);

#endif //GRAPH_H