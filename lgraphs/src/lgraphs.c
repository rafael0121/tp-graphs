#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <lgraphs.h>

Graph * graph_create(bool directed, unsigned n){
	Graph *graph = malloc(sizeof(Graph));

    graph->total_vertex = n;
    graph->total_edge = n * (n-1);
	graph->directed = directed;
	graph->degree = 0;
    
    graph->vertex_array = malloc(sizeof(Vertex) * n);

    for(int i=0; i<n; i++){
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
		graph->vertex_array[i].degree = 0;
        graph->vertex_array[i].edges_incident = list_create();
	}

    graph->edges_list = list_create();
    
    return graph;
}

void edge_insert(Graph *graph, unsigned id1, unsigned id2, int weight){
    
    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];
    
    if(search_edge(vertex_1->edges_incident, id1, id2) != NULL) return; 

    Edge *edge = malloc(sizeof(Edge));
    
    edge->vertex_left = vertex_1;
    edge->vertex_right = vertex_2;
    edge->weight = weight;

    list_add_begin(graph->edges_list, edge, sizeof(Edge));
    
    list_add_end(vertex_1->edges_incident, edge, sizeof(Edge));
    list_add_end(vertex_2->edges_incident, edge, sizeof(Edge));

    vertex_1->degree++;
    vertex_2->degree++;
    graph->degree += 2;
}

void edge_remove (Graph *graph, unsigned id1, unsigned id2){
    Vertex *vertex_1 = &graph->vertex_array[id1];
    Vertex *vertex_2 = &graph->vertex_array[id2];

    Edge *edge = search_edge(vertex_1->edges_incident, id1, id2);

    if(edge != NULL){
        list_remove(vertex_1->edges_incident, list_search_node(vertex_1->edges_incident, edge));     
        list_remove(vertex_2->edges_incident, list_search_node(vertex_2->edges_incident, edge));     
        list_remove(graph->edges_list, list_search_node(graph->edges_list, edge));     

    };
}

unsigned vertex_degree (Graph *g, unsigned id) {
    return (g->vertex_array[id].degree);
}

unsigned *save_vertex_neighbors(Graph *graph, unsigned id)
{   
    Vertex *vertex = &graph->vertex_array[id];

	unsigned size = vertex->degree;
	unsigned *neigh = malloc(sizeof(unsigned) * size);

    lnode *node = vertex->edges_incident->root;
    Edge *edge = NULL;

    int j = 0;
	while(node != NULL){
        edge = node->obj_struct->obj_addr;
        
        if(edge->vertex_left->id != id){
            neigh[j] = edge->vertex_left->id;
            j++;
        }else{
            neigh[j] = edge->vertex_right->id;
            j++;
        }
        node = node->next;
	};

	return neigh;
}

SearchData * main_depth_search(Graph *graph){
    unsigned total_vertex = graph->total_vertex;
    Vertex *vertex_array = graph->vertex_array;

    SearchData *data = malloc(sizeof(SearchData));
    
    data->end_time = malloc(total_vertex * sizeof(unsigned));
    data->discovery_time = malloc(total_vertex * sizeof(unsigned));
    data->parent = malloc(total_vertex * sizeof(int));
    
    for(int i=0; i<total_vertex;i++){
        data->end_time[i] = 0;
        data->discovery_time[i] = 0;
        data->parent[i] = -1;
    };

    unsigned time = 0;

    for(int i=0;i<total_vertex; i++){
        if(data->end_time[i] == 0){
            depth_search(&vertex_array[i], &time, data);           
        };
    };

    return data;
}

void depth_search(Vertex *v, unsigned *time, SearchData *data){
    
    ++*time;
    data->discovery_time[v->id] = *time;

    Vertex *w;
    
    lnode *node = v->edges_incident->root;
    Edge *edge;

    while(node != NULL){
        edge = node->obj_struct->obj_addr;

        if(edge->vertex_left->id != v->id){
            w = edge->vertex_left;
        }else{
            w = edge->vertex_right;
        }

        if(data->discovery_time[w->id] == 0){
            // visitar aresta de árvore (v, w)
            data->parent[w->id] = v->id; 
            depth_search(w, time, data);           

        }else if(data->end_time[w->id] == 0 && data->parent[v->id] != w->id){
            // visitar aresta de retorno (v, w)
        }
        node = node->next;
    }

    ++*time;
    data->end_time[v->id] = *time; 
};

/**
 * @brief Salva o grafo em um arquivo.
 *
 * @param graph Grafo a ser salvo.
 */
bool save_graph(Graph *graph)
{
	FILE *file;

	file = fopen("list_graph.csv", "w");

    unsigned * neigh;
    Vertex *vertex;

    for(unsigned id = 0; id < graph->total_vertex; id++){
        neigh = save_vertex_neighbors(graph, id);
        vertex = &graph->vertex_array[id];

        fprintf(file, "%i", id);
        for(int j = 0; j < vertex->degree; j++){
            fprintf(file, ";%i", neigh[j]);        
        }

        fprintf(file, "\n");
    }

    fclose(file);

	return true;
}

/**
 * @brief Retorna true se o grafo é completo e false se não for
 *
 * @param graph Grafo a ser analisado.
 */
bool is_graph_complete(Graph *graph)
{
	if ((graph->degree / (unsigned) 2) == (graph->total_vertex * (graph->total_vertex - 1)) / 2)
	{
		return true;
	}
	else
		return false;
}

/**
 * @brief Retorna grau do grafo e atualiza o grau do grafo.
 *
 * @param graph Grafo a ser analisado.
 */
unsigned get_graph_degree (Graph *graph) {
    Vertex *vertex;
    unsigned degree = 0;
    for(unsigned id = 0; id < graph->total_vertex; id++){
        vertex = &graph->vertex_array[id];
        degree += vertex->degree;
    }
    graph->degree = degree;
}