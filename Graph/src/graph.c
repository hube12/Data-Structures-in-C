#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "graph.h"


Node newNode(int id, int actualId, char *name, double latitude, double longitude) {
	Node node = (Node) malloc(sizeof(*node));
	node->id = id;
	node->actualId = actualId;
	node->name = strdup(name);
	node->latitude = latitude;
	node->longitude = longitude;
	return node;
}

Graph createGraph(int nbrVertices, ...) {
	Graph graph = (Graph) malloc(sizeof(*graph));
	if (graph == NULL) {
		fprintf(stderr, "Graph creation failed");
		exit(-1);
	}
	graph->nbrVertices = nbrVertices;
	graph->vertices = (Node *) calloc(nbrVertices, sizeof(Node));
	if (graph->vertices == NULL) {
		fprintf(stderr, "Vertices creation failed");
		exit(-1);
	}
	graph->adjacencyList = (AdjacencyList *) calloc(nbrVertices, sizeof(AdjacencyList));
	if (graph->adjacencyList == NULL) {
		fprintf(stderr, "adjacency list creation failed");
		exit(-1);
	}
	va_list args;
	va_start(args, nbrVertices);
	for (int i = 0; i < nbrVertices; i++) {
		graph->vertices[i] = va_arg(args, Node);
		graph->adjacencyList[i] = (struct NodeList *) malloc(sizeof(struct NodeList));
		if (graph->adjacencyList[i] == NULL) {
			fprintf(stderr, "Allocation of the Nodelist start failed");
			exit(-1);
		}
		graph->adjacencyList[i]->current = NULL;
		graph->adjacencyList[i]->next = NULL;
		graph->adjacencyList[i]->weight = -1;
	}
	va_end(args);
	return graph;
}

void addVertex(Graph graph, Node vertex) {
	//fixing the vertex id (or position inside the array for fast gathering)
	if (vertex->id != graph->nbrVertices) {
		fprintf(stderr, "Wrong vertex id");
		vertex->id = graph->nbrVertices;
	}

	//adding one vertex
	graph->nbrVertices = graph->nbrVertices + 1;
	//reallocating the vertices array
	Node *tempVertices = (Node *) realloc(graph->vertices, graph->nbrVertices * sizeof(Node));
	if (tempVertices == NULL) {
		fprintf(stderr, "Reallocation Vertices failed");
		exit(-1);
	}
	graph->vertices = tempVertices;

	//reallocating the adjacency list array
	AdjacencyList *tempAdjacencyList = (AdjacencyList *) realloc(graph->adjacencyList, graph->nbrVertices * sizeof(AdjacencyList));
	if (tempAdjacencyList == NULL) {
		fprintf(stderr, "Reallocation Adjacency List failed");
		exit(-1);
	}
	graph->adjacencyList = tempAdjacencyList;

	//allocating the start of the not initialized heads
	graph->adjacencyList[1] = (struct NodeList *) malloc(sizeof(struct NodeList));
	if (graph->adjacencyList[1] == NULL) {
		fprintf(stderr, "Allocation of the Nodelist start failed");
		exit(-1);
	}
	graph->adjacencyList[1]->current = NULL;
	graph->adjacencyList[1]->next = NULL;
	graph->adjacencyList[1]->weight = -1;

	//adding the vertex to the correct position
	graph->vertices[graph->nbrVertices - 1] = vertex;
}

void addVertices(Graph graph, int nbr, ...) {
	//adding vertices
	graph->nbrVertices = graph->nbrVertices + nbr;

	//reallocating the vertices array and the adjacency list
	Node *tempVertices = (Node *) realloc(graph->vertices, graph->nbrVertices * sizeof(Node));
	if (tempVertices == NULL) {
		fprintf(stderr, "Reallocation Vertices failed");
		exit(-1);
	}
	graph->vertices = tempVertices;
	AdjacencyList *tempAdjacencyList = (AdjacencyList *) realloc(graph->adjacencyList, graph->nbrVertices * sizeof(AdjacencyList));
	if (tempAdjacencyList == NULL) {
		fprintf(stderr, "Reallocation Adjacency List failed");
		exit(-1);
	}
	graph->adjacencyList = tempAdjacencyList;

	//adding the vertices to the correct position and initializing the heads
	va_list args;
	va_start(args, nbr);
	for (int i = 0; i < nbr; i++) {
		graph->adjacencyList[graph->nbrVertices - nbr + i] = (struct NodeList *) malloc(sizeof(struct NodeList));
		if (graph->adjacencyList[graph->nbrVertices - nbr + i] == NULL) {
			fprintf(stderr, "Allocation of the Nodelist start failed");
			exit(-1);
		}
		graph->adjacencyList[graph->nbrVertices - nbr + i]->current = NULL;
		graph->adjacencyList[graph->nbrVertices - nbr + i]->next = NULL;
		graph->adjacencyList[graph->nbrVertices - nbr + i]->weight = -1;
		graph->vertices[graph->nbrVertices - nbr + i] = va_arg(args, Node);
	}
	va_end(args);
}

void addLink(Graph graph, int vertexId, Node vertex, int weight) {
	AdjacencyList temp = graph->adjacencyList[vertexId];
	while (temp->next != NULL) {
		temp = temp->next;
	}
	if (temp->current == NULL) {
		//initializing the node list with the first link
		temp->current = vertex;
		temp->next = NULL;
		temp->weight = weight;
	} else {
		//adding a node to the list
		struct NodeList *tempNextNode = (struct NodeList *) malloc(sizeof(struct NodeList));
		if (tempNextNode == NULL) {
			fprintf(stderr, "Allocation of the next node failed");
			exit(-1);
		}
		temp->next = tempNextNode;
		temp->next->current = vertex;
		temp->next->next = NULL;
		temp->next->weight = weight;
	}
}

int getWeight(Graph graph, Node vertex1, Node vertex2) {
	AdjacencyList adjacencyList = graph->adjacencyList[vertex1->id];
	while (adjacencyList->next != NULL) {
		if (adjacencyList->current == vertex2) {
			return adjacencyList->weight;
		}
		adjacencyList = adjacencyList->next;
	}
	if (adjacencyList->current == vertex2) {
		return adjacencyList->weight;
	}
	return -1;
}

void getPath(Graph graph, Node start, Node end, short visited[], int paths[], int *pathIndex, int **array, int *arrIndex) {
	visited[start->id] = 1;
	paths[*pathIndex] = start->id;
	(*pathIndex)++;
	if (start == end) {
		int *intArray = (int *)calloc(graph->nbrVertices, sizeof(int));
		for (int i = 0; i < graph->nbrVertices; i++) {
			if (i>=*pathIndex){
				intArray[i]=-1;
			}else{
				intArray[i] = paths[i];
			}
		}
		array[*arrIndex] = intArray;
		(*arrIndex)++;
	} else {
		AdjacencyList temp = graph->adjacencyList[start->id];
		while (temp->next != NULL) {
			if (visited[temp->current->id] != 1) {
				getPath(graph, temp->current, end, visited, paths, pathIndex, array, arrIndex);
			}
			temp = temp->next;
		}
		if (temp->current != NULL) {
			if (visited[temp->current->id] != 1) {
				getPath(graph, temp->current, end, visited, paths, pathIndex, array, arrIndex);
			}
		}
	}
	(*pathIndex)--;
	visited[start->id] = 0;
}

int **getPaths(Graph graph, Node start, Node end) {
	short *visited = calloc(graph->nbrVertices, sizeof(short));
	int *paths = (int *) calloc(graph->nbrVertices, sizeof(int));
	int pathIndex = 0;
	int **array = (int **) calloc(graph->nbrVertices, sizeof(int *));
	int arrIndex = 0;
	getPath(graph, start, end, visited, paths, &pathIndex, array, &arrIndex);
	return array;
}

void printPaths(int **arrayPaths,int nbrVertices){
	for (int i = 0; i < nbrVertices; i++) {
		if (arrayPaths[i] != NULL) {
			for (int j=0;j<nbrVertices;j++){
				if (arrayPaths[i][j]==-1){
					break;
				}
				printf("%d ",arrayPaths[i][j]);
			}
			printf("\n");
		}
	}
}

void destroyPathArray(int **array,int nbrVertices){
	for(int i=0;i<nbrVertices;i++){
		free(array[i]);
	}
	free(array);
	*(array)=NULL;
}

void destroyNode(Node *node) {
	free((*node)->name);
	free((*node));
	(*node) = NULL;
}

void destroyGraph(Graph *graph) {
	//removing the NodeList, no need of removing the nodes since they are unique in the graph and inside the vertices array
	for (int i = 0; i < (*graph)->nbrVertices; i++) {
		AdjacencyList current = (*graph)->adjacencyList[i];
		while (current->next != NULL) {
			AdjacencyList next = current->next;
			free(current);
			current = next;
		}
		free(current);
		destroyNode(&((*graph)->vertices[i]));
	}
	free((*graph)->vertices);
	free((*graph)->adjacencyList);
	free((*graph));
	(*graph) = NULL;
}
