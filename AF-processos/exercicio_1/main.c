#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv) {

    // - Bifurco meu main em um processo filho
    int pid = fork();

    // - o main é maior que zero, poderia usar diferente de 0 tb
    if (pid > 0) {
        int status;
        // -- Gero o segundo filho
        pid = fork();
        wait(&status);
        // -- Printo na tela os filhos criados
        printf("Processo filho %d criado\n", getpid());
    }

    if (pid != 0) {
        printf("Processo pai finalizado!\n");
    }

    return 0;
}
