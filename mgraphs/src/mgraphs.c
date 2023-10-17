#include <stdlib.h>
#include <stdbool.h>
#include <mgraphs.h>

/**
 * @brief Cria um grafo e inicializa suas variáveis
 *
 * @param directed Grafo direcionado ou não.
 * @param n Quantidade de vértices a serem criados.
 */
ggraph * create_graph(bool directed, int n){

	ggraph *graph = malloc(sizeof(ggraph));
	
	graph->total_vertex = n;
	graph->total_edge = n*n;
	graph->directed = directed;
	
	graph->edge_array = malloc(sizeof(gedge) * graph->total_edge);
	
	for(int i=0; i<graph->total_edge; i++){
		graph->edge_array[i].connect = 0;
		graph->edge_array[i].weight = 0;
	}
	
	graph->vertex_array = malloc(sizeof(gvertex)*n); 

	for(int i=0; i<n; i++){
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
	}

	return graph;
}
