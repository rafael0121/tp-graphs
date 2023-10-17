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

	}

	/**
	 * @brief Struct arestas.
	 */
	struct gedge{
		struct gvertex *vert_right; // Vértice a direita.
		struct gvertex *vert_left;  // Vértice a esquerda.
		unsigned weight;	    // Peso do vértice
	}

	/**
	 * @brief Struct grafo.
	 */
	struct graph{
		unsigned gdegree; // Grau do grafo.
		unsigned tvertex; // Total de vertíces.
		unsigned tedge;	  // Total de arestas.
		bool directed;	  // Se o grafo é direcionado ou não.

	}

	typedef struct gvertex;
	typedef struct gedge;


#endif
