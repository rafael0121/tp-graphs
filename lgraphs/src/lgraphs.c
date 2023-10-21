#include <stdlib.h>
#include <stdio.h>
#include <lgraphs.h>

Graph * graph_create(bool directed, unsigned n){
	Graph *graph = malloc(sizeof(Graph));

    graph->total_vertex = n;
    graph->total_edge = n * (n-1);
	graph->directed = directed;
	graph->degree = 0;
    
    graph->vertex_array = malloc(sizeof(Vertex) * n);

    for(int i=0; i<n; i++){
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
		graph->vertex_array[i].degree = 0;
        graph->vertex_array[i].edge_array = malloc(sizeof(void) * n);
	}
    
    return graph;
}

void edge_insert(Graph *graph, unsigned id1, unsigned id2, int weight){

    Edge *edge_new = malloc(sizeof(Edge));

    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];

    edge_new->weight = weight;
    edge_new->vertex_left = &graph->vertex_array[id1];
    edge_new->vertex_right = &graph->vertex_array[id2];

    vertex_1->edge_array[vertex_1->degree] = edge_new;
    vertex_2->edge_array[vertex_2->degree] = edge_new;

}
