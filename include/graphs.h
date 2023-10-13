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
		unsigned id; 	 	// Identificador do vértice.
		unsigned vdegree;	// Grau do vértice.
		unsigned obj_size;	// Tamanho do objeto.
		    void *obj;	  	// Objeto armazenado no vértice.
		
	}

	/**
	 * @brief Struct arestas.
	 */
	struct gedge{
		unsigned weight;	     	// Peso da aresta.
		  struct gvertex *vert_right;	// Vértice a direita.
		  struct gvertex *vert_left; 	// Vértice a esquerda.
	}

	/**
	 * @brief Struct grafo.
	 */
	struct ggraph{
		unsigned gdegree; 		// Grau do grafo.
		unsigned vertex_total; 		// Total de vertíces.
		unsigned edge_total;	  	// Total de arestas.
		    bool directed;	  	// Se o grafo é direcionado ou não.

		  struct list *vertex_table;	// Tabela de vértices;
		  struct list *edge_table;	// Tabela de arestas.
	}
	
	typedef struct gvertex;
	typedef struct gedge;
	typedef struct ggraph;

	ggraph * create_graph(gvertex *vertex, bool directed, ){
		ggraph *graph = malloc(sizeof(ggraph));
		
		graph->gdegree = 0;
		graph->total_vertex = 0;
		graph->total_edge = 0;
		
		graph->vertex_table = create_list(vertex);
	}

	
#endif
