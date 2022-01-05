#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

//        (pai)
//          |
//      +---+---+
//      |       |
//     sed    grep

// ~~~ printfs  ~~~
//        sed (ao iniciar): "sed PID %d iniciado\n"
//       grep (ao iniciar): "grep PID %d iniciado\n"
//          pai (ao iniciar): "Processo pai iniciado\n"
// pai (após filho terminar): "grep retornou com código %d,%s encontrou adamantium\n"
//                            , onde %s é
//                              - ""    , se filho saiu com código 0
//                              - " não" , caso contrário

// Obs:
// - processo pai deve esperar pelo filho
// - 1º filho, após o término do 1º deve trocar seu binário para executar
//   sed -i /silver/axamantium/g;s/adamantium/silver/g;s/axamantium/adamantium/g text
//   + dica: leia as dicas do grep
// - 2º filho deve trocar seu binário para executar "grep adamantium text"
//   + dica: use execlp(char*, char*...)
//   + dica: em "grep adamantium text",  argv = {"grep", "adamantium", "text"}

int main(int argc, char** argv) {
    // - pai iniciado
    printf("Processo pai iniciado\n");

    // - variavel para depois iniciar segundo filho
    int pid2;
    // - variavel para armazenar o status no wait
    int status;
    // - Primeira ramificação = primeiro filho
    int pid = fork();

    // - primeira parte o sed, o filho -m 0 entra no if
    if (pid == 0) {
        // - pos um fork descarrego os prints
        fflush(stdout);
        // - imprimo sed inciado
        printf("sed PID %d iniciado\n", getpid());
        // - aguardando status
        wait(&status);
        // - funcao execlp sed para alterar silver pro adamantium
        execlp("sed", "sed", "-i", "-e", "s/silver/axamantium/g;s/adamantium/silver/g;s/axamantium/adamantium/g", "text", NULL);
    }
    // - Criando segundo filho com o main != 0
    if (pid != 0) {

        // - pid2 dando um fork para criar o segundo filho pid2 vai ser usado na logica seguinte
        pid2 = fork();

    }

    // - != 0 main entra aqui
    if (pid != 0){
        // - unico que tem pid2 == 0 é o segundo filho so ele executara o grep
        if (pid2 == 0) {
            //-- imprime grep iniciado
            printf("grep PID %d iniciado\n", getpid());
            // - solto todos os prints pois antes teve um fork
            fflush(stdout);
            // - aguarda status
            wait(&status);
            // - funcao execlp grep procura palavras adamantium
            execlp("grep","grep","adamantium", "text", NULL);
        }
        // - solto os prints pro terminal ficar organizado
        fflush(stdout);
        // - aguardo status
        wait(&status);
        // - logica que eu criei para imprimir não ou "" não consegui pensar em uma forma melhor as outras que tentei deram errado
        if (status == 0) {
            printf("grep retornou com código %d,%s encontrou adamantium\n", status, "");
        }
        if (status != 0) {
            printf("grep retornou com código %d,%s encontrou adamantium\n", status, " não");
        }
    }
    

    // ....
    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/
    
    return 0;
}
