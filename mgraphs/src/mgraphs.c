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
Graph * graph_create(bool directed, unsigned n){

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
	}else{
        if(graph->edge_array[edge_pos1].connect == 0){
            graph->graph_degree+=2;
            graph->vertex_array[id1].vertex_degree++;
            graph->vertex_array[id2].vertex_degree++;
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
	}else{
        if(graph->edge_array[edge_pos1].connect == 1){
            graph->graph_degree-=2;
            graph->vertex_array[id1].vertex_degree--;
            graph->vertex_array[id2].vertex_degree--;
        }
		graph->edge_array[edge_pos1].connect = 0;
		graph->edge_array[edge_pos1].weight = 0;

		graph->edge_array[edge_pos2].connect = 0;
		graph->edge_array[edge_pos2].weight = 0;
	}
}

unsigned vertex_degree (Graph *graph, unsigned id){
	return graph->vertex_array[id].vertex_degree;
}

SearchData breadth_search(Graph *graph)
{
	int numVertex = graph->total_vertex;
	SearchData *data = malloc(sizeof(SearchData));
	Queue *vertexQueue = createQueue(numVertex);
	Vertex *markedVertices = malloc(numVertex * sizeof(Vertex)); // vetor de vertices marcados
	int lenMarkedVertices = 0;
	Vertex vertex1;
	unsigned *adjList;

	markedVertices[0] = graph->vertex_array[0]; // marca raiz
	lenMarkedVertices++;

	enqueue(vertexQueue, markedVertices[0]); // poe raiz na fila

	int nextAdj = 0;

	while (isEmpty(vertexQueue))
	{										// enquanto a fila nao esta vazia
		vertex1 = front(vertexQueue);		// vertice que esta no inicio da fila
		adjList = malloc(vertex1.id * sizeof(unsigned));
		for (int i = 0; i < numVertex; i++) // Ladj = lista de adjacencia de vertice1
			if(graph->edge_array[(vertex1.id * numVertex) + i].connect == 1)
				adjList[i] = graph->edge_array[(vertex1.id * numVertex) + i].connect;

		while (adjList != numVertex)
		{ // enquanto a lista de adjacencia do vertice1 nao acaba
			if (!search_vertex(adjList[nextAdj], markedVertices, lenMarkedVertices, graph->vertex_array))
			{														  // busca p->vertice no vetor verticesMarcados
				markedVertices[lenMarkedVertices++] = graph->vertex_array[nextAdj]; // marcou p->vertice
				PoeVerticeNaFila(F, p->vertice);					  // poe p->vertice na fila
																	  // arestas que compoem arvore geradora mínima, aresta (vertice1, p->vertice)
			}
			else if (WPertenceF(p->vertice, F))
			{ // se p->vertice pertence a F
			  // arestas (vertice1, p->vertice) que não compoem árvore geradora mínima
			}
			p = p->prox;
		}
		RetiraVerticeFila(F);
	}
	return 0;
}

bool search_vertex(int adj, Vertex *list, int tam, Vertex *vertices)
{
	for(int i=0; i<tam; i++)
		if(vertices[adj].id == list[i].id)
			return true;
	
	return false;
}


