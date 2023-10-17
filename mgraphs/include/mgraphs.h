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
	unsigned id; // Identificador do vértice.
	void *obj; // Objeto armazenado no vértice.
}typedef gvertex;

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
	int weight; // Peso do vértice
}typedef gedge;

/**
 * @brief Struct grafo.
 */
struct{
	unsigned degree; // Grau do grafo
	unsigned total_vertex; // Total de vertíces.
	unsigned total_edge; // Total de arestas na matriz (Incluindo vértices repetidos).
	bool directed; // Se o grafo é direcionado ou não.
	gedge *edge_array;
	gvertex *vertex_array;
}typedef ggraph;

//Funções de biblioteca

unsigned get_vertex_degree (ggraph *, unsigned); // Retorna o grau do vértice, recebe o id do vértice.
bool vertex_path_exists (ggraph *, unsigned, unsigned); // Retorna se existe um caminho entre 2 vértices.

void insert_edge (ggraph *, unsigned, unsigned, int); // Insere uma aresta no grafo, recebe o id de dois vértices e o peso da aresta.
void remove_edge (ggraph *, unsigned, unsigned); // Remove uma aresta do grafo, recebe o id de dois vértices.
void save_edge_neighbors (ggraph *, unsigned, int *); // Salva o id dos vértices vizinhos do vértice solicitado.

ggraph * create_graph (bool, int); // Cria um novo grafo
unsigned get_graph_degree (ggraph *); // Retorna o grau do grafo.    
bool is_graph_connect (ggraph *); // Retorna se o grafo é conexo.
bool is_graph_regular (ggraph *); // Retorna se o grafo é regular.
bool is_graph_complete (ggraph *); // Retorna se o grafo é completo.
void save_graph(ggraph *); // Salva o grafo em um arquivo csv padrão Gephi.

void depth_search (ggraph *); // Realiza uma busca em profundidade no grafo.
void breadth_search (ggraph *); // Realiza uma busca em largura no grafo.

#endif
