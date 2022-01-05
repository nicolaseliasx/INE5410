#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

int produzir(int value);    //< definida em helper.c
void consumir(int produto); //< definida em helper.c
void *produtor_func(void *arg);
void *consumidor_func(void *arg);

int indice_produtor, indice_consumidor, tamanho_buffer;
int* buffer;


sem_t sem_cap;
sem_t sem_disp;


//Você deve fazer as alterações necessárias nesta função e na função
//consumidor_func para que usem semáforos para coordenar a produção
//e consumo de elementos do buffer.
void *produtor_func(void *arg) {
    //arg contem o número de itens a serem produzidos
    int max = *((int*)arg);
    for (int i = 0; i <= max; ++i) {
        int produto;
        if (i == max)
            produto = -1;          //envia produto sinlizando FIM
        else 
            produto = produzir(i); //produz um elemento normal
        sem_wait(&sem_cap);
        indice_produtor = (indice_produtor + 1) % tamanho_buffer; //calcula posição próximo elemento
        buffer[indice_produtor] = produto; //adiciona o elemento produzido à lista
        sem_post(&sem_disp);
    }
    return NULL;
}

void *consumidor_func(void *arg) {
    while (1) {
        sem_wait(&sem_disp);
        indice_consumidor = (indice_consumidor + 1) % tamanho_buffer; //Calcula o próximo item a consumir
        int produto = buffer[indice_consumidor]; //obtém o item da lista
        sem_post(&sem_cap);
        //Podemos receber um produto normal ou um produto especial
        if (produto >= 0)
            consumir(produto); //Consome o item obtido.
        else
            break; //produto < 0 é um sinal de que o consumidor deve parar
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s tamanho_buffer itens_produzidos\n", argv[0]);
        return 0;
    }

    tamanho_buffer = atoi(argv[1]);
    int n_itens = atoi(argv[2]);
    printf("n_itens: %d\n", n_itens);

    //Iniciando buffer
    indice_produtor = 0;
    indice_consumidor = 0;
    buffer = malloc(sizeof(int) * tamanho_buffer);

    // Inicio do semaforo a ser ultilizado
    sem_init(&sem_cap, 0, n_itens);
    sem_init(&sem_disp, 0, 0);

    // Crie threads e o que mais for necessário para que uma produtor crie 
    // n_itens produtos e o consumidor os consuma
    // Thread do produtor 
    pthread_t threads_pr;
    // Thread do consumidor
    pthread_t threads_co;
    // Consumidor
    pthread_create(&threads_pr, NULL, &consumidor_func, NULL);
    // Produtor
    pthread_create(&threads_co, NULL, &produtor_func, &n_itens);
    
    // Joins com os resultados
    pthread_join(threads_pr, NULL);
    pthread_join(threads_co, NULL);
    // ....
    
    //Libera memória do buffer
    free(buffer);

    sem_destroy(&sem_cap);
    sem_destroy(&sem_disp);

    return 0;
}

