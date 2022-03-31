#ifndef __ESTEIRA_H__
#define __ESTEIRA_H__

    #include <pthread.h>
    #include <math.h>
    #include "lampada.h"
    #include <semaphore.h>
    /*============================================================================*
     * DESCRIÇÃO: Representa uma esteira.                                         *
     *============================================================================*/

    #define ESTEIRA_VEL_MIN   1   /* Velocidade mínima da esteira.          */
    #define ESTEIRA_VEL_MAX   10  /* Velocidade máxima da esteira.          */
    #define ESTEIRA_VEL_TEMPO 1   /* Conversor de velocidade em tempo.      */

    /**
     * @brief Define os atributos da esteira.
     */
    typedef struct {
        equipamento_t tipo;               /* Guarda o tipo do equipamento: ESTEIRA. */
        lampada_t *lampadas;              /* Array que armanazena as lâmpadas produzidas. */
        unsigned int lampadas_produzidas; /* Quantidade de lâmpadas produzidas até o momento. */
        unsigned int lampadas_consumidas; /* Quantidade de lâmpadas consumidas até o momento. */
        pthread_t thread;                 /* A thread esteira. */
        
        /* TODO: Adicione aqui os atributos que achar necessários. Esses atributos
        deverão ser usados pelas funções da esteira. */
    } esteira_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa a esteira.
     * 
     * @param self A esteira.
     */
    extern void esteira_inicializa(esteira_t *self);

    /**
     * @brief Função a ser executada pela thread esteira. Implementa o comportamento
     * de uma esteira.
     *
     * @param arg O argumento de entrada da thread, que deverá ser um esteira_t.
     */
    extern void * esteira_executa(void *arg);

    /**
     * @brief Adiciona uma lâmpada na esteira.
     * 
     * @param self A esteira.
     */
    extern void esteira_produz(esteira_t *self);

    /**
     * @brief Remove uma lâmpada da esteira.
     * 
     * @param self A esteira.
     * @return Um ponteiro para a lâmpada removida.
     */
    extern lampada_t * esteira_remove(esteira_t *self); 

    /**
     * @brief Finaliza a esteira.
     * 
     * @param self A esteira.
     */
    extern void esteira_finaliza(esteira_t *self);

    extern void esteira_insere(esteira_t *self);

    extern sem_t para_esteira;

    /*============================================================================*
     * ATENCÃO: Insira aqui funções que você quiser adicionar a interface para    *
     * serem usadas em arquivos que incluem esse header.                          *
     *============================================================================*/

#endif /*__ESTEIRA_H__*/