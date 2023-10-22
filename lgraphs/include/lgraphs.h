#ifndef LGRAPHS_H_
#define LGRAPHS_H_
    
    #include <stdlib.h>
    #include <stdbool.h>
    #include <math.h>
    #include <list.h>

    /**
     * @brief Struct vértice.
     */
    struct{
        unsigned id; // Identificador do vértice.
        void *obj; // Objeto armazenado no vértice.
        unsigned degree; //grau do vértice.
        list *edges_incident ; //lista de arestas ligadas ao vértice.
    }typedef Vertex;

    /**
     * @brief Struct arestas.
     */
    struct Edge{
        Vertex *vertex_left;
        Vertex *vertex_right;
        double weight; // Peso do vértice
    }typedef Edge;
    
    /**
     * @brief Struct grafo.
     */
    struct{
        unsigned degree; // Grau do grafo
        unsigned total_vertex; // Total de vertíces.
        unsigned total_edge; // Total de arestas possíveis.
        bool directed; // Se o grafo é direcionado ou não.
        Vertex *vertex_array;
        list *edges_list;
    }typedef Graph;

    //Funções de biblioteca

    unsigned vertex_degree (Graph *, unsigned); // Retorna o grau do vértice, recebe o id do vértice.
    bool vertex_path_exists (Graph *, unsigned, unsigned); // Retorna se existe um caminho entre 2 vértices.

    void edge_insert (Graph *, unsigned, unsigned, int); // Insere uma aresta no grafo, recebe o id de dois vértices e o peso da aresta.
    void edge_remove (Graph *, unsigned, unsigned); // Remove uma aresta do grafo, recebe o id de dois vértices.
    unsigned * save_vertex_neighbors (Graph *, unsigned); // Salva o id dos vértices vizinhos do vértice solicitado.
    Graph * graph_create (bool, unsigned); // Cria um novo grafo
    unsigned get_graph_degree (Graph *); // Retorna o grau do grafo.    
    bool is_graph_connect (Graph *); // Retorna se o grafo é conexo.
    bool is_graph_regular (Graph *); // Retorna se o grafo é regular.
    bool is_graph_complete (Graph *); // Retorna se o grafo é completo.
    bool save_graph(Graph *); // Salva o grafo em um arquivo csv padrão Gephi.

    void depth_search (Graph *); // Realiza uma busca em profundidade no grafo.
    void breadth_search (Graph *); // Realiza uma busca em largura no grafo.
    
    static unsigned real_total_edge(Graph *graph){
        return graph->degree / (unsigned) 2;  

    };


    static Edge * search_edge(list *list, int id1, int id2){
        lnode *node = NULL;
        Edge *edge = NULL;
        for(node;node != NULL; node = node->next){
            edge = node->obj_struct->obj_addr;

            if(edge->vertex_left->id == id1 || edge->vertex_right->id == id1){
                if(edge->vertex_left->id == id2 || edge->vertex_right->id == id2) return edge;
            }
        }

        return NULL;

    }

#endif
