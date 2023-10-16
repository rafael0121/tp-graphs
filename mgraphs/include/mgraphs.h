/**
 * @brief Biblioteca de grafos.
 *
 */

#ifndef GRAPHS_H
#define GRAPHS_H

	#include <stdlib.h>
	#include <stdbool.h>
	
	/**
	 * @brief Struct grafo.
	 */
	struct{
		unsigned gdegree; 		// Grau do grafo.
		unsigned total_vertex; 		// Total de vertíces.
		unsigned total_edge;	  	// Total de arestas.
		    bool directed;	  	// Se o grafo é direcionado ou não.
		     int *matrix ;		// Linha de arestas.
	}typedef ggraph;
	

	

	
#endif
