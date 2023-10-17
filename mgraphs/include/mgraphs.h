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
	int weight; // Peso do vértice
}typedef Edge;

/**
 * @brief Struct grafo.
 */
struct{
	unsigned degree; // Grau do grafo
	unsigned total_vertex; // Total de vertíces.
	unsigned total_edge; // Total de arestas na matriz (Incluindo vértices repetidos).
	bool directed; // Se o grafo é direcionado ou não.
	Edge *edge_array;
	Vertex *vertex_array;
}typedef Graph;

//Funções de biblioteca

unsigned get_vertex_degree (Graph *, unsigned); // Retorna o grau do vértice, recebe o id do vértice.
bool vertex_path_exists (Graph *, unsigned, unsigned); // Retorna se existe um caminho entre 2 vértices.

void insert_edge (Graph *, unsigned, unsigned, int); // Insere uma aresta no grafo, recebe o id de dois vértices e o peso da aresta.
void remove_edge (Graph *, unsigned, unsigned); // Remove uma aresta do grafo, recebe o id de dois vértices.
void save_edge_neighbors (Graph *, unsigned, int *); // Salva o id dos vértices vizinhos do vértice solicitado.

Graph * create_graph (bool, unsigned); // Cria um novo grafo
unsigned get_graph_degree (Graph *); // Retorna o grau do grafo.    
bool is_graph_connect (Graph *); // Retorna se o grafo é conexo.
bool is_graph_regular (Graph *); // Retorna se o grafo é regular.
bool is_graph_complete (Graph *); // Retorna se o grafo é completo.
void save_graph(Graph *); // Salva o grafo em um arquivo csv padrão Gephi.

void depth_search (Graph *); // Realiza uma busca em profundidade no grafo.
void breadth_search (Graph *); // Realiza uma busca em largura no grafo.

#endif
