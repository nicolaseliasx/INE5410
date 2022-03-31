#ifndef __BUFFER_H__
#define __BUFFER_H__

    #include "config.h"
    #include "lampada.h"

    /*============================================================================*
     * DESCRIÇÃO: Representa uma buffer.                                          *
     *============================================================================*/

    /**
     * @brief Define os atributos do buffer.
     */
    typedef struct {   
        unsigned int slots_ocupados; /* Quantidade atual de lâmpadas no buffer. */
        lampada_t **slots;           /* Array que armanazena referências para lâmpadas no buffer. */
    
        /* TODO: Adicione aqui os atributos que achar necessários. Esses atributos
        deverão ser usados pelas funções do buffer. */
    } buffer_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa o buffer.
     * 
     * @param self O buffer.
     */
    extern void buffer_inicializa(buffer_t *self);

    /**
     * @brief Insere uma lâmpada no buffer.
     * 
     * @param self O buffer.
     * @param lampada A lâmpada a ser inserida no buffer.
     */
    extern void buffer_insere(buffer_t *self, lampada_t *lampada);

    /**
     * @brief Remove uma lâmpada do buffer.
     * 
     * @param self O buffer.
     * @param lampada A lâmpada a ser removida do buffer.
     * @return Um ponteiro para a lâmpada removida.
     */
    extern lampada_t * buffer_remove(buffer_t *self);

    /**
     * @brief Finaliza o buffer.
     * 
     * @param self O buffer.
     */
    extern void buffer_finaliza(buffer_t *self);

#endif /*__BUFFER_H__*/