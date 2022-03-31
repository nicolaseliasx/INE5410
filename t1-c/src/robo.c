#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "config.h"
#include "robo.h"

/* VARIAVEIS GLOBAIS DE EXCLUSAO MUTUA*/

pthread_mutex_t agv_coloca;

pthread_mutex_t bancada_mutex;
pthread_mutex_t buffer_mutex;


/* VARIAVEIS GLOBAIS SEMAFOROS PARA CONTROLE DA BANCADA E DO BUFFER*/
sem_t bancada_full;
sem_t bancada_empty;
sem_t buffer_full;
sem_t buffer_empty;



/* VARIAVEIS GLOAIS INTEIROS PARAR CONTAGEM DE LAMPADAS*/
int contador_lampadas_agv = 0;

/* VARIAVEL BOOLEANA GLOBAL PARA INICIALIZAR MUTEXS E SEMAFOROS */
bool inicializa;

void robo_inicializa(robo_t *self, unsigned int id, 
                     void *equipamento_esquerda, equipamento_t tipo_equipamento_esquerda,
                     void *equipamento_direita, equipamento_t tipo_equipamento_direita)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    // INICIALIZAÇÃO DOS MUTEXES E SEMAFOROS
    inicializa = true;
    if (inicializa) {
        inicializa = false;
        config.lampadas_no_agv = 0;
        config.lampada_final = false;

        // SEMAFORO QUE PERMITE A ENTRADA DE NO MAXIMO CAPACIDADE BUFFER
        sem_init(&buffer_empty, 0, config.capacidade_buffer);
        sem_init(&buffer_full, 0, 0);

        // SEMAFORO QUE CONSISTE NA CONDIÇÃO DE PARADA DA BANCADA
        sem_init(&bancada_empty, 0, config.capacidade_bancada);
        sem_init(&bancada_full, 0, 0);

        // EXCLUSAO MUTUA ULTILIZADA NO CONTROLE DOS BRAÇOS PARA ELES NÃO COLIDIREM
        pthread_mutex_init(&agv_coloca, NULL);
        pthread_mutex_init(&bancada_mutex, NULL);
        pthread_mutex_init(&buffer_mutex, NULL);
        
    }
    


    self->id = id;
    self->equipamento_esquerda = equipamento_esquerda;
    self->tipo_equipamento_esquerda = tipo_equipamento_esquerda;
    self->equipamento_direita = equipamento_direita;
    self->tipo_equipamento_direita = tipo_equipamento_direita;

    if (pthread_create(&self->thread, NULL, robo_executa, (void *) self) == 0) {
        plog("[robô %u] Inicializado\n", self->id);
    }
    else {
        plog("[robô %u] Erro ao inicializar o robô\n", self->id);
    }
}


void * robo_executa(void *arg)
{

    int contador_lampadas = 0;
    while (contador_lampadas < config.quantidade_lampadas) {
        
        robo_t *robo = (robo_t *) arg;

        lampada_t *lampada_teste = robo_pega_lampada(robo);
        
        robo_coloca_lampada(robo, lampada_teste);

        contador_lampadas++;
    }

    pthread_exit(NULL);
}

lampada_t * robo_pega_lampada(robo_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    // VARIAVEIS AUXILIAR
    lampada_t *lampada = NULL;

    esteira_t *esteira = NULL;

    switch(self->tipo_equipamento_esquerda) {
        case ESTEIRA:
            esteira = (esteira_t *) self->equipamento_esquerda;
            //lampadas produzidas - consumidar da esteira tem que ser diferente de zero pra ele pegar
            while ((esteira->lampadas_produzidas - esteira->lampadas_consumidas) == 0) {}

            lampada = esteira_remove((esteira_t *) self->equipamento_esquerda);
            plog("[robô %u] Lâmpada %u REMOVIDA da ESTEIRA\n", self->id, lampada->id);
            break;

        case BUFFER:
            //buffer = (buffer_t *) self->equipamento_esquerda;
            // REGIAO CRITICA
            
            sem_wait(&buffer_full);
            pthread_mutex_lock(&buffer_mutex);
            lampada = buffer_remove((buffer_t *) self->equipamento_esquerda);
            plog("[robô %u] Lâmpada %u REMOVIDA do BUFFER\n", self->id, lampada->id);
            pthread_mutex_unlock(&buffer_mutex);
            sem_post(&buffer_empty);
            

            
            
            break;
        case BANCADA:
            //bancada = (bancada_t *) self->equipamento_esquerda;
            // REGIAO CRITICA
            
            sem_wait(&bancada_full);
            pthread_mutex_lock(&bancada_mutex);
            lampada = bancada_remove((bancada_t *) self->equipamento_esquerda);
            plog("[robô %u] Lâmpada %u REMOVIDA da BANCADA\n", self->id, lampada->id);
            pthread_mutex_unlock(&bancada_mutex);
            sem_post(&bancada_empty);
            
            break;
        default:
            plog("[robô %u] Erro ao recuperar equipamento da esquerda\n", self->id);
    }
    
    return(lampada);
}
/*ROBOS QUE COLOCAM E RETIRAM DO BUFFER NAO PODEM ACESSAR  SIMULTANEAMENTE*/
/*ROBOS QUE COLOCAM E RETIRAM DA BANCADA DE TESTE NAO PODEM ACESSAR  SIMULTANEAMENTE*/
void robo_coloca_lampada(robo_t *self, lampada_t *lampada)
{
    controle_agvs_t * controle = NULL;
    agv_t *agv = NULL;
    
    /* TODO: Adicionar código nesta função se necessário! */

    switch(self->tipo_equipamento_direita) {
        case BUFFER:
            
            sem_wait(&buffer_empty);
            pthread_mutex_lock(&buffer_mutex);
            buffer_insere((buffer_t *) self->equipamento_direita, lampada);
            plog("[robô %u] Lâmpada %u INSERIDA no BUFFER\n", self->id, lampada->id);
            pthread_mutex_unlock(&buffer_mutex);
            sem_post(&buffer_full);
            
            
            break;
        case BANCADA:
            
            sem_wait(&bancada_empty);
            pthread_mutex_lock(&bancada_mutex);
            bancada_insere((bancada_t *) self->equipamento_direita, lampada);
            plog("[robô %u] Lâmpada %u INSERIDA na BANCADA\n", self->id, lampada->id);
            pthread_mutex_unlock(&bancada_mutex);
            sem_post(&bancada_full);

            break;
        case AGVS:
            
            controle = (controle_agvs_t *) self->equipamento_direita;
            if (lampada->resultado_teste == DESCONHECIDO) {
                /* Devolve lâmpada para bancada de teste */
                bancada_insere((bancada_t *) self->equipamento_esquerda, lampada);
                plog("[robô %u] Lâmpada %u DEVOLVIDA para a BANCADA\n", self->id, lampada->id);
                break;
            } else if (lampada->resultado_teste == APROVADA) {
                while(agv == NULL)
                    agv = controle_retorna_agv(controle, false); // AGV com lâmpadas aprovadas 
                
            } else {                                         // Lâmpada reprovada no teste
                while(agv == NULL)
                    agv = controle_retorna_agv(controle, true);  // AGV com lâmpadas para reciclar
                
            }

            // FAZER ALGUMA CONDICAO DE VERIFICACAO AQUI
            pthread_mutex_lock(&agv_coloca);
            if (config.lampadas_no_agv == config.quantidade_lampadas - 1) {
                config.lampada_final = true;
                plog("---------ULTIMA LAMPADA DETECTADA--------------\n");
            }
            agv_insere(agv, lampada);
            config.lampadas_no_agv++;
            plog("[robô %u] Lâmpada %u INSERIDA no AGV %u\n", self->id, lampada->id, agv->id);
            pthread_mutex_unlock(&agv_coloca);   
            break;
            

        default:
            plog("[robô %u] Erro ao recuperar equipamento da direita\n", self->id);
    }
}

void robo_finaliza(robo_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    pthread_join(self->thread, NULL);

    /* DESTRUIÇÃO DOS MUTEXES E SEMAFOROS*/

    sem_destroy(&bancada_empty);
    sem_destroy(&bancada_full);
    sem_destroy(&buffer_empty);
    sem_destroy(&buffer_full);
    pthread_mutex_destroy(&buffer_mutex);
    pthread_mutex_destroy(&bancada_mutex);

    plog("[robô %u] Finalizado\n", self->id);
}
