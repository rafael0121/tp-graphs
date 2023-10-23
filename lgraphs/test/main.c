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
    int n = 10;

    graph = graph_create(graph, 6);
    
    edge_insert(graph, 0, 1, 0);
    edge_insert(graph, 1, 2, 0);
    edge_insert(graph, 2, 3, 0);
    edge_insert(graph, 3, 4, 0);
    edge_insert(graph, 4, 5, 0);
    
    SearchData *data = main_depth_search(graph);

    for(int i=0;i<graph->total_vertex;i++){
        
        printf("\n\n\n%i ---------- \n", i);
        printf("End time: %d \n", data->end_time[i]);
        printf("Discovery time: %d \n", data->discovery_time[i]);
        printf("Parent: %d \n", data->parent[i]);

    }

    print_graph(graph);

    save_graph(graph);
    
}
