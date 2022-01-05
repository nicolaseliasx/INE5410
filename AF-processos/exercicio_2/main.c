#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int main(int argc, char** argv) {

    // - Criando variavel inteira para ultilizar fork nos netos
    int pid2;
    // - Fazendo a primeira bifurcação gerando o primeiro filho do processo pai
    int pid = fork();
    
    // - Verifico se o pid se difere de 0, se sim esse pid é o pai
    if (pid != 0) {

        // - Gero o outro filho, agora tenho os dois filhos
        pid = fork();

    }

    // - Testo se o pid que tenho é igual a 0, se sim então sou um dos filhos do main
    if (pid == 0) {

        // - Mostro na tela o id do filho e seu main que no caso é o main
        printf("Processo: %d, filho de %d\n",getpid(), getppid());
        // - Gero o primeiro neto, ambos filhos passarao aqui então terei 2 netos com esse fork()
        pid2 = fork();

        // - Verifico se o pid2 que acaba de gerar é diferente de 0 se for ent ainda estou o filho
        if (pid2 != 0) {

            // - Gero o segundo neto, como os dois passam aqui terei 4 Netos
            pid2 = fork();

            // - Repito o processo
            if (pid2 != 0) {
                // - Tenho ao todo 6 netos 3 de cada filho do main
                pid2 = fork();

            }
        }
    }

    // - Verifico de o pid2 é igual a zero se for estou nos netos
    if (pid2 == 0) {
        // - Executo o printf que solicitado no enunciado
        printf("Processo %d, filho de %d\n",getpid(),getppid());\
        // - Comando sleep 5 para o neto aguardar
        sleep(5);
    }

    // - Verifico se o pid é igual a zero se for estou em um dos filhos do main
    if (pid == 0) {
        // - verificando se meu pid2 é diferente de zero se for continuo estando no filho do main
        if (pid2 != 0) {
            //- inicio o wait esperando que os netos terminei sua execução
            int status;
            wait(&status);
            // - Apos netos terminarem mostro na tela o printf
            printf("Processo %d finalizado\n",getpid());
        }

    // -  Print de processo finalizado no qual o filho do main está aguarrdando
    if (pid2 == 0) {
        printf("Processo %d finalizado\n",getpid());
    }

    }

    // -  Repito o processo [para o main aguardar o filho
    if (pid != 0) {
        int status;
        wait(&status);
        printf("Processo principal %d finalizado\n",getpid());
    }

    return 0;
}
