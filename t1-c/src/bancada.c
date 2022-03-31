#include <stdlib.h>
#include "bancada.h"
#include <semaphore.h>
#include <pthread.h>


void bancada_inicializa(bancada_t *self)
{

    //sem_init(&bancada, 0, config.capacidade_bancada);
    /* TODO: Adicionar código nesta função se necessário! */
    self->slots_ocupados = 0;
    self->total_testadas = 0;
    self->total_aprovadas = 0;
    self->total_reprovadas = 0;
    self->contador_lampadas = 0;
    self->slots = (lampada_t *) malloc(sizeof(lampada_t) * config.capacidade_bancada);

    plog("[bancada] Inicializada\n");
}

void bancada_insere(bancada_t *self, lampada_t *lampada) 
{
    /* TODO: Adicionar código nesta função se necessário! */
    /* Incrementa a quantidade de slots ocupados na bancada. */
    while (self->slots_ocupados == config.capacidade_bancada) {}
    self->slots[self->slots_ocupados] = *lampada;
    self->slots_ocupados++;
    bancada_testa(self, &self->slots[self->slots_ocupados - 1]);
}

bool bancada_testa(bancada_t *self, lampada_t *lampada)
    /*TESTAR PARA VER SE NÃO EXISTE NENHUM DOS 4 DEFEITOS*/

    /*(1) se o vidro do bulbo da lâmpada está em perfeito estado;*/
    /*(2) se a lâmpada acende; */
    /*(3) se a rosca da lâmpada está em perfeito estado;*/
    /*(4) e se a marca e informações da lâmpada estão impressas no bulbo*/
{
    /* TODO: Adicionar código nesta função se necessário! */

    /* Simula um tempo aleatório de teste da lâmpada. NÃO REMOVER! */
    msleep(rand() % config.tempo_max_teste);

    self->total_testadas++;

    /* Testa se a lâmpada possui algum defeito. */
    if (lampada->bulbo == FALHA || lampada->luz == FALHA || lampada->marca == FALHA || lampada->rosca == FALHA) {
        lampada->resultado_teste = REPROVADA;
        self->total_reprovadas++;
        plog("[bancada] Resultado do teste da lâmpada %u: REPROVADA!\n", lampada->id);
        self->contador_lampadas++;
        return false;
    }

    self->total_aprovadas++;
    lampada->resultado_teste = APROVADA;
    plog("[bancada] Resultado do teste da lâmpada %u: APROVADA!\n", lampada->id);
    self->contador_lampadas++;
    return true;
}


lampada_t * bancada_remove(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    /* Decrementa a quantidade de slots ocupados na bancada. */
    
    lampada_t *lampada_remove;
    // ESSA CONDIÇÃO ERA PRA GARANTIR QUE TERÁ LAMPADAS TESTADAS E ENTRARIA NO IF DO FOR
    while (self->contador_lampadas == 0) {}
    for (int i = 0; i < config.capacidade_bancada; i++) {
        if (self->slots[i].resultado_teste == APROVADA ||
            self->slots[i].resultado_teste == REPROVADA) {
            lampada_remove = &self->slots[i];
            self->slots[i] = self->slots[self->slots_ocupados - 1];
            self->slots_ocupados--;
            self->contador_lampadas--;
            return(lampada_remove);
        }
    }
    return(NULL);
}

void bancada_finaliza(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    free(self->slots);
    plog("[bancada] Finalizada\n");
}

void bancada_imprime_resultados(bancada_t *self) 
{
    printf("\n");
    printf(BAR);
    printf("RESULTADOS DA SIMULAÇÃO\n");
    printf(BAR);
    printf("Lâmpadas testadas  : %u\nLâmpadas aprovadas : %u\nLâmpadas reprovadas: %d\n", self->total_testadas, self->total_aprovadas, self->total_reprovadas);
    printf(BAR);
    printf("\n");
}
