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


// - Ultilizei mesma logica do exercicio 2 so adaptei para exercer uma multiplicacao
// - Porem eu nao soube ultilizar a struct para acumular de certa forma dava algo errado
// - não soube identificar o por que do valor inteiro da minha struct na hora de acumular o valor fica incorreto
// - ultilizei uma variavel global os erros foram resolvidos nesse caso
int accumulator = 0;

double* load_vector(const char* filename, int* out_size);


// Avalia se o prod_escalar é o produto escalar dos vetores a e b. Assume-se
// que ambos a e b sejam vetores de tamanho size.
void avaliar(double* a, double* b, int size, double prod_escalar);


// - criei uma struct values para guardar os valores necessarios para realizar o metodo thread
typedef struct values_t {
    double* a;
    double* b;
    int lower_bound;
    int upper_bound;
} values;

// - Aqui acontece a parte principal do programa, cria um ponteiro pro argumento que vem da criação do thread
void* thread(void* arg) {
    values* op = (values*) arg;
    // - se o i for igual ao lower_bound ou i menor que upper bound eu incremento o i e realizo a soma do conteudo da minha struct
    for (size_t i = op->lower_bound; i < op->upper_bound; i++) {
        accumulator += op->a[i] * op->b[i];
    }
    // finalizo o thread sem mensagens de retorno
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

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

    values ops[n_threads];
    // array com n de threads
    pthread_t threads[n_threads];

    int mult_per_thread = (int) a_size / (int) n_threads;

    if (n_threads > a_size) {
        n_threads = a_size;
    }

    // - parte de salvamento na struct dos valores lidos de a b e c
    for (size_t i = 0; i < n_threads; ++i) {
        ops[i].a = a;
        ops[i].b = b;
        // - parte da logica dos limitadores
        ops[i].lower_bound = i * mult_per_thread;
        ops[i].upper_bound = i * mult_per_thread + mult_per_thread;

        // - verifico se meu i é == a n threads -1
        if (i == n_threads - 1)
            // - se for eu seto o upper para tamanho de a
            ops[i].upper_bound = a_size;
    }

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
    avaliar(a, b, a_size, accumulator);

    //Libera memória
    free(a);
    free(b);

    return 0;
}
