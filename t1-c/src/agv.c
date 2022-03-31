#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "agv.h"
#include <semaphore.h>

pthread_mutex_t recicla;
pthread_mutex_t posiciona;

sem_t max_agv_pos;

bool inicializa = true;

void agv_inicializa(agv_t *self, unsigned int id)
{
    // INICIALIZAÇÃO DOS MUTEXES E SEMAFOROS
    if (inicializa) {
        inicializa = false;
        pthread_mutex_init(&recicla, NULL);
        pthread_mutex_init(&posiciona, NULL);
        // PERMITE POSICIONAR APENAS DOIS AGVS
        sem_init(&max_agv_pos, 0, 2);
    }
    
    self->posicionado = false;
    self->id = id;
    self->cont_lampadas = 0;
    if (pthread_create(&self->thread, NULL, agv_executa, (void *) self) == 0) {
        plog("[AGV %u] Inicializado\n", self->id);
    }
    else {
        plog("[AGV %u] Erro ao inicializar AGV\n", self->id);
    }
}

bool reciclagem = true;

void * agv_executa(void *arg)
{
    agv_t *agv = (agv_t *) arg;
    
    if (agv->posicionado == false) {
        while (true) {
            sem_wait(&max_agv_pos);
            pthread_mutex_lock(&recicla);
            // MUDA A CADA VEZ QUE UMA THREAD PASSA AQUI
            if (!agv->posicionado){
                if (reciclagem) {
                    reciclagem = false;
                } else {
                    reciclagem = true;
                }
            }  
            pthread_mutex_unlock(&recicla);

            pthread_mutex_lock(&posiciona);
            // CHAMA METODO POSICIONA
            if (!agv->posicionado)
                agv_posiciona(agv, reciclagem); 
            pthread_mutex_unlock(&posiciona);

            // AGUARDA ESSA CONDIÇÃO SER SATISFEITA
            while (agv->cont_lampadas < config.capacidade_agv && !config.lampada_final) {}
            agv_transporta(agv);
            sem_post(&max_agv_pos);

            if (config.lampada_final) {
                sem_post(&ultima_lampada);
                break;
            }
        }
    }

    /* Recupera o argumento de entrada (agv_t). */
    /* agv_t *agv = (agv_t *) arg; */

    /* TODO: Implementar aqui o comportamento do AGV */
  
    pthread_exit(NULL);
}

void agv_posiciona(agv_t *self, bool reciclar)
{
    /* AGV se posiciona para que lâmpadas sejam colocadas no seu compartimento de carga. */

    if (!self->posicionado && self->cont_lampadas == 0) {
        self->reciclar = reciclar;
        self->posicionado = true;

        if (reciclar) {
            plog("[AGV %u] Posicionado para carregamento com lâmpadas para reciclagem\n", self->id);
        } else {
            plog("[AGV %u] Posicionado para carregamento com lâmpadas aprovadas no teste\n", self->id);
        }
    } else {
        plog("[AGV %u] Erro ao tentar posicionar AVG em uso\n", self->id);
    }
}

void agv_insere(agv_t *self, lampada_t *lampada)
{
    /* TODO: Inserir uma lâmpada no compartimento de carga do AGV. */
    self->cont_lampadas++;
    plog("[AGV %u] Lâmpada inserida no compartimento de carga.\n", self->id);
}

/*DOIS CARRINHOS DIFERENTES, UM PARA AS LAMPADAS REPROVADAS QUE SERÃO RECICLADAS 
E OUTRO PARA AS LAMPADAS APROVADAS QUE SERÃO EMBALADAS*/
/*SE O COMPARTIMENTO DE CARGA ESTIVER CHEIO, O AGV VAI TRANPOSTAR PARA O DEPOSITO 
E OUTRO AGV VAI TOMAR O SEU LUGAR, QUANTIDADE DE AGVS EM OPERAÇÃO É quantidade_agvs*/
void agv_transporta(agv_t *self)
{
    /* TODO: Transportar a carga de lâmpadas para o depósito. */

    self->posicionado = false;
    self->cont_lampadas = 0;
    plog("[AGV %u] Lâmpadas transportadas para o depósito.\n", self->id);
}

void agv_finaliza(agv_t *self)
{
    /* TODO: Adicionar código aqui se necessário! */
    sem_destroy(&max_agv_pos);
    pthread_mutex_destroy(&recicla);
    pthread_mutex_destroy(&posiciona);
    pthread_join(self->thread, NULL);
    plog("[AGV %u] Finalizado\n", self->id);
}
