#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "controle_agvs.h"


void controle_inicializa_agvs(controle_agvs_t * controle, unsigned int quantidade_agvs)
{
    /* TODO: Adicionar código nesta função se necessário! */
    plog("[controle AGVs] Inicializado\n");
    controle->quantidade_agvs = quantidade_agvs;
    controle->agvs = (agv_t *) malloc(sizeof(agv_t) * quantidade_agvs);
    for (int i = 0; i < quantidade_agvs; i++)
        agv_inicializa(&controle->agvs[i], i);

    
}

agv_t * controle_retorna_agv(controle_agvs_t * controle, bool reciclagem)
{
    /* TODO: retornar o AGV posicionado para receber lâmpadas aprovadas no teste (se reciclar==false) 
       ou rejeitadas (se reciclar==true); aguarda o posicionamento de AGVs se necessário */
    //return &controle->agvs[0]; /* Altere para que seja retornado o AGV correto */


    for (int i = 0; i < controle->quantidade_agvs; i++) {
        if (controle->agvs[i].posicionado && controle->agvs[i].reciclar == reciclagem) {
            return(&controle->agvs[i]);
        }
    }
    return NULL;
}
void controle_finaliza_agvs(controle_agvs_t * controle)
{
    /* TODO: Adicionar código nesta função se necessário! */

    for (int i = 0; i < controle->quantidade_agvs; i++)
        agv_finaliza(&controle->agvs[i]);
        
    free(controle->agvs);

    plog("[controle AGVs] Finalizado\n");
}
