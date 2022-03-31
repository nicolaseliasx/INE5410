#include <stdlib.h>
#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>
#include "esteira.h"


pthread_mutex_t GERAL_BUFFER;



void buffer_inicializa(buffer_t *self)
{   

    pthread_mutex_init(&GERAL_BUFFER, NULL);
    
    /* TODO: Adicionar código nesta função se necessário! */
    self->slots_ocupados = 0;
    self->slots = (lampada_t **) malloc(sizeof(lampada_t *) * config.capacidade_buffer);
    plog("[buffer] Inicializado\n");
}

void buffer_insere(buffer_t *self, lampada_t *lampada) 
{
    /* TODO: Adicionar código nesta função se necessário! */
    self->slots[self->slots_ocupados] = lampada;
    /* Incrementa a quantidade de slots ocupados no buffer. */
    self->slots_ocupados++;
}

lampada_t * buffer_remove(buffer_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    /* Decrementa a quantidade de slots ocupados no buffer. */
    self->slots_ocupados--;
    sem_post(&para_esteira);
    // SEMAFORO PARA PARAR ESTEIRA CASO BUFFER CHEIO
    return(self->slots[self->slots_ocupados]);
}

void buffer_finaliza(buffer_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    free(self->slots);
    plog("[buffer] Finalizado\n");
}