
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    printf("\n---------------------MENU----------------------\n");
    printf("[+] - somar 1000 UD;\n");
    printf("[-] - subtrair 1000 UD;\n");
    printf("[p] - imprimir o valor do saldo;\n");
    printf("[k] - finalizar a execucao.\n");
    printf("------------------------------------------------\n\n");
    printf("O valor inicial de saldo eh: 0\n\n");

    int saldo[2];
    int opcao[2];
    int caractere = 0;

    if (pipe(saldo) < 0 || pipe(opcao) < 0)
    {
        printf("Erro ao criar pipe\n");
        exit(1);
    }

    int aux = 0;
    if (write(saldo[1], &aux, sizeof(int)) == -1)
    {
        printf("Erro ao escrever no pipe\n");
        exit(1);
    }

    pid_t pidPai = getpid();
    pid_t filhoSoma = fork();
    pid_t filhoSubtrai = -1;

    if (filhoSoma < 0)
    {
        printf("Erro ao criar fork\n");
        exit(1);
    }
    fflush(stdin);

    if (getpid() == pidPai)
    {
        filhoSubtrai = fork();
        if (filhoSubtrai < 0)
        {
            exit(1);
        }
        if (filhoSubtrai == 0)
        {
            filhoSoma = -1;
        }
    }

    if (getpid() == pidPai)
    {
        int x;
        while (caractere != 107 || caractere != 75)
        {
            do
            {
                caractere = (int)getchar();
            } while ((caractere != 43) && (caractere != 80) && (caractere != 112) && (caractere != 107) && (caractere != 75) && (caractere != 45));

            if (caractere == 80 || caractere == 112)
            {
                read(saldo[0], &x, sizeof(int));
                printf("-----------------------------\n");
                printf("Print em PID : %d\n", getpid());
                printf("Saldo        : %d UD\n", x);
                printf("-----------------------------\n");
                write(saldo[1], &x, sizeof(int));
            }
            else
            {
                write(opcao[1], &caractere, sizeof(int));
            }

            if (caractere == 107 || caractere == 75)
            {
                printf("-----------------------------\n");
                kill(filhoSoma, SIGKILL);
                kill(filhoSubtrai, SIGKILL);
                kill(getpid(), SIGKILL);
                exit(0);
            }
        }
    }
    else if (filhoSoma == 0)
    {
        int operacao;
        int x;
        do
        {
            read(opcao[0], &operacao, sizeof(int));

            if (operacao == 43)
            {
                printf("-----------------------------\n");
                printf("Adicionando 1000 UD em PID  : %d\n", getpid());
                printf("-----------------------------\n");
                read(saldo[0], &x, sizeof(int));
                x += 1000;
                write(saldo[1], &x, sizeof(int));
            }
            else
            {
                write(opcao[1], &operacao, sizeof(int));
            }
        } while (operacao != 107 || operacao != 75);
    }
    else if (filhoSubtrai == 0)
    {
        int operacao;
        int x;
        do
        {
            read(opcao[0], &operacao, sizeof(int));

            if (operacao == 45)
            {
                printf("-----------------------------\n");
                printf("Removendo 1000 UD em PID: %d\n", getpid());
                printf("-----------------------------\n");
                read(saldo[0], &x, sizeof(int));
                x -= 1000;
                write(saldo[1], &x, sizeof(int));
            }
            else
            {
                write(opcao[1], &operacao, sizeof(int));
            }
        } while (operacao != 107 || operacao != 75);
    }

    return 0;
}
