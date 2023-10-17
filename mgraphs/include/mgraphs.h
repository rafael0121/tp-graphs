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
	}typedef gvertex;

	/**
	 * @brief Struct arestas.
	 */
	struct{
		int connect;	// Informa se os vértices estão conectados 1 = conectado/aresta de saída,
				// 0 = desconectados e -1 aresta de entrada.
		int weight;	// Peso do vértice
	}typedef gedge;

	/**
	 * @brief Struct grafo.
	 */
	struct{
		unsigned total_vertex;		// Total de vertíces.
		unsigned total_edge;		// Total de arestas na matriz (Incluindo vértices repetidos).
		    bool directed;		// Se o grafo é direcionado ou não.
						//
		   gedge *edge_array;
		 gvertex *vertex_array;
	}typedef ggraph;

	//Funções de biblioteca
	
	  ggraph * create_graph (bool, int);			
	    void edge_insert (ggraph *, unsigned, unsigned, int);	// Insere uma aresta no grafo, recebe o id de dois vértices e o peso
									// da aresta.
	     int edge_remove (ggraph *, unsigned, unsigned);		// Remove uma aresta do grafo, recebe o id de dois vértices.
	unsigned vertex_degree (ggraph *, unsigned);			// Retorna o grau do vértice, recebe o id do vértice.
	    void vertex_neigh (ggraph *, unsigned, int *);		// Salva o id dos vértices vizinhos do vértice solicitado.
	unsigned graph_degree (ggraph *);				// Retorna o grau do grafo.
	    bool graph_connect (ggraph *);				// Retorna se o grafo é conexo.
	    bool graph_regular (ggraph *);				// Retorna se o grafo é regular.
	    bool graph_complete (ggraph *);				// Retorna se o grafo é completo.
	    void depth_search (ggraph *);				// realiza uma busca em profundidade no grafo.
	    void breadth_search (ggraph *);				// realiza uma busca em largura no grafo.
	    bool vertex_path (ggraph *, unsigned, unsigned);		// Retorna se existe um caminho entre 2 vértices.
	    void ggraph_save(ggraph *);					// Salva o grafo em um arquivo csv padrão Gephi.

	

	
#endif
