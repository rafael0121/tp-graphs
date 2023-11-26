#include <lgraphs.h>
#include <stdio.h>
#include <time.h>


void print_graph(Graph *graph){
    
    printf("\n\n");

    //print list
    unsigned * neigh;
    Vertex *vertex;

    for(unsigned id = 0; id < graph->total_vertex; id++){
        neigh = save_vertex_neighbors(graph, id);
        vertex = &graph->vertex_array[id];

        printf("%i ->", id);
        for(int j = 0; j < vertex->degree; j++){
            printf(" %i ->", neigh[j]);         
        }
        
        printf("   Grau = %d ", vertex->degree);

        printf("\n");
    }

    printf("\nGrau do grafo = %d \n", get_graph_degree(graph));

}


int main(){
    Graph *graph = NULL;
    int n = 5;

    graph = graph_create(graph, 5);
    
    edge_insert(graph, 0, 1, 0);
    edge_insert(graph, 2, 1, 0);
    
    SearchData_depth *data = main_depth_search(graph);

    for(int i=0;i<graph->total_vertex;i++){
        printf("\n\n\n%i ---------- \n", i);
        printf("End time: %d \n", data->end_time[i]);
        printf("Discovery time: %d \n", data->discovery_time[i]);
        printf("Parent: %d \n", data->parent[i]);

    }
    
    printf("\n\n------------------- Pesquisa em largura\n\n");

    SearchData_breadth *data_b = main_breadth_search(graph);
    

    for(int i=0;i<graph->total_vertex;i++){
        printf("\n\n\n%i ---------- \n", i);
        printf("Tempo de visita: %d \n", data_b->visited_time[i]);
        printf("Nível: %d \n", data_b->level[i]);
        printf("Parent: %d \n", data_b->parent[i]);

    }
    
    if(is_graph_connect(graph)){
        printf("\nO grafo é conexo");
    }else{
        printf("\nO grafo NÃO é conexo");
    }

    if(is_graph_complete(graph)) {
        printf("\n\nGrafo completo");
    } else {
        printf("\n\nGrafo incompleto");
    }

    print_graph(graph);

    int flag = 0;

    do {
        // Show menu
        printf("\nMenu:\n");
        printf("1. Dijkstra\n");
        printf("2. Bellman-Ford\n");
        printf("3. Floyd-Warshall\n");
        printf("0. Finish\n");
        printf("Choose an option: ");
        scanf("%d", &flag);

        //switch case
        switch (flag) {
            case 1:
                printf("Você escolheu a Opção 1.\n");
                // código Dijkstra
                break;
            case 2:
                printf("Você escolheu a Opção 2.\n");
                // código Bellman-Ford
                break;
            case 3:
                printf("Você escolheu a Opção 3.\n");
                // código Floyd-Warshall
                break;
            case 0:
                printf("Leaving the program. See you later!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }

    } while (flag != 0);

    /*
    // Marcar o tempo inicial
    clock_t inicio = clock();

    // Marcar o tempo final
    clock_t fim = clock();

    // Calcular o tempo decorrido em segundos
    double tempoDecorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Exibir o tempo decorrido
    printf("A função levou %.6f segundos para ser executada.\n", tempoDecorrido);
    */

    save_graph(graph);
    
}
