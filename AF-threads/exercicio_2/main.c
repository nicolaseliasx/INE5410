#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

// Lê o conteúdo do arquivo filename e retorna um vetor E o tamanho dele
// Se filename for da forma "gen:%d", gera um vetor aleatório com %d elementos
//
// +-------> retorno da função, ponteiro para vetor malloc()ado e preenchido
// | 
// |         tamanho do vetor (usado <-----+
// |         como 2o retorno)              |
// v                                       v
double* load_vector(const char* filename, int* out_size);


// Avalia o resultado no vetor c. Assume-se que todos os ponteiros (a, b, e c)
// tenham tamanho size.
void avaliar(double* a, double* b, double* c, int size);

// - criei uma struct values para guardar os valores necessarios para realizar o metodo thread
typedef struct values_t {
    double* a;
    double* b;
    double* c;
    int lower_bound;
    int upper_bound;
} values;

// - Aqui acontece a parte principal do programa, cria um ponteiro pro argumento que vem da criação do thread
void* thread(void* arg) {
    values* op = (values*) arg;
    // - se o i for igual ao lower_bound ou i menor que upper bound eu incremento o i e realizo a soma do conteudo da minha struct
    for (size_t i = op->lower_bound; i < op->upper_bound; i++) {
        op->c[i] = op->a[i] + op->b[i];
    }
    // finalizo o thread sem mensagens de retorno
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    // Gera um resultado diferente a cada execução do programa
    // Se **para fins de teste** quiser gerar sempre o mesmo valor
    // descomente o srand(0)
    srand(time(NULL)); //valores diferentes
    //srand(0);        //sempre mesmo valor

    //Temos argumentos suficientes?
    if(argc < 4) {
        printf("Uso: %s n_threads a_file b_file\n"
               "    n_threads    número de threads a serem usadas na computação\n"
               "    *_file       caminho de arquivo ou uma expressão com a forma gen:N,\n"
               "                 representando um vetor aleatório de tamanho N\n",
               argv[0]);
        return 1;
    }
  
    //Quantas threads?
    int n_threads = atoi(argv[1]);

    if (!n_threads) {
        printf("Número de threads deve ser > 0\n");
        return 1;
    }
    //Lê números de arquivos para vetores alocados com malloc
    int a_size = 0, b_size = 0;
    double* a = load_vector(argv[2], &a_size);
    if (!a) {
        //load_vector não conseguiu abrir o arquivo
        printf("Erro ao ler arquivo %s\n", argv[2]);
        return 1;
    }
    double* b = load_vector(argv[3], &b_size);
    if (!b) {
        printf("Erro ao ler arquivo %s\n", argv[3]);
        return 1;
    }
    
    //Garante que entradas são compatíveis
    if (a_size != b_size) {
        printf("Vetores a e b tem tamanhos diferentes! (%d != %d)\n", a_size, b_size);
        return 1;
    }
    //Cria vetor do resultado 
    double* c = malloc(a_size*sizeof(double));

    // Calcula com uma thread só. Programador original só deixou a leitura 
    // do argumento e fugiu pro caribe. É essa computação que você precisa 
    // paralelizar

    // array para armazenar as operacoes com o numero de threads fornecido
    values ops[n_threads];
    // array com n de threads
    pthread_t threads[n_threads];

    // - aqui umas das logicas principais para saber quantos threads posso ultilizar por operacao
    // - somas por thread consiste do tamanho do a dividido pelo numero de threads
    int sums_per_thread = (int) a_size / (int) n_threads;

    // - verifico se meu numero de threads é maior que o tamanho de a, entao eu seto meu numero de threads pro tamanho de a
    if (n_threads > a_size) n_threads = a_size;

    // - parte de salvamento na struct dos valores lidos de a b e c
    for (size_t i = 0; i < n_threads; ++i) {
        ops[i].a = a;
        ops[i].b = b;
        ops[i].c = c;
        // - parte da logica dos limitadores
        ops[i].lower_bound = i * sums_per_thread;
        ops[i].upper_bound = i * sums_per_thread + sums_per_thread;

        // - verifico se meu i é == a n threads -1
        if (i == n_threads - 1)
            // - se for eu seto o upper para tamanho de a
            ops[i].upper_bound = a_size;
    }

    // - ponteiro que recebe ops que é uma struct values para passar como argumento na criacao
    values* op_pointer = ops;

    // - criando thread especificando o que vai exercer e o ponteiro criado anteriormente
    for (size_t i = 0; i < n_threads; ++i)
        pthread_create(&threads[i], NULL, thread, op_pointer + i);

    // - Aguarda o termino de cada thread, e não salva por conta do NULL
    for (size_t i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);


    //    +---------------------------------+
    // ** | IMPORTANTE: avalia o resultado! | **
    //    +---------------------------------+
    avaliar(a, b, c, a_size);
    

    //Importante: libera memória
    free(a);
    free(b);
    free(c);

    return 0;
}
