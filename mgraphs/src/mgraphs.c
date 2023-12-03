#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mgraphs.h>
#include <queue.h>
#include <math.h>
#include <limits.h>

#define INFINITY_DOUBLE INFINITY

/**
 * @brief Cria um grafo e inicializa suas variáveis
 *
 * @param directed Grafo direcionado ou não.
 * @param n Quantidade de vértices a serem criados.
 */
Graph *graph_create(bool directed, unsigned n)
{

	Graph *graph = malloc(sizeof(Graph));

	graph->total_vertex = n;
	graph->total_edge = n * n;
	graph->directed = directed;

	graph->edge_array = malloc(sizeof(Edge) * graph->total_edge);

	for (int i = 0; i < graph->total_edge; i++)
	{
		graph->edge_array[i].connect = 0;
		graph->edge_array[i].weight = 0;
	}

	graph->vertex_array = malloc(sizeof(Vertex) * n);

	for (int i = 0; i < n; i++)
	{
		graph->vertex_array[i].id = i;
		graph->vertex_array[i].obj = NULL;
		graph->vertex_array[i].degree = 0;
	}

	return graph;
}

void edge_insert(Graph *graph, unsigned id1, unsigned id2, int weight)
{

	int edge_pos2 = graph->total_vertex * id1 + id2;
	int edge_pos1 = graph->total_vertex * id2 + id1;

	if (graph->directed)
	{
		graph->edge_array[edge_pos1].connect = -1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = 1;
		graph->edge_array[edge_pos2].weight = weight;
	}
	else
	{
		if (graph->edge_array[edge_pos1].connect == 0)
		{
			graph->degree += 2;
			graph->vertex_array[id1].degree++;
			graph->vertex_array[id2].degree++;
		}

		graph->edge_array[edge_pos1].connect = 1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = 1;
		graph->edge_array[edge_pos2].weight = weight;
	}
}

void edge_remove(Graph *graph, unsigned id1, unsigned id2)
{
	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;

	if (graph->directed)
	{
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}
	else
	{
		if (graph->edge_array[edge_pos1].connect == 1)
		{
			graph->degree -= 2;
			graph->vertex_array[id1].degree--;
			graph->vertex_array[id2].degree--;
		}
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}
}

unsigned vertex_degree(Graph *graph, unsigned id)
{
	return graph->vertex_array[id].degree;
}

/**
 * @brief Realiza uma busca em largura no grafo buscando por id de vértice. Retorna uma struct com o vértice solicitado e a tabela gerada pela pesquisa.
 *
 * @param graph Grafo.
 * @param id Vértice a ser buscado
 */
SearchData *breadth_search(Graph *graph, int id)
{
	int numVertex = graph->total_vertex;

	SearchData *data = malloc(sizeof(SearchData));
	data->dataTable = (int **)malloc(3 * sizeof(int *));
	for (int i = 0; i < 3; i++)
	{
		data->dataTable[i] = (int *)malloc(numVertex * sizeof(int));
	}
	int t = 0;
	Queue *vertexQueue = createQueue(numVertex);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i != 2)
			{
				data->dataTable[i][j] = t;
			}
			else
			{
				data->dataTable[i][j] = -1;
			}
		}
	}

	int lv;
	while (search_lv(data, numVertex, &lv))
	{
		t++;
		data->dataTable[0][lv] = t;
		enqueue(vertexQueue, graph->vertex_array[lv]);

		while (!isEmpty(vertexQueue))
		{
			Vertex v = dequeue(vertexQueue);
			int *w = malloc(v.degree * sizeof(int));
			for (int i = 0, j = 0; i < numVertex; i++)
			{
				if (graph->edge_array[(v.id * numVertex) + i].connect == 1)
				{
					w[j] = i;
					j++;
				}
			}
			for (int i = 0; i < v.degree; i++)
			{
				if (data->dataTable[2][v.id] == -1)
				{
					data->dataTable[2][v.id] = 0;
				}
				if (data->dataTable[0][w[i]] == 0)
				{
					data->dataTable[2][w[i]] = v.id;
					data->dataTable[1][w[i]] = data->dataTable[1][v.id] + 1;
					data->dataTable[0][w[i]] = ++t;
					enqueue(vertexQueue, graph->vertex_array[w[i]]);
					if (graph->vertex_array[w[i]].id == id)
						data->result = &graph->vertex_array[w[i]];
				}
			}
		}
	}
	return data;
}

/**
 * @brief Realiza uma busca em profundidade no grafo buscando por id de vértice. Retorna uma struct com o vértice solicitado e a tabela gerada pela pesquisa.
 *
 * @param graph Grafo.
 * @param id Vértice a ser buscado
 */
SearchData *depth_search(Graph *graph, int searchId)
{
	int numVertex = graph->total_vertex;

	SearchData *data = malloc(sizeof(SearchData));
	data->dataTable = (int **)malloc(3 * sizeof(int *));
	for (int i = 0; i < 3; i++)
	{
		data->dataTable[i] = (int *)malloc(numVertex * sizeof(int));
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i != 2)
			{
				data->dataTable[i][j] = 0;
			}
			else
			{
				data->dataTable[i][j] = -1;
			}
		}
	}

	int t = 0;
	int id = 3;
	while (search_lv(data, numVertex, &id))
	{
		data = depth_search_recursive(id, data, &t, graph, searchId);
	}
	return data;
}

SearchData *depth_search_recursive(int id, SearchData *data, int *t, Graph *graph, int searchId)
{
	++*t;
	data->dataTable[0][id] = *t;
	int *w = vertex_neighbors(id, graph);
	if (graph->vertex_array[id].degree != 0)
	{
		for (int i = 0; i < graph->vertex_array[id].degree; i++)
		{
			if (data->dataTable[0][w[i]] == 0)
			{
				data->dataTable[2][w[i]] = id;
				data = depth_search_recursive(w[i], data, t, graph, searchId);
			}
			if (searchId == id)
			{
				data->result = &graph->vertex_array[id];
			}
		}
	}
	++*t;
	data->dataTable[1][id] = *t;
	return data;
}

/**
 * @brief Realiza uma busca por todos os vértices vizinhos ao vértice requisitado.
 *
 * @param id Vértice a ser verificado.
 * @param graph Grafo a ser utilizado.
 */
int *vertex_neighbors(int id, Graph *graph)
{
	int *w = malloc(graph->vertex_array[id].degree * sizeof(int));
	for (int i = 0, j = 0; i < graph->total_vertex; i++)
		if (graph->edge_array[(id * graph->total_vertex) + i].connect == 1)
		{
			w[j] = i;
			j++;
		}
	return w;
}

/**
 * @brief Retorna true se o grado passado é conexo e false se não for.
 *
 * @param g Grafo a ser analisado.
 */
bool is_graph_connect(Graph *g)
{
	SearchData *src = breadth_search(g, 0);
	for (int i = 0; i < g->total_vertex; i++)
		if (src->dataTable[2][i] == -1)
			return false;

	return true;
}

bool search_lv(SearchData *table, int len, int *callback)
{
	for (int i = 0; i < len; i++)
		if (table->dataTable[0][i] == 0)
		{
			*callback = i;
			return true;
		}

	return false;
}

unsigned *save_vertex_neighbors(Graph *graph, unsigned id)
{
	unsigned size = graph->vertex_array[id].degree;
	unsigned *neigh = malloc(sizeof(unsigned) * size);

	int j = 0;
	for (int i = 0; i < graph->total_vertex; i++)
	{
		if (graph->edge_array[(id * graph->total_vertex) + i].connect == 1)
		{
			neigh[j] = i;
			j++;
		}
	}

	return neigh;
}

bool is_graph_complete(Graph *graph)
{
	if (real_total_edge(graph) == (graph->total_vertex * (graph->total_vertex - 1)) / 2)
	{
		return true;
	}
	else
		return false;
}

bool is_graph_regular(Graph *graph)
{
	int first_degree = graph->vertex_array[0].degree;
	int tam = graph->total_vertex;

	for (int i = 1; i < tam; i++)
	{
		if (first_degree != graph->vertex_array[i].degree)
		{
			return false;
		}
	}

	return true;
}

unsigned graph_degree(Graph *graph)
{
	return graph->degree;
}

bool save_graph(Graph *graph)
{
	FILE *file;

	file = fopen("matrix_graph.csv", "w");

	int aux = graph->total_vertex;
	int count = 0;

	while (aux > 0)
	{
		aux /= 10;
		count++;
	}
	int alg = ceil(log10(graph->total_vertex)) + 1 * sizeof(char);

	char vertex_name[alg];

	for (int i = 0; i < graph->total_vertex; i++)
	{
		sprintf(vertex_name, ";V%d", i);
		fprintf(file, vertex_name);
	}

	fprintf(file, "\n");

	for (int id = 0; id < graph->total_vertex; id++)
	{
		sprintf(vertex_name, "V%d", id);
		fprintf(file, vertex_name);

		for (int j = 0; j < graph->total_vertex; j++)
		{
			char edge_connect[5];
			sprintf(edge_connect, ";%i", graph->edge_array[(id * graph->total_vertex) + j].connect);
			fprintf(file, edge_connect);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return true;
}

bool checkValidation(unsigned *array, unsigned v) {
	if(array[v] != NULL) {
		return true;
	} else {
		return false;
	}
}

unsigned *newValidation(unsigned *array, unsigned n, unsigned root) {
	array = malloc(sizeof(unsigned)*n); 
	for(unsigned i = 0; i < n; i++) 
		array[i] = NULL;
	array[root] = 1;
	return array;
}

BellmanData *bellmanFord(Graph *graph, unsigned root)
{

	if (root < 0)
	{
		root = 0;
	}

	BellmanData *data = malloc(sizeof(BellmanData));

	data->distance = malloc(sizeof(double) * graph->total_vertex);
	data->predecessor = malloc(sizeof(int) * graph->total_vertex);

	for (unsigned i = 0; i < graph->total_vertex; i++)
	{
		data->distance[i] = INFINITY_DOUBLE;
		data->predecessor[i] = -1;
	}

	data->distance[root] = 0.0;
	bool repet = true;
	unsigned *validationList = newValidation(validationList, graph->total_vertex, root);

	while (repet)
	{
		repet = false;
		for (int i = 0; i < graph->total_vertex; i++)
		{
			for (int j = 0; j < graph->total_vertex; j++)
			{
				if (checkValidation(validationList, i) && graph->edge_array[(i * graph->total_vertex) + j].connect == 1)
				{
					validationList[j] = 1;
					if (data->distance[j] > data->distance[i] + graph->edge_array[(i * graph->total_vertex) + j].weight)
					{
						repet = true;
						data->distance[j] = data->distance[i] + graph->edge_array[(i * graph->total_vertex) + j].weight;
						data->predecessor[j] = i;
					}
				}
			}
		}
	}

	return data;
}

void bellmanFordforAll(Graph *graph)
{
	for (unsigned j = 0; j < graph->total_vertex; j++)
	{
		BellmanData *bellman = NULL;
		bellman = bellmanFord(graph, j);

		printf("Bellman para Vertice de id: %d:\nDistancia: [", j);
		for (unsigned i = 0; i < graph->total_vertex; i++)
		{
			printf(" {%f}", bellman->distance[i]);
		}
		printf(" ]");
		printf("\nPredecessor: [");
		for (unsigned i = 0; i < graph->total_vertex; i++)
		{
			printf(" {%d}", bellman->predecessor[i]);
		}
		printf(" ]\n\n\n");
	}
}