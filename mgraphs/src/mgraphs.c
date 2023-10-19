#include <stdlib.h>
#include <stdbool.h>
#include <mgraphs.h>

/**
 * @brief Cria um grafo e inicializa suas variáveis
 *
 * @param is_graph_directed Grafo direcionado ou não.
 * @param n Quantidade de vértices a serem criados.
 */
Graph * create_graph(bool is_graph_directed, unsigned N){

	// N é o número de vértices do grafo a ser criado

	Graph *graph = malloc(sizeof(Graph));
	
	graph->total_vertex = N;
	graph->total_edge = N*N;
	graph->is_graph_directed = is_graph_directed;
	
	graph->edge_array = malloc(sizeof(Edge) * graph->total_edge);
	
	for(int i=0; i<graph->total_edge; i++){
		graph->edge_array[i].connect = 0;
		graph->edge_array[i].weight = 0;
	}
	
	graph->vertex_array = malloc(sizeof(Vertex)*n); 

	for(int i=0; i<n; i++){
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
	}

	return graph;
}

void insert_edge (Graph *graph, unsigned id1, unsigned id2, int weight){
	
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;
	
	if(graph->is_graph_directed){
		graph->edge_array[edge_pos1].connect = 1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = -1;
		graph->edge_array[edge_pos2].weight = weight;
	}else{
        if(graph->edge_array[edge_pos1].connect == 0){
            graph->graph_degree+=2;
            graph->vertex_array[id1].vertex_degree++;
            graph->vertex_array[id2].vertex_degree++;
        }

		graph->edge_array[edge_pos1].connect = 1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = 1;
		graph->edge_array[edge_pos2].weight = weight;
	}
}

void remove_edge (Graph * graph, unsigned id1, unsigned id2){
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;
	
	if(graph->is_graph_directed){
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}else{
        if(graph->edge_array[edge_pos1].connect == 1){
            graph->graph_degree-=2;
            graph->vertex_array[id1].vertex_degree--;
            graph->vertex_array[id2].vertex_degree--;
        }
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}
}

unsigned vertex_degree (Graph *graph, unsigned id){
	return graph->vertex_array[id].vertex_degree;
}

int graph_degree (Graph *graph) {
	int degree = 0;
	int counter = 0;
	if (graph->is_graph_weighted == false) {
		for (counter = 0; counter < graph->total_vertex; counter++) {
			degree += graph->vertex_array[counter].vertex_degree;
		}
	}
	else {
		for (counter = 0; counter < graph->total_edge; counter++) {
			degree += graph->edge_array[counter].weight;
		}
	}
	return degree;
}