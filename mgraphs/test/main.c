#include <mgraphs.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

void print_graph(Graph *graph)
{
    int v;

	// Print Graph
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

	// Print searched vertex and search table;

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

void bellmanford ()
{
	unsigned n = 10000;
	Graph *graph = graph_create(true, n);

	/*edge_insert(graph, 0, 1, 6);
	edge_insert(graph, 0, 2, 5);
	edge_insert(graph, 0, 3, 5);
	edge_insert(graph, 1, 4, -1);
	edge_insert(graph, 2, 1, -2);
	edge_insert(graph, 2, 4, 1);
	edge_insert(graph, 3, 2, -2);
	edge_insert(graph, 3, 5, -1);
	edge_insert(graph, 4, 6, 3);
	edge_insert(graph, 5, 6, 3);*/

	edge_insert(graph, 44, 17, -96);
    edge_insert(graph, 93, 34, 58);
    edge_insert(graph, 71, 48, -8);
    edge_insert(graph, 56, 8, -27);
    edge_insert(graph, 79, 24, 39);
    edge_insert(graph, 11, 62, 79);
    edge_insert(graph, 3, 86, -47);
    edge_insert(graph, 64, 31, 62);
    edge_insert(graph, 23, 77, -10);
    edge_insert(graph, 38, 65, -71);
    edge_insert(graph, 12, 87, 1);
    edge_insert(graph, 46, 68, 37);
    edge_insert(graph, 2, 33, -26);
    edge_insert(graph, 18, 91, 76);
    edge_insert(graph, 40, 89, -52);
    edge_insert(graph, 95, 46, 3);
    edge_insert(graph, 88, 57, 66);
    edge_insert(graph, 72, 76, -60);
    edge_insert(graph, 15, 83, 53);
    edge_insert(graph, 52, 20, 29);
    edge_insert(graph, 60, 50, -11);
    edge_insert(graph, 50, 61, -44);
    edge_insert(graph, 8, 98, 41);
    edge_insert(graph, 37, 73, -98);
    edge_insert(graph, 94, 55, -17);
    edge_insert(graph, 84, 25, 81);
    edge_insert(graph, 33, 16, -84);
    edge_insert(graph, 75, 19, -31);
    edge_insert(graph, 97, 47, 7);
    edge_insert(graph, 69, 4, 85);
    edge_insert(graph, 19, 80, -15);
    edge_insert(graph, 89, 59, -22);
    edge_insert(graph, 26, 12, 88);
    edge_insert(graph, 13, 74, -56);
    edge_insert(graph, 54, 36, 67);
    edge_insert(graph, 45, 81, -69);
    edge_insert(graph, 36, 70, 34);
    edge_insert(graph, 59, 29, -97);
    edge_insert(graph, 73, 7, 9);
    edge_insert(graph, 22, 63, -2);
    edge_insert(graph, 35, 41, 50);
    edge_insert(graph, 7, 90, -45);
    edge_insert(graph, 98, 16, 72);
    edge_insert(graph, 9, 66, -35);
    edge_insert(graph, 92, 37, -64);
    edge_insert(graph, 76, 55, 11);
    edge_insert(graph, 30, 87, -59);
    edge_insert(graph, 31, 85, 92);
    edge_insert(graph, 64, 99, 13);
    edge_insert(graph, 19, 81, 70);
    edge_insert(graph, 88, 56, -66);
    edge_insert(graph, 42, 78, 23);
    edge_insert(graph, 54, 61, 93);
    edge_insert(graph, 58, 1, 44);
    edge_insert(graph, 84, 38, -83);
    edge_insert(graph, 8, 98, 5);
    edge_insert(graph, 32, 89, -19);
    edge_insert(graph, 40, 23, -75);
    edge_insert(graph, 27, 15, 76);
    edge_insert(graph, 18, 91, -56);
    edge_insert(graph, 83, 47, 91);
    edge_insert(graph, 71, 49, -23);
    edge_insert(graph, 50, 13, 51);
    edge_insert(graph, 28, 66, -30);
    edge_insert(graph, 59, 10, 89);
    edge_insert(graph, 45, 77, -36);
    edge_insert(graph, 2, 74, 12);
    edge_insert(graph, 69, 85, -68);
    edge_insert(graph, 5, 53, 15);
    edge_insert(graph, 38, 33, -90);
    edge_insert(graph, 20, 51, 55);
    edge_insert(graph, 84, 3, -95);
    edge_insert(graph, 95, 68, 80);
    edge_insert(graph, 26, 43, -8);
    edge_insert(graph, 63, 29, 79);
    edge_insert(graph, 47, 96, 59);
    edge_insert(graph, 17, 76, -32);
    edge_insert(graph, 37, 98, -77);
    edge_insert(graph, 16, 30, -58);
    edge_insert(graph, 79, 11, 46);
    edge_insert(graph, 48, 74, -99);
    edge_insert(graph, 6, 45, 32);
    edge_insert(graph, 42, 31, -67);
    edge_insert(graph, 13, 57, 25);
    edge_insert(graph, 65, 55, -18);
    edge_insert(graph, 21, 98, 85);
    edge_insert(graph, 3, 70, -47);
    edge_insert(graph, 46, 64, 1);
    edge_insert(graph, 28, 96, -24);
    edge_insert(graph, 77, 19, 38);
    edge_insert(graph, 91, 32, -74);
    edge_insert(graph, 12, 9, -7);
    edge_insert(graph, 1, 25, 7);
    edge_insert(graph, 90, 58, -100);
    edge_insert(graph, 64, 21, 34);
    edge_insert(graph, 37, 51, -56);
    edge_insert(graph, 98, 10, 12);
    edge_insert(graph, 30, 75, -51);
    edge_insert(graph, 69, 88, 67);
    edge_insert(graph, 27, 55, 95);
    edge_insert(graph, 14, 97, -55);
    edge_insert(graph, 74, 8, 59);
    edge_insert(graph, 61, 40, -90);
    edge_insert(graph, 22, 85, 77);
    edge_insert(graph, 44, 65, -11);
    edge_insert(graph, 72, 35, 52);
    edge_insert(graph, 16, 79, -83);
    edge_insert(graph, 99, 52, -26);
    edge_insert(graph, 42, 6, 93);
    edge_insert(graph, 87, 24, -32);
    edge_insert(graph, 3, 47, 66);
    edge_insert(graph, 38, 91, -20);
    edge_insert(graph, 70, 19, 29);
    edge_insert(graph, 31, 82, 48);
    edge_insert(graph, 495, 743, -952);
    edge_insert(graph, 264, 685, -786);
    edge_insert(graph, 538, 34, 972);
    edge_insert(graph, 754, 248, 607);
    edge_insert(graph, 781, 48, -119);
    edge_insert(graph, 319, 684, -602);
    edge_insert(graph, 643, 912, -578);
    edge_insert(graph, 12, 956, -673);
    edge_insert(graph, 132, 447, 609);
    edge_insert(graph, 491, 757, 92);
    edge_insert(graph, 873, 9, -762);
    edge_insert(graph, 521, 292, -453);
    edge_insert(graph, 724, 528, -788);
    edge_insert(graph, 469, 611, 685);
    edge_insert(graph, 716, 346, -312);
    edge_insert(graph, 657, 511, 388);
    edge_insert(graph, 649, 122, -491);
    edge_insert(graph, 267, 956, -209);
    edge_insert(graph, 893, 621, 334);
    edge_insert(graph, 397, 850, 782);
    edge_insert(graph, 504, 8, -905);
    edge_insert(graph, 879, 121, 267);
    edge_insert(graph, 112, 418, 913);
    edge_insert(graph, 830, 307, -645);
    edge_insert(graph, 794, 681, 877);
    edge_insert(graph, 668, 348, 265);
    edge_insert(graph, 754, 255, -43);
    edge_insert(graph, 444, 841, 7);
    edge_insert(graph, 111, 772, 876);
    edge_insert(graph, 289, 37, -281);
    edge_insert(graph, 259, 780, -27);
    edge_insert(graph, 575, 11, -830);
    edge_insert(graph, 476, 631, 893);
    edge_insert(graph, 989, 12, -1000);
    edge_insert(graph, 126, 750, 406);
    edge_insert(graph, 491, 785, -656);
    edge_insert(graph, 349, 123, -748);
    edge_insert(graph, 525, 860, 621);
    edge_insert(graph, 384, 799, 756);
    edge_insert(graph, 602, 364, -99);
    edge_insert(graph, 365, 471, 40);
    edge_insert(graph, 21, 937, -739);
    edge_insert(graph, 758, 291, 750);
    edge_insert(graph, 437, 978, 320);
    edge_insert(graph, 913, 684, -21);
    edge_insert(graph, 157, 901, 296);
    edge_insert(graph, 330, 31, -192);
    edge_insert(graph, 211, 840, -502);
    edge_insert(graph, 134, 698, 666);
    edge_insert(graph, 376, 295, -668);
    edge_insert(graph, 938, 122, 876);
    edge_insert(graph, 822, 505, 642);
    edge_insert(graph, 492, 921, -246);
    edge_insert(graph, 653, 490, -543);
    edge_insert(graph, 317, 895, -690);
    edge_insert(graph, 496, 828, -424);
    edge_insert(graph, 392, 807, 940);
    edge_insert(graph, 701, 635, 1000);
    edge_insert(graph, 511, 160, 185);
    edge_insert(graph, 999, 227, 523);
    edge_insert(graph, 345, 896, -668);
    edge_insert(graph, 348, 701, -20);
    edge_insert(graph, 575, 789, -675);
    edge_insert(graph, 141, 657, 866);
    edge_insert(graph, 782, 82, 895);
    edge_insert(graph, 830, 557, -992);
    edge_insert(graph, 270, 784, 314);
    edge_insert(graph, 771, 298, 881);
    edge_insert(graph, 520, 910, -804);
    edge_insert(graph, 35, 693, 219);
    edge_insert(graph, 249, 906, -797);
    edge_insert(graph, 513, 389, 618);
    edge_insert(graph, 872, 375, 755);
    edge_insert(graph, 177, 785, -366);
    edge_insert(graph, 360, 585, -836);
    edge_insert(graph, 265, 763, 917);
    edge_insert(graph, 408, 730, -971);
    edge_insert(graph, 812, 474, -425);
    edge_insert(graph, 74, 841, 257);
    edge_insert(graph, 619, 482, -626);
    edge_insert(graph, 448, 919, 85);
    edge_insert(graph, 739, 611, 35);
    edge_insert(graph, 558, 939, -995);
    edge_insert(graph, 161, 482, -305);
    edge_insert(graph, 958, 406, 942);
    edge_insert(graph, 541, 660, 948);
    edge_insert(graph, 5243, 7624, -8901);
    edge_insert(graph, 3721, 689, 1500);
    edge_insert(graph, 9234, 1875, -3425);
    edge_insert(graph, 5634, 189, 6500);
    edge_insert(graph, 8176, 2543, -7123);
    edge_insert(graph, 981, 6421, -8910);
    edge_insert(graph, 2978, 7194, 8293);
    edge_insert(graph, 6347, 8654, -5674);
    edge_insert(graph, 4321, 8912, 7000);
    edge_insert(graph, 1765, 2315, -9123);
    edge_insert(graph, 5623, 8756, -2312);
    edge_insert(graph, 1234, 789, 5678);
    edge_insert(graph, 5421, 3718, -9832);
    edge_insert(graph, 6892, 4876, 2345);
    edge_insert(graph, 8123, 1234, -7890);
    edge_insert(graph, 9876, 5432, 8765);
    edge_insert(graph, 4532, 8653, -4321);
    edge_insert(graph, 2314, 5432, 7654);
    edge_insert(graph, 7892, 2987, -1023);
    edge_insert(graph, 8762, 9823, 4567);
    edge_insert(graph, 5432, 1245, -4321);
    edge_insert(graph, 9872, 6543, 6789);
    edge_insert(graph, 5643, 2314, -7654);
    edge_insert(graph, 9012, 7865, 4321);
    edge_insert(graph, 5432, 6789, -1234);
    edge_insert(graph, 8123, 5678, 9012);
    edge_insert(graph, 9876, 1234, -7890);
    edge_insert(graph, 8765, 4321, 5678);
    edge_insert(graph, 6543, 7890, -1234);
    edge_insert(graph, 2345, 8765, 9012);
    edge_insert(graph, 4567, 5432, -6789);
    edge_insert(graph, 7890, 9012, 1234);
    edge_insert(graph, 9876, 2345, -8765);
    edge_insert(graph, 5432, 5678, 9012);
    edge_insert(graph, 1234, 6789, -2345);
    edge_insert(graph, 8765, 9012, 3456);
    edge_insert(graph, 4567, 7890, -5678);
    edge_insert(graph, 2345, 1234, 8765);
    edge_insert(graph, 7890, 5678, -9012);
    edge_insert(graph, 4321, 3456, 7890);
    edge_insert(graph, 6789, 9012, -1234);
    edge_insert(graph, 5678, 7890, 2345);
    edge_insert(graph, 1234, 4567, -6789);
    edge_insert(graph, 4321, 2345, -5678);
    edge_insert(graph, 8765, 5678, 9012);
    edge_insert(graph, 3456, 7890, -1234);
    edge_insert(graph, 8765, 9012, -7890);
    /*edge_insert(graph, 2345, 5678, 1234);
    edge_insert(graph, 9012, 8765, 5678);
    edge_insert(graph, 5678, 9012, 8765);
    edge_insert(graph, 2345, 7890, -5678);
    edge_insert(graph, 4321, 5678, 9012);
    edge_insert(graph, 8765, 2345, -7890);
    edge_insert(graph, 7890, 9012, 5678);
    edge_insert(graph, 5678, 7890, -2345);
    edge_insert(graph, 1234, 4567, 6789);
    edge_insert(graph, 8765, 7890, 5678);
    edge_insert(graph, 3456, 1234, -5678);
    edge_insert(graph, 5678, 9012, 2345);
    edge_insert(graph, 7890, 4567, -6789);
    edge_insert(graph, 2345, 5678, 9012);
    edge_insert(graph, 9012, 7890, -1234);
    edge_insert(graph, 4321, 2345, 5678);
    edge_insert(graph, 8765, 5678, -9012);
    edge_insert(graph, 3456, 7890, 1234);
    edge_insert(graph, 5678, 4321, -7890);
    edge_insert(graph, 9012, 8765, 2345);
    edge_insert(graph, 1234, 7890, -5678);
    edge_insert(graph, 8765, 9012, 7890);
    edge_insert(graph, 2345, 5678, -1234);
    edge_insert(graph, 9012, 8765, -5678);
    edge_insert(graph, 5678, 7890, 2345);
    edge_insert(graph, 2345, 7890, -8765);
    edge_insert(graph, 4321, 5678, 9012);
    edge_insert(graph, 8765, 2345, -7890);
    edge_insert(graph, 7890, 9012, 5678);
    edge_insert(graph, 5678, 7890, -2345);
    edge_insert(graph, 9015, 2348, -7893);
    edge_insert(graph, 9016, 2349, -7894);
    edge_insert(graph, 9017, 2350, -7895);
    edge_insert(graph, 9018, 2351, -7896);
    edge_insert(graph, 9019, 2352, -7897);*/

	// print_graph(graph);

	// save_graph(graph);

	/*BellmanData *bellman = bellmanFord(graph, -1);

	printf("Bellman:\nDistancia: [");
	for(int i=0; i<graph->total_vertex; i++) {
		printf(" {%u}", bellman->distance[i]);
	}
	printf("]");
	printf("\nPredecessor: [");
	for(int i=0; i<graph->total_vertex; i++) {
		printf(" {%d}", bellman->predecessor[i]);
	}
	printf("]\n");*/

	clock_t inicio = clock();

    bellmanFordforAll(graph);

    clock_t fim = clock();

    double tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo levado para processar a função: %f segundos\n", tempoTotal);

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
