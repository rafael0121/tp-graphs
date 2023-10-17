/**
 * @brief Biblioteca de grafos.
 *
 */

#ifndef GRAPHS_H
#define GRAPHS_H

	#include <stdlib.h>
	#include <bool.h>

	/**
	 * @brief Struct vértice.
	 */
	struct gvertex{
		unsigned id; 	  // id Identificador do vértice.
		unsigned vdegree; // Grau do vértice.
		void *obj;	  // Objeto armazenado no vértice.

	}typedef gvertex;

	/**
	 * @brief Struct arestas.
	 */
	struct gedge{
		struct gvertex *vert_right; // Vértice a direita.
		struct gvertex *vert_left;  // Vértice a esquerda.
		int weight;	    // Peso do vértice
	}struct gedge;

	/**
	 * @brief Struct grafo.
	 */
	struct ggraph{
		unsigned total_vertex; 	// Total de vertíces.
		unsigned total_edge;	  	// Total de arestas.
		    bool directed;	// Se o grafo é direcionado ou não.
		
	}

	//Funções de biblioteca
	
	  ggraph * create_graph (bool, int);			
	unsigned edge_insert (ggraph *, unsigned, unsigned);	// Insere uma aresta no grafo, recebe o id de dois vértices.
	     int edge_remove (ggraph *, unsigned, unsigned);	// Remove uma aresta do grafo, recebe o id de dois vértices.
	unsigned vertex_degree (ggraph *, unsigned);		// Retorna o grau do vértice, recebe o id do vértice.
	    void vertex_neigh (ggraph *, unsigned, int *);	// Salva o id dos vértices vizinhos do vértice solicitado.
	unsigned graph_degree (ggraph *);			// Retorna o grau do grafo.
	    bool graph_connect (ggraph *);			// Retorna se o grafo é conexo.
	    bool graph_regular (ggraph *);			// Retorna se o grafo é regular.
	    bool graph_complete (ggraph *);			// Retorna se o grafo é completo.
	    void depth_search (ggraph *);			// realiza uma busca em profundidade no grafo.
	    void breadth_search (ggraph *);			// realiza uma busca em largura no grafo.
	    bool vertex_path (ggraph *, unsigned, unsigned);	// Retorna se existe um caminho entre 2 vértices.
	    void ggraph_save(ggraph *);				// Salva o grafo em um arquivo csv padrão Gephi.
            :w

	

	
#endif
