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
	
	graph->vertex_array = malloc(sizeof(Vertex)*N); 

	for(int i=0; i<N; i++){
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
	}

	return graph;
}

void edge_insert (Graph *graph, unsigned id1, unsigned id2, int weight){
	
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;
	
	if(graph->is_graph_directed){
		graph->edge_array[edge_pos1].connect = 1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = -1;
		graph->edge_array[edge_pos2].weight = weight;
	}else{
		graph->edge_array[edge_pos1].connect = 1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = 1;
		graph->edge_array[edge_pos2].weight = weight;
	}
}

void edge_remove (Graph * graph, unsigned id1, unsigned id2){
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;
	
	if(graph->is_graph_directed){
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}else{
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}
}

unsigned vertex_degree (Graph *graph, unsigned id){
	int degree = 0;
	int array_pos = graph->total_vertex * id;

	for(int i=0; i<graph->total_vertex; i++){
		degree += graph->edge_array[array_pos + i].connect;
	}

	return degree;
}
