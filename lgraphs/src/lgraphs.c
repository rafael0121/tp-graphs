#include <stdlib.h>
#include <stdio.h>
#include <lgraphs.h>

Graph * graph_create(bool directed, unsigned n){
	Graph *graph = malloc(sizeof(Graph));

    graph->total_vertex = n;
    graph->total_edge = 0;
	graph->directed = directed;
	graph->degree = 0;

    graph->vertex_array = malloc(sizeof(Vertex) * n);

    for(int i=0; i<n; i++){
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
		graph->vertex_array[i].degree = 0;
        graph->vertex_array[i].edge_array = 0;
	}
    
    return graph;
}
