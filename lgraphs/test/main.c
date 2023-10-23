#include <lgraphs.h>
#include <stdio.h>


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

}


int main(){
    Graph *graph = NULL;
    int n = 5;

    graph = graph_create(graph, 5);
    
    edge_insert(graph, 0, 1, 0);
    edge_insert(graph, 0, 2, 0);
    edge_insert(graph, 1, 2, 0);
    edge_insert(graph, 1, 3, 0);
    edge_insert(graph, 2, 3, 0);
    edge_insert(graph, 2, 4, 0);
    edge_insert(graph, 3, 4, 0);
    
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

    print_graph(graph);

    save_graph(graph);
    
}
