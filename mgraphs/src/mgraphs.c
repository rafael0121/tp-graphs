#include <stdlib.h>
#include <stdbool.h>
#include <mgraphs.h>
#include <queue.h>

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
	graph->degree = 0;

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
	}

	return graph;
}

void edge_insert(Graph *graph, unsigned id1, unsigned id2, int weight)
{

	int edge_pos1 = graph->total_vertex * id1 + id2;
	int edge_pos2 = graph->total_vertex * id2 + id1;

	if (graph->directed)
	{
		graph->edge_array[edge_pos1].connect = 1;
		graph->edge_array[edge_pos1].weight = weight;

		graph->edge_array[edge_pos2].connect = -1;
		graph->edge_array[edge_pos2].weight = weight;
	}
	else
	{
		if (graph->edge_array[edge_pos1].connect == 0)
		{
			graph->graph_degree += 2;
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
			graph->graph_degree -= 2;
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
void save_vertex_neighbors(Graph *graph, unsigned id, unsigned *neigh)
{

	unsigned size = graph->vertex_array[id].degree;
	neigh = malloc(sizeof(unsigned) * size);

	int j = 0;
	for (int i = 0; i < graph->total_vertex; i++)
	{
		if (graph->edge_array[(id * graph->total_vertex) + i].connect == 1)
		{
			neigh[j] = i;
			j++;
		}
	}
}

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
				if(data->dataTable[2][v.id] == -1) {
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

bool is_graph_connect(Graph *g) {
	SearchData *src = breadth_search(g, 0);
	for(int i = 0; i < g->total_vertex; i++)
		if(src->dataTable[2][i] == -1)
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
