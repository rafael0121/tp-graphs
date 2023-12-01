#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mgraphs.h>
#include <queue.h>
#include <math.h>

/*
 * #################################################################################
 * ----------------------- START Basic Graphs Operations ---------------------------
 * #################################################################################
 */

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
		graph->edge_array[i].weight = INFINITY;
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
		graph->edge_array[edge_pos2].connect = 1;

		graph->edge_array[edge_pos1].connect = -1;

		graph->edge_array[edge_pos2].weight = weight;

        graph->degree += 2;
        graph->vertex_array[id1].degree++;

	} else {
		graph->edge_array[edge_pos1].connect = 1;

		graph->edge_array[edge_pos2].connect = 1;

		graph->edge_array[edge_pos1].weight = weight;
		graph->edge_array[edge_pos2].weight = weight;
        
        graph->degree += 2;
        graph->vertex_array[id1].degree++;
        graph->vertex_array[id2].degree++;
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

unsigned * save_vertex_neighbors(Graph *graph, unsigned id)
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

unsigned graph_degree (Graph *graph) {
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

/**
 * @brief Retorna aresta correspondente a abstração
 * de uma matriz com linhas e colunas do vetor de 
 * arestas.
 */
Edge * get_edge (int line, int column, Graph *graph) 
{
    unsigned total_vertex = graph->total_vertex;

    if (line >= total_vertex || column >= total_vertex)
        return NULL;

    int line_pos = line * graph->total_vertex;
    int column_pos = column;

    return &graph->edge_array[line_pos + column_pos];

}

int graph_delete (Graph *graph)
{
    // free vertex objects
    for (int i = 0; i < graph->total_vertex; i++)
        free(graph->vertex_array[i].obj);
    
    // free vertex array 
    free(graph->vertex_array);
    
    // free edge array 
    free(graph->edge_array);

    //free graph
    free(graph);

    return 1;
};

/*
 * #################################################################################
 * ------------------------- END Basic Graphs Operations ---------------------------
 * #################################################################################
 */

/*
 * #################################################################################
 * ----------------------------- START Breadth Search ------------------------------
 * #################################################################################
 */

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

/*
 * #################################################################################
 * ------------------------------ END Breadth Search -------------------------------
 * #################################################################################
 */

/*
 * #################################################################################
 * ------------------------------ START Deep Search --------------------------------
 * #################################################################################
 */

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
	if(graph->vertex_array[id].degree != 0) {
		for(int i=0; i<graph->vertex_array[id].degree; i++) {
			if(data->dataTable[0][w[i]] == 0) {
				data->dataTable[2][w[i]] = id;
				data = depth_search_recursive(w[i], data, t, graph, searchId);
			}
			if(searchId == id) {
				data->result = &graph->vertex_array[id];
			}
		}
	}	
	++*t;
	data->dataTable[1][id] = *t;
	return data;
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



/**
 * @brief Realiza uma busca por todos os vértices vizinhos ao vértice requisitado.
 *
 * @param id Vértice a ser verificado.
 * @param graph Grafo a ser utilizado.
 */
int *vertex_neighbors(int id, Graph *graph) {
	int *w = malloc(graph->vertex_array[id].degree * sizeof(int));
	for(int i=0, j=0; i<graph->total_vertex; i++)
		if(graph->edge_array[(id * graph->total_vertex) + i].connect == 1) {
			w[j] = i;
			j++;
		}
	return w;
}

/*
 * #################################################################################
 * ------------------------------ END Deep Search ----------------------------------
 * #################################################################################
 */

/*
 * #################################################################################
 *---------------------------- START Floyd-Warshall --------------------------------
 * #################################################################################
*/

/**
 * @brief Retorna o endereço da posição line x column abstraindo o vetor de distância
 */
static float * fwget_dist (int line, int column, float *dist_array, Graph *graph)
{
    unsigned total_vertex = graph->total_vertex;

    if (line >= total_vertex || column >= total_vertex)
        return NULL;

    int line_pos = line * graph->total_vertex;
    int column_pos = column;

    return &dist_array[line_pos + column_pos];

}

ShortestPath * floydwarshall(Graph *graph){
    ShortestPath *path = malloc(sizeof(ShortestPath));   
    unsigned total_vertex = graph->total_vertex; 
    unsigned total_edge = graph->total_edge; 
    float *dist_array = malloc(sizeof(float) * graph->total_edge); 
    
    path->graph = graph;
    path->dist_array = dist_array; 
    

    for (int i = 0; i < total_edge; i++)
        dist_array[i] = INFINITY;
    for (int i = 0; i < total_vertex; i++) {
        float *dist = fwget_dist (i, i, dist_array, graph);
        *dist = 0;
    }
        
    for (int line = 0; line < total_vertex; line++) {
        unsigned *w_array = save_vertex_neighbors(graph, line);
        for (int column = 0; column < graph->vertex_array[line].degree; column++){
            unsigned *w = &w_array[column];
            float * dist = fwget_dist (line, *w, dist_array, graph);
            *dist = get_edge(line, *w, graph)->weight;
        }
    }

    float * direct_dist;
    float indirect_dist;

    for (int comp = 0; comp < total_vertex; comp++)
        for (int line = 0; line < total_vertex; line++)
            for(int column = 0; column < total_vertex; column++){
                direct_dist = fwget_dist(line, column, dist_array, graph);
                indirect_dist = *(fwget_dist(line, comp, dist_array, graph)) + *(fwget_dist(comp, column, dist_array, graph));
                if (*direct_dist > indirect_dist) {
                    *direct_dist = indirect_dist;
                }
            }
    return path;
}
/*
 * #################################################################################
 * ---------------------------------- END Floyd-Warshall ---------------------------
 * #################################################################################
 */

/*
 * #################################################################################
 * ---------------------------------- START A* ---------------------------
 * #################################################################################
 */

ShortestPath * astar (Graph *graph, unsigned src_id){
    ShortestPath *path = malloc(sizeof(ShortestPath));   

    unsigned total_vertex = graph->total_vertex; 
    unsigned total_edge = graph->total_edge; 

    float *dist_array = malloc(sizeof(float) * graph->total_edge); 
    
    path->graph = graph;
    path->dist_array = dist_array; 
    path->id = src_id;
    

    for (int i = 0; i < total_edge; i++)
        dist_array[i] = INFINITY;

    float *dist = fwget_dist (src_id, src_id, dist_array, graph);
    *dist = 0;

    //Dijkstra   
   
    struct vertexpath *varray = malloc(sizeof(struct vertexpath)*total_vertex);

    for (int i = 0; i < total_vertex; i++) {
        varray[i].pred = -1;
        varray[i].dist = &dist_array[i];
        varray[i].visited = false;
    }

    varray[src_id].dist = 0;
    varray[src_id].visited = true;

    for (int x = 0; x < total_vertex; x++) {
        // Se vértice não tiver sido visitado ainda
        if (!varray[x].visited) {

            // Visitar vértice x
            varray[x].visited = true;
            
            // Salva vizinhança do vértice x;
            unsigned *x_neigh = save_vertex_neighbors(graph, x);
            unsigned y;

            for (int i = 0; i < graph->vertex_array[x].degree; i++) {
                y = x_neigh[i];

                // se o vértice y não tiver sido vizitado ainda
                if (varray[y].visited == false) {
                    int src_x_y = *varray[x].dist + get_edge(x, y, graph)->weight;
                    /*
                     * Se a distância da fonte até y passando por x
                     * for maior que a distância da fonte até y.
                     */
                    if (src_x_y < *varray[y].dist) {
                        *varray[y].dist = src_x_y;
                        varray[y].pred = x;
                    }
                }
             }       
        }
    }

    return path;
};

/*
 * #################################################################################
 * ---------------------------------- END A* ---------------------------
 * #################################################################################
 */
