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

pthread_mutex_t mutex;


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
        if (i == max) {
            produto = -1;          //envia produto sinlizando FIM
        }
        else {
            // mutex para os treahds produzir um de cada vez e não da conflito no semaforo
            pthread_mutex_lock(&mutex);
            produto = produzir(i); //produz um elemento normal
            pthread_mutex_unlock(&mutex);
        }
            
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
        if (produto >= 0) {
            consumir(produto); //Consome o item obtido.
        }   
        else {
            printf("chegou aq");
            break; //produto < 0 é um sinal de que o consumidor deve parar
        }
            
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
    int n_produtores = atoi(argv[3]);
    int n_consumidor = atoi(argv[4]);
    printf("itens=%d, n_produtores=%d, n_consumidores=%d\n",
	   n_itens, n_produtores, n_consumidor);

    //Iniciando buffer
    indice_produtor = 0;
    indice_consumidor = 0;
    buffer = malloc(sizeof(int) * tamanho_buffer);

    // Inicio do semaforo a ser ultilizado
    sem_init(&sem_cap, 0, n_itens);
    sem_init(&sem_disp, 0, 0);

    // Crie threads e o que mais for necessário para que uma produtor crie 
    // n_itens produtos e o consumidor os consuma
    pthread_t threads_pr[n_produtores];
    pthread_t threads_co[n_consumidor];

    // criando n threads produtor
    for (int i = 0; i < n_produtores; i++) {
        pthread_create(&threads_pr[i], NULL, &produtor_func, &n_itens);
    }
    // criando n threads consumidor
    for (int i = 0; i < n_consumidor; i++) {
        pthread_create(&threads_co[i], NULL, &consumidor_func, NULL);
    }

    
    // joins
    for (int i = 0; i < n_produtores; i++) {
        pthread_join(threads_pr[i], NULL);
    }
    
    // joins
    for (int i = 0; i < n_consumidor; i++) {
        pthread_join(threads_co[i], NULL);
    }
   
    //Libera memória do buffer
    free(buffer);
    
    pthread_mutex_destroy(&mutex);

    sem_destroy(&sem_cap);
    sem_destroy(&sem_disp);

    return 0;
}

