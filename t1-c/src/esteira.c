#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "config.h"
#include "esteira.h"
#include <semaphore.h>

sem_t para_esteira;

sem_t ultima_lampada;

void * esteira_executa(void *arg)
{
    plog("[esteira] Inicializada\n");

    /* Recupera o argumento de entrada (esteira_t). */
    esteira_t *esteira = (esteira_t *) arg;

    double fator = (double) (ESTEIRA_VEL_MAX + 1 - config.velocidade_esteira);
    
    /* Produz config.total_lampadas lâmpadas. */
    for (int i = 0; i < config.quantidade_lampadas; i++) {
        // DECREMENTA UMA POSIÇÃO DO SEMAFORO ATE CAPACIDADE ESTEIRA == 0 = TRAVA
        sem_wait(&para_esteira);  
        esteira_insere(esteira);
        msleep((long) ESTEIRA_VEL_TEMPO * pow(2.0, fator));    
    }
    pthread_exit(NULL); 
}
/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo!  */
/* Professor Marcio permitiu alteração das funções abaixo    */
/* --------------------------------------------------------- */

void esteira_inicializa(esteira_t *self)
{   

    sem_init(&para_esteira, 0, config.capacidade_buffer);
    sem_init(&ultima_lampada, 0, 0);


    self->tipo = ESTEIRA;
    self->lampadas_produzidas = 0;
    self->lampadas_consumidas = 0;
    self->lampadas = (lampada_t *) malloc(sizeof(lampada_t) * config.quantidade_lampadas);

    if (pthread_create(&self->thread, NULL, esteira_executa, (void *) self) != 0) {
        plog("[esteira] Erro ao inicializar esteira\n");
    }
}

void esteira_insere(esteira_t *self) 
{   
    if (rand() % 2 == 0)
        lampada_inicializa(&(self->lampadas[self->lampadas_produzidas]), self->lampadas_produzidas, OK, OK, OK, OK);
    else
        lampada_inicializa(&(self->lampadas[self->lampadas_produzidas]), self->lampadas_produzidas, rand() % 2, rand() % 2, rand() % 2, rand() % 2);
    
    plog("[esteira] Lâmpada %u INSERIDA na esteira (bulbo: %s, luz: %s, rosca: %s, marca: %s)\n", self->lampadas_produzidas, lampada_param_status(self->lampadas[self->lampadas_produzidas].bulbo), 
        lampada_param_status(self->lampadas[self->lampadas_produzidas].luz), lampada_param_status(self->lampadas[self->lampadas_produzidas].rosca), lampada_param_status(self->lampadas[self->lampadas_produzidas].marca));
    
    self->lampadas_produzidas++;
}

lampada_t lampada_remove;

lampada_t * esteira_remove(esteira_t *self)
{   
    lampada_remove = self->lampadas[self->lampadas_consumidas++];
    return(&lampada_remove);
}

void esteira_finaliza(esteira_t *self)
{
    sem_wait(&ultima_lampada);
    pthread_join(self->thread, NULL);
    free(self->lampadas);
    plog("[esteira] Finalizada\n");
}

