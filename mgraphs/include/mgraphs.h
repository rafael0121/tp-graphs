/**
 * @brief Biblioteca de grafos.
 *
 */

#ifndef GRAPHS_H
#define GRAPHS_H

	#include <stdlib.h>
	#include <stdbool.h>

	/**
	 * @brief Struct vértice.
	 */
	struct{
		unsigned id; 	  // id Identificador do vértice.
		void *obj;	  // Objeto armazenado no vértice.
	}typedef Vertex;

	/**
	 * @brief Struct arestas.
	 */
	struct{
		int connect;	// Informa se os vértices estão conectados 1 = conectado/aresta de saída,
				// 0 = desconectados e -1 aresta de entrada.
		int weight;	// Peso do vértice
	}typedef Edge;

	/**
	 * @brief Struct grafo.
	 */
	struct{
		unsigned total_vertex;		// Total de vertíces.
		unsigned total_edge;		// Total de arestas na matriz (Incluindo vértices repetidos).
		    bool directed;		// Se o grafo é direcionado ou não.
						//
		   Edge *edge_array;
		 Vertex *vertex_array;
	}typedef Graph;

	//Funções de biblioteca
	
	  Graph * create_graph (bool, int);			
	    void edge_insert (Graph *, unsigned, unsigned, int);	// Insere uma aresta no grafo, recebe o id de dois vértices e o peso
									// da aresta.
	    void edge_remove (Graph *, unsigned, unsigned);		// Remove uma aresta do grafo, recebe o id de dois vértices.
	unsigned vertex_degree (Graph *, unsigned);			// Retorna o grau do vértice, recebe o id do vértice.
	    void vertex_neigh (Graph *, unsigned, int *);		// Salva o id dos vértices vizinhos do vértice solicitado.
	unsigned graph_degree (Graph *);				// Retorna o grau do grafo.
	    bool graph_connect (Graph *);				// Retorna se o grafo é conexo.
	    bool graph_regular (Graph *);				// Retorna se o grafo é regular.
	    bool graph_complete (Graph *);				// Retorna se o grafo é completo.
	    void depth_search (Graph *);				// realiza uma busca em profundidade no grafo.
	    void breadth_search (Graph *);				// realiza uma busca em largura no grafo.
	    bool vertex_path (Graph *, unsigned, unsigned);		// Retorna se existe um caminho entre 2 vértices.
	    void Graph_save(Graph *);					// Salva o grafo em um arquivo csv padrão Gephi.

	

	
#endif
