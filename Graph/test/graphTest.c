#define SNOW_ENABLED
#define SNOW_USE_FNMATCH 0
#include "../src/graph.h"
#include "../include/snow.h"


describe(Structure_Graph){
	it("Node Creation"){
		Node node=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		assertneq(node,NULL,"The node creation failed");
		asserteq_str(node->name,"Muş Airport","The name of a node was not correctly copied");
		asserteq_dbl(node->latitude,38.747798919677734,"The node latitude was not correctly initialized (maybe lost of precision)");
		asserteq_dbl(node->longitude,41.66120147705078,"The node longitude was not correctly initialized (maybe lost of precision)");
		asserteq_int(node->id,0,"The graph id of the node is not correct");
		asserteq_int(node->actualId,6782,"The node actualId is not correct");
		destroyNode(&node);
		asserteq(node,NULL,"The node destruction failed");
	}
	it("Empty graph Creation"){
		Graph graph=createGraph(0);
		assertneq(graph,NULL,"The graph creation failed");
		assertneq(graph->adjacencyList,NULL,"The adjacency list creation failed");
		assertneq(graph->vertices,NULL,"The vertices list creation failed");
		asserteq_int(graph->nbrVertices,0,"The numbers of vertices isn't correct");
		destroyGraph(&graph);
		asserteq(graph,NULL,"The graph destruction failed");
	}
	it("Graph creation"){
		Node node=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		assertneq(node,NULL,"The node creation failed");
		Graph graph=createGraph(1,node);
		assertneq(graph,NULL,"The graph creation failed");
		assertneq(graph->adjacencyList,NULL,"The adjency list creation failed");
		assertneq(graph->vertices,NULL,"The vertices list creation failed");
		asserteq_int(graph->nbrVertices,1,"The numbers of vertices isn't correct");
		assertneq(graph->adjacencyList[0],NULL,"The adjacency list initialization failed");
		assertneq(graph->vertices[0],NULL,"The vertices list initialization failed");
		asserteq_ptr(graph->vertices[0],node,"The array of vertices was not correctly initialized");
		asserteq(graph->adjacencyList[0]->current,NULL,"The adjacency list actual node was not correctly initialized");
		asserteq(graph->adjacencyList[0]->next,NULL,"The adjacency list next node was not correctly initialized");
		asserteq_int(graph->adjacencyList[0]->weight,-1,"The weight the adjacency list was not correctly initialized");
		destroyGraph(&graph);
		asserteq(graph,NULL,"The graph destruction failed");
	}
	it("Graph creation 2"){
		Node node=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		Node node2=newNode(1,6783,"Sinop Airport",42.015800476074,35.066398620605);
		Graph graph=createGraph(2,node,node2);
		assertneq(graph,NULL,"The graph creation failed");
		asserteq_ptr(graph->vertices[0],node,"The array of vertices was not correctly initialized");
		asserteq_ptr(graph->vertices[1],node2,"The array of vertices was not correctly initialized");
		destroyGraph(&graph);
		asserteq(graph,NULL,"The graph destruction failed");
	}
	it("Graph adding vertex"){
		Node node=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		Node node2=newNode(1,6783,"Sinop Airport",42.015800476074,35.066398620605);
		Graph graph=createGraph(1,node);
		assertneq(graph,NULL,"The graph creation failed");
		asserteq_ptr(graph->vertices[0],node,"The array of vertices was not correctly initialized");
		addVertex(graph,node2);
		asserteq_int(graph->nbrVertices,2,"The number of vertices was not correctly updated");
		asserteq_ptr(graph->vertices[0],node,"The array of vertices was not correctly initialized");
		asserteq_ptr(graph->vertices[1],node2,"The array of vertices was not correctly initialized");
		destroyGraph(&graph);
		asserteq(graph,NULL,"The graph destruction failed");
	}
	it("Graph adding vertices"){
		Node node=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		Node node2=newNode(1,6783,"Sinop Airport",42.015800476074,35.066398620605);
		Graph graph=createGraph(0);
		assertneq(graph,NULL,"The graph creation failed");
		addVertices(graph,2,node,node2);
		asserteq_ptr(graph->vertices[0],node,"The array of vertices was not correctly initialized");
		asserteq_ptr(graph->vertices[1],node2,"The array of vertices was not correctly initialized");
		destroyGraph(&graph);
		asserteq(graph,NULL,"The graph destruction failed");
	}
	it("Graph linking"){
		Node node=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		assertneq(node,NULL,"The node creation failed");
		Node node2=newNode(1,6783,"Sinop Airport",42.015800476074,35.066398620605);
		assertneq(node2,NULL,"The node creation failed");
		Graph graph=createGraph(2,node,node2);
		assertneq(graph,NULL,"The graph creation failed");
		asserteq_ptr(graph->vertices[0],node,"The array of vertices was not correctly initialized");
		asserteq_ptr(graph->vertices[1],node2,"The array of vertices was not correctly initialized");
		addLink(graph,0,node2,13);
		asserteq_int(getWeight(graph,node,node2),13,"The link was not correctly made between node id=0 and node id=1");
		addLink(graph,0,node,10);
		asserteq_int(getWeight(graph,node,node),10,"The link was not correctly made between node id=0 and node id=0");
		asserteq_int(getWeight(graph,node2,node),-1,"A link exists between node id=1 and node id=0 whereas none was created");
		asserteq_int(getWeight(graph,node2,node2),-1,"A link exists between node id=1 and node id=1 whereas none was created");
		destroyGraph(&graph);
		asserteq(graph,NULL,"The graph destruction failed");
	}
	it("Graph paths"){
		Node node0=newNode(0,6782,"Muş Airport",38.747798919677734,41.66120147705078);
		Node node1=newNode(1,6783,"Sinop Airport",42.015800476074,35.066398620605);
		Node node2=newNode(2,6783,"Sinop Airport",42.015800476074,35.066398620605);
		Node node3=newNode(3,6783,"Sinop Airport",42.015800476074,35.066398620605);
		Graph graph=createGraph(4,node0,node1,node2,node3);
		addLink(graph,0,node1,13);
		addLink(graph,1,node2,13);
		addLink(graph,0,node2,13);
		addLink(graph,2,node3,13);
		int **array=getPaths(graph,node0,node3);
		int array1[]={0,1,2,3};
		int array2[]={0,2,3};
		asserteq_buf(array[0],array1, sizeof(array1),"The path was not correctly found");
		asserteq_buf(array[1],array2, sizeof(array2),"The path was not correctly found");
        //destroyPathArray(array,4);
	}
}

snow_main();