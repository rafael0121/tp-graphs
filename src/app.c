#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(){
    
    unsigned input = 3;

    pid_t pid;
    while(input != 0){
        printf("Olá, digite o número da biblioteca que deseja utilizar\n\n");

        printf("Grafos em matriz - (1)\n");
        printf("Grafos em Lista de adjacência - (2)\n");
        printf("Sair - (0)\n\n");

        printf("Selecionar: ");

        scanf("%d", &input);

        if(input > 2 || input < 0){
            printf("\nOpção inválida!\n");
        }

        if(input == 2){
            pid = fork();
            if(pid == 0){
                printf("\n erro = %d\n\n", execv("./app_lgraphs.out", NULL));
                return -1;
            }

        }

        if(input == 1){
            pid = fork();
            if(pid == 0){
                printf("\n erro = %d\n\n", execv("./app_mgraphs.out", NULL));
                return -1;
            }

        }

        wait(&pid);
    }

    return 0;
}
