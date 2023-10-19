#include <mgraphs.h>
#include <stdio.h>

void print_graph(Graph *graph)
{

	printf("\n\n");

	printf("     | ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("V%i | ", i);
	}
	int v = 0;
	for (int i = 0; i < graph->total_edge; i++)
	{
		if ((i % graph->total_vertex) == 0)
			printf("\n V%i  | ", v++);
		printf(" %i | ", graph->edge_array[i].connect);
	}

	printf("\n\n");
}

int main()
{
	unsigned n = 10;
	Graph *graph = graph_create(false, n);

	edge_insert(graph, 6, 2, 0);
	edge_insert(graph, 3, 2, 0);
	edge_insert(graph, 5, 2, 0);
	edge_insert(graph, 1, 2, 0);

	print_graph(graph);

	printf("\nResultado: \n");

	SearchData *src = breadth_search(graph, 2);

	printf("\nID: %d\n\n", src->result->id);

	printf("Resultado tabela: \n");

	printf("Vertices: ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("[  %d  ]", i);
	}
	printf("\n[  L  ]   ");
	for (int j = 0; j < 10; j++)
	{
		printf("[  %d  ]", src->dataTable[0][j]);
	}
	printf("\n[Nivel]   ");
	for (int j = 0; j < 10; j++)
	{
		printf("[  %d  ]", src->dataTable[1][j]);
	}
	printf("\n[ Pai ]   ");
	for (int j = 0; j < 10; j++)
	{
		printf("[  %d ]", src->dataTable[2][j]);
	}

	if(is_graph_connect(graph))
		printf("\n\nGrafo conexo");
	else 
		printf("\n\nGrafo desconexo");

	printf("\n\n %d", vertex_degree(graph, 2));
	printf("\n\n %d", vertex_degree(graph, 6));
	printf("\n\n %d", vertex_degree(graph, 3));
	printf("\n\n %d", vertex_degree(graph, 5));
	printf("\n\n %d", vertex_degree(graph, 1));
}
