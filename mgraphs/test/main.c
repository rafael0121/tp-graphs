#include <mgraphs.h>
#include <stdio.h>

void print_graph(ggraph *graph){

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
	int n =10;
	ggraph *graph = create_graph(false, n);
	
	edge_insert(graph, 6, 2, 0);

	print_graph(graph);

}
