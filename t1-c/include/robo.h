#ifndef __ROBO_H__
#define __ROBO_H__

    #include <pthread.h>
    #include "config.h"
    #include "esteira.h"
    #include "buffer.h"
    #include "bancada.h"
    #include "agv.h"
    #include "controle_agvs.h"

    /*============================================================================*
     * DESCRIÇÃO: Representa um robô.                                             *
     *============================================================================*/

    /**
     * @brief Define os atributos do robô.
     */
    typedef struct {
        unsigned int id;                         /* Identificador único do robô. */
        void *equipamento_esquerda;              /* Referência para o equipamento à esquerda do robô. */
        equipamento_t tipo_equipamento_esquerda; /* Tipo do equipamento à esquerda do robô. */
        void *equipamento_direita;               /* Referência para o equipamento à direita do robô. */
        equipamento_t tipo_equipamento_direita;  /* Tipo do equipamento à direita do robô. */
        pthread_t thread;                        /* A thread robô. */
        
        /* TODO: Adicione aqui os atributos que achar necessários. Esses atributos
        deverão ser usados pelas funções do robô. */
    } robo_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa o robô.
     * 
     * @param self O robô.
     * @param id O identificador do robô.
     * @param equipamento_esquerda O equipamento que está à esquerda do robô.
     * @param tipo_equipamento_esquerda O tipo do equipamento que está à esquerda do robô.
     * @param equipamento_direita O equipamento que está à direita do robô.
     * @param tipo_equipamento_direita O tipo do equipamento que está à direita do robô.
     */
    extern void robo_inicializa(robo_t *self, unsigned int id, void *equipamento_esquerda, equipamento_t tipo_equipamento_esquerda, void *equipamento_direita, equipamento_t tipo_equipamento_direita);

    /**
     * @brief Função a ser executada pela thread robô. Implementa o comportamento
     * de um robô.
     *
     * @param arg O argumento de entrada da thread, que deverá ser um robo_t.
     */
    extern void * robo_executa(void *arg);

    /**
     * @brief Pega uma lâmpada do equipamento à esquerda do robô.
     * 
     * @param self O robô.
     * @return Um ponteiro para a lâmpada removida do equipamento.
     */
    extern lampada_t * robo_pega_lampada(robo_t *self);

    /**
     * @brief Colova uma lâmpada no equipamento à direita do robô.
     * 
     * @param self O robô.
     */
    extern void robo_coloca_lampada(robo_t *self, lampada_t *lampada);

    /**
     * @brief Finaliza o robô.
     * 
     * @param self O robô.
     */
    extern void robo_finaliza(robo_t *self);

    /*============================================================================*
     * ATENCÃO: Insira aqui funções que você quiser adicionar a interface para    *
     * serem usadas em arquivos que incluem esse header.                          *
     *============================================================================*/

#endif /*__ROBO_H__*/