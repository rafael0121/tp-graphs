#include <mgraphs.h>
#include <stdio.h>
#include <math.h>

void print_graph(Graph *graph){

    //Print Graph
	printf("\n\n");

	printf("     | ");
	for(int i = 0; i < graph->total_vertex; i++){
		printf("V%i | ", i);
		
	}
	int v = 0;
	for(int i = 0; i < graph->total_edge; i++){
		if((i % graph->total_vertex) == 0) printf("\n V%i  | ", v++);
		printf(" %i | ", graph->edge_array[i].connect);
	}
	
    printf("\n\n");
    //-------------------------

    //Print vertices degree
    for(int i=0; i<graph->total_vertex; i++){
        printf("V%i Grau = %d \n",i, vertex_degree(graph, i));       
    }

    printf("\n\n");
    //----------
        
    //Print vertices neighborhood
    for(int id=0; id<graph->total_vertex; id++){
        unsigned *neigh_array = save_vertex_neighbors(graph, id);

        printf("V%i - Γ[ ", id);
        for(int j=0; j<graph->vertex_array[id].degree;j++){
            printf("%i,", neigh_array[j]);
        }
        printf("\b]\n");
    }
    printf("\n\n");


    //----------
    
    //Print is_graph_regular;
    
    if(is_graph_regular(graph)){
        printf("O grafo é regular.");
    }else{
        printf("O grafo NÃO é regular.");

    }

    printf("\n\n");
    //----------
    
    //Print is_graph_complete;
    
    if(is_graph_complete(graph)){
        printf("O grafo é completo.");
    }else{
        printf("O grafo NÃO é completo.");

    }

    printf("\n\n");

}

int main(){
	unsigned n =2;
	Graph *graph = graph_create(false, n);
	
	edge_insert(graph, 0, 1, 0);
    

	print_graph(graph);
    
    save_graph(graph);

}
