#include <mgraphs.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
     
void print_graph(Graph *graph)
{
    int v;

    //Print Graph
	printf("\n\n");

	printf("     | ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("V%i  | ", i);
	}

    Edge *print_edge;

	for (int line = 0; line < graph->total_vertex; line++)
    {
        printf("\n V%i  | ", line);

        for (int column = 0; column < graph->total_vertex; column++)
        {
            print_edge = get_edge(line, column, graph);

            if (print_edge != NULL)
                printf("%.1f | ", print_edge->weight);
        }
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
	for (int j = 0; j < graph->total_vertex; j++)
	{
		printf("[  %d  ]", src->dataTable[0][j]);
	}
	printf("\n[Nivel]   ");
	for (int j = 0; j < graph->total_vertex; j++)
	{
		printf("[  %d  ]", src->dataTable[1][j]);
	}
	printf("\n[ Pai ]   ");
	for (int j = 0; j < graph->total_vertex; j++)
	{
		printf("[  %d ]", src->dataTable[2][j]);
	}
	//----------
   
	//Print searched vertex and search table with depht;

	SearchData *src2 = depth_search(graph, 2);

	printf("\n\nID: %d\n\n", src2->result->id);

	printf("Resultado tabela: \n");

	printf("Vertices: ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("[  %d  ]", i);
	}
	printf("\n[ TD  ]   ");
	for (int j = 0; j < graph->total_vertex; j++)
	{
		printf("[  %d  ]", src2->dataTable[0][j]);
	}
	printf("\n[ TT  ]   ");
	for (int j = 0; j < graph->total_vertex; j++)
	{
		printf("[  %d  ]", src2->dataTable[1][j]);
	}
	printf("\n[ Pai ]   ");
	for (int j = 0; j < graph->total_vertex; j++)
	{
		printf("[  %d ]", src2->dataTable[2][j]);
	}
	//----------
    
	//Print if graph is connect.
	if(is_graph_connect(graph))
		printf("\n\nGrafo conexo");
	else 
		printf("\n\nGrafo desconexo");

    //----------
    printf("\n\n");

    for(int id=0; id<graph->total_vertex; id++){
        unsigned *neigh_array = save_vertex_neighbors(graph, id);

        printf("V%i - Γ[ ", id);
        for(int j=0; j<graph->vertex_array[id].degree;j++){
            printf("%i,", neigh_array[j]);
        }
        printf("\b]\n");
    }

    //Print Floyd Marshall
	printf("\n\n");

    ShortestPath *path = floydwarshall(graph);

	printf("     | ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("V%i  | ", i);
	}
	v = 0;
	for (int i = 0; i < graph->total_edge; i++)
	{
		if ((i % graph->total_vertex) == 0)
			printf("\n V%i  | ", v++);

            printf("%.1f | ", path->dist_array[i]);

	}
    
    //Print dijkstra.
	printf("\n\n");

	v = 5;

    path = dijkstra(graph, v);

	printf("     | ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("V%i  | ", i);
	}
	
	printf("\n V%i  | ", v);

    for (int i = 0; i < graph->total_vertex; i++)
	{
            printf("%.1f | ", path->dist_array[i]);
	}
    
    
}


void gen_graph ()
{
    clock_t start, end;
    double cpu_time_used;
    int m = 3;
    unsigned n[m][m];
	Graph *graph = graph_create(true, m*m);
    
    int v = 0;
    //gerar matrix
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            n[i][j] = v;
            v++;
        }
    }

    
    start = clock();
    // gerar grafo
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if (j < m-1) { 
                edge_insert(graph, n[i][j], n[i][j+1], 1);
                edge_insert(graph, n[i][j+1], n[i][j], 1);
            } 

            if (i < m-1) {
                edge_insert(graph, n[i][j], n[i+1][j], 1);
                edge_insert(graph, n[i+1][j], n[i][j], 1);
            }
        }
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n\n%f\n", cpu_time_used);

    //Print A*.
	printf("\n\n");

	unsigned src = 0;
    unsigned targ = 5;

    ShortestPath *path;
    path = astar(graph, src, targ, m, n);

	printf("     | ");
	for (int i = 0; i < graph->total_vertex; i++)
	{
		printf("V%i  | ", i);
	}
	
	printf("\n V%i  | ", src);

    for (int i = 0; i < graph->total_vertex; i++)
	{
            printf("%.1f | ", path->dist_array[i]);
	}
    
    //print_graph(graph);
}

int main(){
    srand(time(NULL));
    


    gen_graph();

    

    
}
