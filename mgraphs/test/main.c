#include <mgraphs.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


Graph * gen_graph (int m){

    Graph *graph = graph_create(true, m*m);

    unsigned n[m][m];
    int v = 0;
    //gerar matrix
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            n[i][j] = v;
            v++;
        }
    }
    
    // gerar grafo
    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if (j < m-1) { 
                edge_insert(graph, n[i][j], n[i][j+1], 1);
                edge_insert(graph, n[i][j+1], n[i][j], 1);
            } 

            if (i < m-1) {
                edge_insert(graph, n[i][j], n[i+1][j], 1);
                edge_insert(graph, n[i+1][j], n[i][j], 1);
            }
        }
    }

    return graph;
}
//--------------------------------------------------------------------------

void run_dijkstra()
{
    clock_t start, end;
    double runtime;   
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(10);  

        start = clock();
        dijkstra(graph, 30);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nTempo total 100: %f segundos\n", runtime);

        exit(0);
    }
    wait(NULL);
    
    
    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(50);  
        
        start = clock();
        dijkstra(graph, 300);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo total 2.500: %f segundos\n", runtime);
        exit(0);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(100);  

        start = clock();
        dijkstra(graph, 200);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo total 10.000: %f segundos\n", runtime);
        exit(0);
    }
    wait(NULL);
}
//----------------------------------------------------------

void run_bellmanFord()
{
    clock_t start, end;
    double runtime;   
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(10);  

        start = clock();
        bellmanFord(graph, 30);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nTempo total 100: %f segundos\n", runtime);

        exit(0);
    }
    wait(NULL);
    
    
    pid = fork();
    if (pid == 0)
    {

        Graph *graph = gen_graph(50);  
        
        start = clock();
        bellmanFord(graph, 300);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo total 2.500: %f segundos\n", runtime);
        exit(0);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(100);  

        start = clock();
        bellmanFord(graph, 200);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo total 10.000: %f segundos\n", runtime);
        exit(0);
    }
    wait(NULL);
}
//----------------------------------------------------------

void run_floydwarshall()
{
    clock_t start, end;
    double runtime;   
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(10);  

        start = clock();
        floydwarshall(graph);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nTempo total 100: %f segundos\n", runtime);

        exit(0);
    }
    wait(NULL);
    
    
    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(50);  

        start = clock();
        floydwarshall(graph);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo total 2.500: %f segundos\n", runtime);
        exit(0);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0)
    {
        Graph *graph = gen_graph(100);  

        start = clock();
        floydwarshall(graph);
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo total 10.000: %f segundos\n", runtime);
        exit(0);
    }
    wait(NULL);
}
//----------------------------------------------------------

void run_astar()
{
    clock_t start, end;
    double runtime;   
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        int m = 10;
        unsigned n[m][m];
        Graph *graph = graph_create(true, m*m);
        
        int v = 0;
        //gerar matrix
        for (int i = 0; i < m; i++){
            for (int j = 0; j < m; j++){
                n[i][j] = v;
                v++;
            }
        }
        
        // gerar grafo
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                if (j < m-1) { 
                    edge_insert(graph, n[i][j], n[i][j+1], 1);
                    edge_insert(graph, n[i][j+1], n[i][j], 1);
                } 

                if (i < m-1) {
                    edge_insert(graph, n[i][j], n[i+1][j], 1);
                    edge_insert(graph, n[i+1][j], n[i][j], 1);
                }
            }
        }

        unsigned src = 0;
        unsigned targ = 5;

        start = clock();
        astar(graph, src, targ, m, n);        
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nTempo total 100: %f segundos\n", runtime);

        exit(0);
    }
    wait(NULL);
    
    
    pid = fork();
    if (pid == 0)
    {
        int m = 50;
        unsigned n[m][m];
        Graph *graph = graph_create(true, m*m);
        
        int v = 0;
        //gerar matrix
        for (int i = 0; i < m; i++){
            for (int j = 0; j < m; j++){
                n[i][j] = v;
                v++;
            }
        }
        
        // gerar grafo
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                if (j < m-1) { 
                    edge_insert(graph, n[i][j], n[i][j+1], 1);
                    edge_insert(graph, n[i][j+1], n[i][j], 1);
                } 

                if (i < m-1) {
                    edge_insert(graph, n[i][j], n[i+1][j], 1);
                    edge_insert(graph, n[i+1][j], n[i][j], 1);
                }
            }
        }

        unsigned src = 0;
        unsigned targ = 1500;

        start = clock();
        astar(graph, src, targ, m, n);        
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nTempo total 100: %f segundos\n", runtime);

        exit(0);
    }
    wait(NULL);
    
    pid = fork();
    if (pid == 0)
    {
        int m = 100;
        unsigned n[m][m];
        Graph *graph = graph_create(true, m*m);
        
        int v = 0;
        //gerar matrix
        for (int i = 0; i < m; i++){
            for (int j = 0; j < m; j++){
                n[i][j] = v;
                v++;
            }
        }
        
        // gerar grafo
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                if (j < m-1) { 
                    edge_insert(graph, n[i][j], n[i][j+1], 1);
                    edge_insert(graph, n[i][j+1], n[i][j], 1);
                } 

                if (i < m-1) {
                    edge_insert(graph, n[i][j], n[i+1][j], 1);
                    edge_insert(graph, n[i+1][j], n[i][j], 1);
                }
            }
        }

        unsigned src = 0;
        unsigned targ = 5500;

        start = clock();
        astar(graph, src, targ, m, n);        
        end = clock();
        runtime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nTempo total 100: %f segundos\n", runtime);

        exit(0);
    }
    wait(NULL);
}
int main ()
{
    int flag;

    do {
        // Show menu
        printf("\nMenu:\n");
        printf("1. Dijkstra\n");
        printf("2. Bellman-Ford\n");
        printf("3. Floyd-Warshall\n");
        printf("4. A*\n");
        printf("0. Finish\n");
        printf("Choose an option: ");
        scanf("%d", &flag);

        //switch case
        switch (flag) {
            case 1:
                printf("Você escolheu a Opção 1.\n");
                run_dijkstra();
                break;
            case 2:
                printf("Você escolheu a Opção 2.\n");
                run_bellmanFord();
                break;
            case 3:
                printf("Você escolheu a Opção 3.\n");
                run_floydwarshall();
                break;
            case 4:
                printf("Você escolheu a Opção 4.\n");
                run_astar();
                break;
            case 0:
                printf("Leaving the program. See you later!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }

    } while (flag != 0);




}
