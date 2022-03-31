#include "lampada.h"

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo!  */
/* --------------------------------------------------------- */

void lampada_inicializa(lampada_t *self, unsigned int id, estado_parametro_t bulbo, estado_parametro_t luz, estado_parametro_t rosca, estado_parametro_t marca)
{
    self->id = id;
    self->bulbo = bulbo;
    self->luz = luz;
    self->rosca = rosca;
    self->marca = marca;
    self->resultado_teste = DESCONHECIDO;
}

char * lampada_param_status(estado_parametro_t param) 
{
    if (param == OK)
        return "OK   ";
    
    return "FALHA";
}
