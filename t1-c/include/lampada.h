#ifndef __LAMPADA_H__
#define __LAMPADA_H__

    #include "config.h"

    /*============================================================================*
     * DESCRIÇÃO: Representa uma lâmpada.                                         *
     *============================================================================*/

    typedef enum {
        DESCONHECIDO,
        APROVADA,
        REPROVADA
    } estado_teste_t;

    typedef enum {
        OK,
        FALHA
    } estado_parametro_t;

    /**
     * @brief Define os atributos da lâmpada.
     */
    typedef struct {
        unsigned int id;                /* Identificador único da lâmpada. */
        estado_parametro_t bulbo;       /* Indica se o bulbo da lâmpada está em perfeito estado. */
        estado_parametro_t luz;         /* Indica se a lâmpada acende. */
        estado_parametro_t rosca;       /* Indica se a rosca da lâmpada está em perfeito estado. */
        estado_parametro_t marca;       /* Indica se a marca e informações da lâmpada estão impressas no bulbo. */
        estado_teste_t resultado_teste; /* Indica o estado da lâmpada após o teste na bancada. */
    } lampada_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa a lâmpada.
     * 
     * @param self A lâmpada.
     * @param id O identificador da lâmpada.
     * @param bulbo Indica se o bulbo da lâmpada está em perfeito estado.
     * @param luz Indica se a lâmpada acende.
     * @param rosca Indica se a rosca da lâmpada está em perfeito estado.
     * @param estado_parametro_t marca;
     */
    extern void lampada_inicializa(lampada_t *self, unsigned int id, estado_parametro_t bulbo, estado_parametro_t luz, estado_parametro_t rosca, estado_parametro_t marca);

    /**
     * @brief Converte um estado_parametro_t em string.
     * 
     * @param param Uma variável do tipo estado_parametro_t.
     * @return Retorna a string "OK" se param == OK. Caso contrário, retorna a string "FALHA".
     */
    extern char * lampada_param_status(estado_parametro_t param);

#endif /*__LAMPADA_H__*/