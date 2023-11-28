/**
 * @brief Biblioteca de grafos matriz.
 */

#ifndef MGRAPHS_H
#define MGRAPHS_H

    #include <stdlib.h>
    #include <stdbool.h>
    #include <math.h>
    #include <limits.h>
    /**
     * @brief Struct vértice.
     */
    struct{
        unsigned id; // Identificador do vértice.
        void *obj; // Objeto armazenado no vértice.
        unsigned degree; //grau do vértice.
    }typedef Vertex;

    /**
     * @brief Struct arestas.
     */
    struct{
        int connect;
        /*
        A variável connect informa se os vértices estão conectados:
        -> -1: aresta de entrada.
        -> 0: vértices desconectados.
        -> 1: vértices conectados / aresta de saída.
        */
        float weight; // Peso do vértice
    }typedef Edge;

    /**
     * @brief Struct grafo.
     */
    struct{
        unsigned degree; // Grau do grafo
        unsigned total_vertex; // Total de vertíces.
        unsigned total_edge; // Total de arestas possível na matriz (Incluindo vértices repetidos).
        bool directed; // Se o grafo é direcionado ou não.
        Edge *edge_array;
        Vertex *vertex_array;
    }typedef Graph;

  /**
   * @brief Struct de pesquisa em grafo.
  */
  struct {
    Vertex *result;
    int **dataTable;
  }typedef SearchData;
    
    struct {
        float *dist_array;
        Graph *graph;
    } typedef ShortestPath;

//Funções de biblioteca

    unsigned vertex_degree (Graph *, unsigned); // Retorna o grau do vértice, recebe o id do vértice.
    bool vertex_path_exists (Graph *, unsigned, unsigned); // Retorna se existe um caminho entre 2 vértices.

    void edge_insert (Graph *, unsigned, unsigned, int); // Insere uma aresta no grafo, recebe o id de dois vértices e o peso da aresta.
    void edge_remove (Graph *, unsigned, unsigned); // Remove uma aresta do grafo, recebe o id de dois vértices.
    unsigned * save_vertex_neighbors (Graph *, unsigned); // Salva o id dos vértices vizinhos do vértice solicitado.
    Graph * graph_create (bool, unsigned); // Cria um novo grafo
    unsigned graph_degree (Graph *); // Retorna o grau do grafo.    
    bool is_graph_connect (Graph *); // Retorna se o grafo é conexo.
    bool is_graph_regular (Graph *); // Retorna se o grafo é regular.
    bool is_graph_complete (Graph *); // Retorna se o grafo é completo.
    bool save_graph(Graph *); // Salva o grafo em um arquivo csv padrão Gephi.

    SearchData * depth_search (Graph *, int); // Realiza uma busca em profundidade no grafo.
    SearchData * breadth_search (Graph *, int); // Realiza uma busca em largura no grafo e busca por um vértice.

    bool search_lv(SearchData *, int, int *); // Retorna os níveis/td 0 das buscas.
    SearchData *depth_search_recursive(int , SearchData *, int *, Graph *, int); // Chamada recursiva para a busca em profundidade.
    int *vertex_neighbors (int, Graph *g); // Retorna um array com os vizinhos de um vértice.

    static unsigned real_total_edge(Graph *graph){
        return graph->degree / (unsigned) 2;  
    };
    
    //Floyd-Warshall
    ShortestPath * floydwarshall(Graph *graph);

#endif
