#ifndef __BANCADA_H__
#define __BANCADA_H__

    #include <stdbool.h>
    #include "config.h"
    #include "lampada.h"

    /*============================================================================*
     * DESCRIÇÃO: Representa uma bancada de teste.                                *
     *============================================================================*/

    /**
     * @brief Define os atributos da bancada de teste.
     */
    typedef struct {   
        unsigned int slots_ocupados;   /* Quantidade atual de lâmpadas na bancada de teste. */
        unsigned int total_testadas;   /* Número total de lâmpadas testadas. */
        unsigned int total_aprovadas;  /* Número total de lâmpadas aprovadas no teste. */
        unsigned int total_reprovadas; /* Número total de lâmpadas reprovadas no teste. */
        unsigned int contador_lampadas;
        lampada_t *slots;              /* Array que armanazena as lâmpadas na bancada de teste. */
    } bancada_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa a bancada de teste.
     * 
     * @param self A bancada.
     */
    extern void bancada_inicializa(bancada_t *self);

    /**
     * @brief Insere uma lâmpada na bancada de teste.
     * 
     * @param self A bancada.
     * @param lampada A lâmpada a ser inserida na bancada.
     */
    extern void bancada_insere(bancada_t *self, lampada_t *lampada);

    /**
     * @brief Testa a lâmpada, verificando se há algum defeito.
     * 
     * @param self A bancada.
     * @param lampada A lâmpada a ser testada.
     * @return Retorna TRUE se a lâmpada foi aprovada no teste. Caso contrário, retorna FALSE.
     */
    extern bool bancada_testa(bancada_t *self, lampada_t *lampada);
    
    /**
     * @brief Remove uma lâmpada da bancada de teste.
     * 
     * @param self A bancada.
     * @param lampada A lâmpada a ser removida da bancada.
     * @return Um ponteiro para a lâmpada removida.
     */
    extern lampada_t * bancada_remove(bancada_t *self);

    /**
     * @brief Finaliza a bancada de teste.
     * 
     * @param self A bancada.
     */
    extern void bancada_finaliza(bancada_t *self);

    /**
     * @brief Imprime estatíscas da bancada.
     * 
     * @param self A bancada.
     */
    extern void bancada_imprime_resultados(bancada_t *self);

#endif /*__BANCADA_H__*/