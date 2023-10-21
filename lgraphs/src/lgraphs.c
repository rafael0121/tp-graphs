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
        graph->vertex_array[i].edge_array = calloc(n, sizeof(void));
	}
    
    return graph;
}

void edge_insert(Graph *graph, unsigned id1, unsigned id2, int weight){
    
    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];
    
    if(vertex_1->edge_array[id2] != NULL) return;

    Edge *edge_new = malloc(sizeof(Edge));
    
    edge_new->weight = weight;
    edge_new->vertex_left = &graph->vertex_array[id1];
    edge_new->vertex_right = &graph->vertex_array[id2];

    vertex_1->edge_array[id2] = edge_new;
    vertex_2->edge_array[id1] = edge_new;

    vertex_1->degree++;
    vertex_2->degree++;

}

void edge_remove (Graph *graph, unsigned id1, unsigned id2){
    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];

    if(vertex_1->edge_array[id2] == NULL) return;


}


unsigned * save_vertex_neighbors (Graph * graph, unsigned id1){
    Vertex vertex = graph->vertex_array[id1];

	unsigned size = vertex.degree;
	unsigned *neigh = malloc(sizeof(unsigned) * size);

    Edge *edge;
    for(int i = 0; i < graph->total_vertex; i++){
        if(vertex.edge_array[i] == NULL) continue;
        edge = vertex.edge_array[i];
        neigh[i] = edge->vertex_left->id != id1 ? edge->vertex_left->id : edge->vertex_right->id;
    }

    return neigh;
}


