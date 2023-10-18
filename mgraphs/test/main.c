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
	int n =10;
	Graph *graph = create_graph(false, n);
	
	insert_edge(graph, 6, 2, 0);

	print_graph(graph);

}
