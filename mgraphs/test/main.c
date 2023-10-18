#include <mgraphs.h>
#include <stdio.h>

void print_graph(Graph *graph){

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

}

int main(){
	unsigned n =10;
	Graph *graph = graph_create(false, n);
	
	edge_insert(graph, 6, 2, 0);
	edge_insert(graph, 3, 2, 0);
	edge_insert(graph, 5, 2, 0);
	edge_insert(graph, 1, 2, 0);
    

	print_graph(graph);

    printf("\n\n %d", vertex_degree(graph, 2));
    printf("\n\n %d", vertex_degree(graph, 6));
    printf("\n\n %d", vertex_degree(graph, 3));
    printf("\n\n %d", vertex_degree(graph, 5));
    printf("\n\n %d", vertex_degree(graph, 1));
}
