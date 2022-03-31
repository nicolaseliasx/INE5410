#ifndef __CONTROLE_AGVS_H__
#define __CONTROLE_AGVS_H__

    #include <pthread.h>
    #include <stdbool.h>
    #include "config.h"
    #include "agv.h"
    #include <semaphore.h>

    /*============================================================================*
     * DESCRIÇÃO: Coordena o funcionamento dos AGVs.                               *
     *============================================================================*/
    /**
     * @brief Define os atributos do controlador de AGVs.
     */
    typedef struct {
        unsigned int quantidade_agvs;  /* Quantidade de AGVs controlados. */
        agv_t *agvs;                   /* Array com todos os AGVs da fábrica. */
       
        /* TODO: Adicione aqui os atributos que achar necessários. */
    } controle_agvs_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa o Controle de AGVs.
     * 
     * @param controle Controle dos AGVs da fábrica.
     * @param quantidade_agvs Quantidade de AGVs a serem inicializados.
     */
    extern void controle_inicializa_agvs(controle_agvs_t *controle, unsigned int quantidade_agvs);

    /**
     * @brief Obtém o AGV posicionado para receber lâmpadas
     * 
     * @param controle Controle dos AGVs da fábrica.
     * @param reciclagem Indica se o AGV desejado é o com lâmpadas para reciclagem.
     * @return Um ponteiro para um AGV.
     */
    extern agv_t * controle_retorna_agv(controle_agvs_t *controle, bool reciclagem);

    /**
     * @brief Finaliza todos os AGVs da fábrica.
     * 
     * @param controle Controle dos AGVs da fábrica.
     */
    extern void controle_finaliza_agvs(controle_agvs_t *controle);

    /*============================================================================*
     * ATENCÃO: Insira aqui funções que você quiser adicionar a interface para    *
     * serem usadas em arquivos que incluem esse header.                          *
     *============================================================================*/



    extern sem_t max_agv_pos;
    extern pthread_mutex_t recicla;

 #endif /*__CONTROLE_AGVS_H__*/