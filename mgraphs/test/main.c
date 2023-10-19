#include <mgraphs.h>
#include <stdio.h>
#include <math.h>

void print_graph(Graph *graph)
{

    //Print Graph
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
	//----------

	//Print searched vertex and search table;

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
	//----------

	//Print if graph is connect.
	if(is_graph_connect(graph))
		printf("\n\nGrafo conexo");
	else 
		printf("\n\nGrafo desconexo");

}

int main(){
	unsigned n = 10;
	Graph *graph = graph_create(false, n);
	
	edge_insert(graph, 6, 2, 0);
	edge_insert(graph, 3, 2, 0);
	edge_insert(graph, 5, 2, 0);
	edge_insert(graph, 1, 2, 0);
    

	print_graph(graph);
    
    save_graph(graph);

}
