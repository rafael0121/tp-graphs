#include <stdlib.h>
#include <stdio.h>
#include <list.h>
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
        graph->vertex_array[i].edges_incident = list_create();
	}

    graph->edges_list = list_create();
    
    return graph;
}

void edge_insert(Graph *graph, unsigned id1, unsigned id2, int weight){
    
    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];
    
    Edge *edge = malloc(sizeof(Edge));
    
    edge->vertex_left = vertex_1;
    edge->vertex_right = vertex_2;
    edge->weight = weight;

    list_add_begin(graph->edges_list, edge, sizeof(Edge));
    
    list_add_end(vertex_1->edges_incident, edge, sizeof(Edge));
    list_add_end(vertex_2->edges_incident, edge, sizeof(Edge));

}

void edge_remove (Graph *graph, unsigned id1, unsigned id2){
    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];

    Edge *edge = search_edge(vertex_1->edges_incident, id1, id2);

    if(edge != NULL){
        list_remove(vertex_1->edges_incident, list_search_node(vertex_1->edges_incident, edge));     
        list_remove(vertex_2->edges_incident, list_search_node(vertex_2->edges_incident, edge));     
        list_remove(graph->edges_list, list_search_node(graph->edges_list, edge));     

    };
}
