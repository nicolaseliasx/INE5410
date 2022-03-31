#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <semaphore.h>
#include <stdbool.h>

extern sem_t ultima_lampada;

/*============================================================================*
 * Configuração                                                               *
 *============================================================================*/

typedef enum {
    ESTEIRA,
    BUFFER,
    BANCADA,
    ROBO,
    AGVS
} equipamento_t;

typedef struct config {
    unsigned int quantidade_lampadas; /* Número de lâmpadas (> 0).                                     */
    unsigned int velocidade_esteira;  /* Velocidade da esteira (de ESTEIRA_VEL_MIN a ESTEIRA_VEL_MAX). */
    unsigned int capacidade_buffer;   /* Capacidade do buffer (> 0).                                   */
    unsigned int capacidade_bancada;  /* Capacidade da bancada de teste (> 0).                         */
    unsigned int tempo_max_teste;     /* Tempo máximo necessário para testar uma lâmpada (> 0).        */
    unsigned int capacidade_agv;      /* Capacidade de cada AGV (> 0).                                 */
    unsigned int quantidade_agvs;     /* Número de AGVs (> 2).                                         */
    unsigned int lampadas_no_agv;
    bool lampada_final;
} config_t;

extern config_t config;

/*============================================================================*
 * Macros                                                                     *
 *============================================================================*/

/**
* @brief Imprime um log em modo debug.
*/
#ifndef NDEBUG
    #define plog(...) printf(__VA_ARGS__); fflush(stdout)
#else
    #define plog(...)
#endif

/**
* @brief Serapador.
*/
#define BAR "=====================================================================\n"


/*============================================================================*
 * Funções                                                                    *
 *============================================================================*/

/**
* @brief Puts the current thread to sleep.
* 
* @param msecs Time in milliseconds.
* 
* @returns 0 em caso de sucesso e -1 em caso de erro.
*/
extern int msleep(long msec);

#endif /*__CONFIG_H__*/