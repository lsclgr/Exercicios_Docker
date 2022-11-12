#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define NUMTHREADS 3

pthread_t threads[NUMTHREADS];
int saldo = 0;
int flag = 0;

void *threadImprime(void *arg); // imprime
void *threadSoma(void *arg);    // soma
void *threadSubtrai(void *arg); // subtracao

int main(int argc, char **argv)
{
    int i;
    int opcao = 0;

    printf("\n-----------------------MENU------------------------\n");
    printf("[+] - somar 1000 UD;\n");
    printf("[-] - subtrair 1000 UD;\n");
    printf("[p] - imprimir o valor do saldo;\n");
    printf("[k] - destuir todos os threads e finalizar a execucao.\n");
    printf("----------------------------------------------------\n\n");
    printf("O valor inicial de saldo eh: %d\n\n", saldo);

    while (opcao != 75 && opcao != 107)
    { // sair
        opcao = (int)getchar();

        if (opcao == 80 || opcao == 112)
        { // imprime
            pthread_join(threads[0], NULL);
            pthread_join(threads[1], NULL);
            pthread_join(threads[2], NULL);
            pthread_create(&(threads[0]), NULL, threadImprime, NULL);
        }
        else if (opcao == 43)
        { // soma
            pthread_join(threads[1], NULL);
            pthread_create(&(threads[1]), NULL, threadSoma, NULL);
        }
        else if (opcao == 45)
        { // subtrai
            pthread_join(threads[2], NULL);
            pthread_create(&(threads[2]), NULL, threadSubtrai, NULL);
        }
        else if (opcao == 75 || opcao == 107)
        {
            pthread_kill(threads[0], 0);
            pthread_kill(threads[1], 0);
            pthread_kill(threads[2], 0);

            printf("------------------------------\n");
            printf("KILLED\n");
            printf("------------------------------\n");
        }
        else
        {
            continue;
        }
    }

    return 0;
}

void *threadImprime(void *arg)
{ // imprime
    pid_t tid;
    tid = syscall(__NR_gettid);
    printf("------------------------------\n");
    printf("TID: %d\n", tid);
    printf("Saldo: %d\n", saldo);
    printf("------------------------------\n");
    pthread_exit(0);
}

void *threadSoma(void *arg)
{ // soma
    pid_t tid;
    tid = syscall(__NR_gettid);
    printf("------------------------------\n");
    printf("ADICIONANDO 1000...\n");
    printf("TID: %d\n", tid);
    saldo += 1000;
    printf("------------------------------\n");
    pthread_exit(0);
}

void *threadSubtrai(void *arg)
{ // subtracao
    pid_t tid;
    tid = syscall(__NR_gettid);
    printf("------------------------------\n");
    printf("REMOVENDO 1000...\n");
    printf("TID: %d\n", tid);
    saldo -= 1000;
    printf("------------------------------\n");
    pthread_exit(0);
}