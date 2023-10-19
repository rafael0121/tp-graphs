#include <stdlib.h>
#include <stdbool.h>
#include <mgraphs.h>

/**
 * @brief Cria um grafo e inicializa suas variáveis
 *
 * @param directed Grafo direcionado ou não.
 * @param n Quantidade de vértices a serem criados.
 */
Graph * graph_create(bool directed, unsigned n){

	Graph *graph = malloc(sizeof(Graph));
	
	graph->total_vertex = n;
	graph->total_edge = n * n;
	graph->directed = directed;
	graph->degree = 0;

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

void edge_insert (Graph *graph, unsigned id1, unsigned id2, int weight){
	
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;
	
	if(graph->directed){
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


void edge_remove (Graph * graph, unsigned id1, unsigned id2){
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;
	
	if(graph->directed){
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

bool is_graph_complete (Graph *graph){
	if (graph->total_edge == (graph->total_vertex * (graph->total_edge - 1))/2)
	{
		return true;
	}
	else return false;
}

bool is_graph_regular (Graph *graph){
	int first_degree = graph->vertex_array[0].vertex_degree;
	int tam = graph->total_vertex;
	int aux;

	for ( int i = 1; i < tam; i++)
	{
		if (first_degree != graph->vertex_array[i])
		{
			return false;
		}
		
	}
	
	return  true;

}

