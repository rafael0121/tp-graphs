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

        printf("\n");
    }

}


int main(){
    Graph *graph;
    int n = 10;

    graph = graph_create(graph, 10);
    
    edge_insert(graph, 1, 2, 0);
    edge_insert(graph, 2, 3, 0);
    edge_insert(graph, 3, 4, 0);
    edge_insert(graph, 3, 4, 0);
    edge_insert(graph, 3, 4, 0);
    

    print_graph(graph);
    
}
