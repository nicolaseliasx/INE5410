#ifndef __AGV_H__
#define __AGV_H__

    #include <pthread.h>
    #include <stdbool.h>
    #include "config.h"
    #include "lampada.h"
    #include <semaphore.h>

    /*============================================================================*
     * DESCRIÇÃO: Representa um AGV.                                             *
     *============================================================================*/

    /**
     * @brief Define os atributos do AGV.
     */
    typedef struct agv {
        unsigned int id;             /* Identificador único do AGV. */
        void *carga;                 /* Conteúdo do compartimento de carga do AGV. PASSAR MENSAGEM*/
        unsigned int cont_lampadas;  /* Quantidade de lâmpadas no compartimento de carga do AGV. */
        bool posicionado;            /* Indica se o AGV está ao posicionado ao lado do robô para ser carregado com lâmpadas. */
        bool reciclar;               /* Indica se este AVG está com uma carga de lâmpadas que serão recicladas. */
        pthread_t thread;            /* A thread do AGV. */

        /* TODO: Adicione aqui os atributos que achar necessários para implementar o
         comportamento do AGV. Esses atributos deverão ser usados pelas funções do AGV. */
    } agv_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa o AGV.
     * 
     * @param self O AGV.
     * @param id O identificador do AGV.
     */
    extern void agv_inicializa(agv_t *self, unsigned int id);

    /**
     * @brief Função a ser executada pela thread do AGV. Implementa o comportamento
     * de um AGV.
     *
     * @param arg O argumento de entrada da thread, que deverá ser um agv_t.
     */
    extern void * agv_executa(void *arg);

    /**
     * @brief AGV se posiciona próximo ao robô, caso haja lugar disponível, para que 
     * as lâmpadas sejam colocadas no seu compartimento de carga.
     * 
     * @param self O AGV.
     * @param reciclar Indica se o AGV receberá uma carga de lâmpadas reprovadas no
     * teste e que serão recicladas
     */
    extern void agv_posiciona(agv_t *self, bool reciclar);

    /**
     * @brief Aguarda que o compartimento de carga esteja cheio de lâmpadas.
     * 
     * @param self O AGV.
     */
    extern void agv_carrega(agv_t *self);

    /**
     * @brief Robô insere uma lâmpada no compartimento de carga do AVG.
     * 
     * @param self O AGV.
     * @param lampada A lâmpada depositada no compartimento de carga.
     */
    extern void agv_insere(agv_t *self, lampada_t *lampada);

    /**
     * @brief Transporta o pallet cheio para o depósito
     * 
     * @param self O AGV.
     */
    extern void agv_transporta(agv_t *self);

    /**
     * @brief Finaliza o AGV.
     * 
     * @param self O AGV.
     */
    extern void agv_finaliza(agv_t *self);

    /*============================================================================*
     * ATENCÃO: Insira aqui funções que você quiser adicionar a interface para    *
     * serem usadas em arquivos que incluem esse header.                          *
     *============================================================================*/

    
 #endif /*__AGV_H__*/