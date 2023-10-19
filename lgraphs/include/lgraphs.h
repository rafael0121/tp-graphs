#ifndef LGRAPHS_H_
#define LGRAPHS_H_
    
    #include <stdlib.h>
    #include <stdbool.h>
    #include <math.h>

    typedef struct Vertex Vertex;

    /**
     * @brief Struct arestas.
     */
    struct{
        Vertex *vertex_left;
        Vertex *vertex_right;
        double weight; // Peso do vértice
    }typedef Edge;

    /**
     * @brief Struct vértice.
     */
    struct Vertex{
        unsigned id; // Identificador do vértice.
        void *obj; // Objeto armazenado no vértice.
        unsigned degree; //grau do vértice.
        Edge *edge_array; //lista de arestas ligadas ao vértice.
    };

    
    /**
     * @brief Struct grafo.
     */
    struct{
        unsigned degree; // Grau do grafo
        unsigned total_vertex; // Total de vertíces.
        unsigned total_edge; // Total de arestas.
        bool directed; // Se o grafo é direcionado ou não.
        Vertex *vertex_array;
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
    
#endif
