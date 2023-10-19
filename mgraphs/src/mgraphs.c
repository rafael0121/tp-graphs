#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mgraphs.h>
#include <math.h>

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
        graph->vertex_array[i].degree = 0;
	}

	return graph;
}

void edge_insert (Graph *graph, unsigned id1, unsigned id2, int weight){
	
	int edge_pos2 = graph->total_vertex * id1 + id2;
	int edge_pos1 = graph->total_vertex * id2 + id1;
	
	if(graph->directed){
		graph->edge_array[edge_pos1].connect = -1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = 1;
		graph->edge_array[edge_pos2].weight = weight;
	}else{
        if(graph->edge_array[edge_pos1].connect == 0){
            graph->degree+=2;
            graph->vertex_array[id1].degree++;
            graph->vertex_array[id2].degree++;
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
            graph->degree-=2;
            graph->vertex_array[id1].degree--;
            graph->vertex_array[id2].degree--;
        }
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}
}

unsigned vertex_degree (Graph *graph, unsigned id){
	return graph->vertex_array[id].degree;
}

unsigned * save_vertex_neighbors (Graph * graph, unsigned id){
    unsigned size = graph->vertex_array[id].degree;
    unsigned *neigh = malloc(sizeof(unsigned) * size);

    int j = 0;
    for(int i=0; i<graph->total_vertex; i++){
        if(graph->edge_array[(id * graph->total_vertex) + i].connect == 1){
            neigh[j] = i;
            j++;
        }
    }

    return neigh;
}

bool is_graph_complete (Graph *graph){
	if (real_total_edge(graph) == ( graph->total_vertex * (graph->total_vertex - 1))/2)
	{
		return true;
	}
	else return false;
}

bool is_graph_regular (Graph *graph){
	int first_degree = graph->vertex_array[0].degree;
	int tam = graph->total_vertex;

	for ( int i = 1; i < tam; i++)
	{
		if (first_degree != graph->vertex_array[i].degree)
		{
			return false;
		}
		
	}
	
	return  true;

}

bool save_graph(Graph *graph){
    FILE *file;   
    
    file = fopen("graph.csv", "w");

    int aux = graph->total_vertex;
    int count = 0;

    while(aux>0){
        aux /= 10;
        count++;
    }
    int alg = ceil(log10(graph->total_vertex))+1*sizeof(char);

    char vertex_name[alg]; 

    for(int i = 0; i < graph->total_vertex; i++){
        sprintf(vertex_name, ";V%d", i);
        fprintf(file, vertex_name);
    }

    fprintf(file, "\n");

    for(int id = 0; id < graph->total_vertex; id++){
        sprintf(vertex_name, "V%d", id);
        fprintf(file, vertex_name);
   
        for(int j = 0; j<graph->total_vertex; j++){
            char edge_connect[5];
            sprintf(edge_connect, ";%i", graph->edge_array[(id * graph->total_vertex) + j].connect);
            fprintf(file, edge_connect);
        }
        fprintf(file, "\n");
    }
    
    return true;
}
