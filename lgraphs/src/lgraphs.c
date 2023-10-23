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
    
    graph->degree -= 2;
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


unsigned graph_degree (Graph *graph) {
    return graph->degree;
}

SearchData_depth * main_depth_search(Graph *graph){
    unsigned total_vertex = graph->total_vertex;
    Vertex *vertex_array = graph->vertex_array;

    SearchData_depth *data = malloc(sizeof(SearchData_depth));
    
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

void depth_search(Vertex *v, unsigned *time, SearchData_depth *data){
    
    ++*time;
    data->discovery_time[v->id] = *time;

    Vertex *w = NULL;
    
    lnode *node = v->edges_incident->root;
    Edge *edge = NULL;

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

SearchData_breadth * main_breadth_search(Graph *graph){
    
    list *queue = list_create();

    unsigned total_vertex = graph->total_vertex;
    Vertex *vertex_array = graph->vertex_array;

    SearchData_breadth *data = malloc(sizeof(SearchData_breadth));
    data->visited_time = malloc(sizeof(SearchData_breadth) * total_vertex);
    data->level = malloc(sizeof(SearchData_breadth) * total_vertex);
    data->parent = malloc(sizeof(SearchData_breadth) * total_vertex);


    for(int i=0; i<total_vertex;i++){
        data->visited_time[i] = 0;
        data->level[i] = 0;
        data->parent[i] = -1;
    };

    unsigned time = 0;
    Vertex *v = NULL; 
    
    for(int i=0; i < total_vertex; i++){
        if(data->level[i] == 0){
            v = &vertex_array[i];
            ++time;  
            data->visited_time[i] = time;
            list_add_end(queue, &v->id, sizeof(unsigned)); 
            breadth_search(vertex_array, queue, data, &time);
        }
    };

    return data;
}


void breadth_search (Vertex *vertex_array, list *queue, SearchData_breadth *data, unsigned *time){
    Vertex *v= NULL;
    Vertex *w= NULL;
    Edge *edge = NULL;


    while(queue->size > 0){
        unsigned *id = queue->root->obj_struct->obj_addr;

        v = &vertex_array[*id];
        
        list_remove_begin(queue);
        
        lnode *node = v->edges_incident->root;

        while(node!=NULL){
            edge = node->obj_struct->obj_addr;

            if(edge->vertex_left->id != v->id){
                w = edge->vertex_left;
            }else{
                w = edge->vertex_right;
            }

            if(data->visited_time[w->id] == 0){
                //visitar aresta pai 

                data->parent[w->id] = v->id;
                data->level[w->id] = data->level[v->id] + 1;
                ++*time;
                data->visited_time[w->id] = *time;
                list_add_end(queue, &w->id, sizeof(unsigned)); 

            }else if(data->level[w->id] == (data->level[v->id] + 1)){
               //visitar aresta tio
            }else if(data->level[w->id] == (data->level[v->id] + 1) && data->parent[w->id] == data->parent[v->id] && data->visited_time[w->id] > data->visited_time[v->id]){
                //visitar aresta irmã
            }else if(data->level[w->id] == data->level[v->id] && data->parent[w->id] != data->parent[v->id] && data->visited_time[w->id] > data->visited_time[v->id]){
                //visitar aresta primo
            }
        
            node = node->next;
        }

    }

}

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

bool is_graph_connect(Graph *graph){
    SearchData_depth *data = main_depth_search(graph);

    unsigned count = 0;

    for(int i =0; i<graph->total_vertex; i++){
        if(data->parent[i] == -1){
            count++;
        }
    }

    if(count >1) return false;

    return true;
}
