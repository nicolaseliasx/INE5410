from threading import Thread
from time import sleep

import init
from atracao import *
from equipamentos import *

class Funcionario(Thread):
    '''
        Funcionário deve realizar as seguintes ações:
        - Limpar os equipamentos.
        - Descansar.
        A sua responsabilidade é implementar os métodos com o comportamento do
        funcionário, respeitando as restrições impostas no enunciado do trabalho.
 
        Observação: Comente no código qual o objetivo de uma dada operação, 
        ou conjunto de operações, para facilitar a correção do trabalho.        
      
    '''

    # Construtor da classe Funcionario
    def __init__(self, id, equipamento):
        self.id     = id
        self.trabalhando = False
        self.equipamento = equipamento

        super().__init__(name=("Funcionario " + str(id)))

    # Imprime mensagem de log
    def log(self, mensagem):
        espacos = (16 - len(self.name)) * ' '
        print('['+ self.name + '] ' + espacos + mensagem + '\n', end='')

    # Comportamento do Funcionario
    def run(self):
        '''
            NÃO ALTERE A ORDEM DAS CHAMADAS ABAIXO.
        '''
        self.log("Iniciando o expediente. Gerenciando equipamento "+self.equipamento.nome)
        self.trabalhando = True     

        cont_equip_limpos = 0
        while self.trabalhando == True :
            self.limpar_equipamento()
            cont_equip_limpos += 1
            if cont_equip_limpos == init.num_equip_turno:
                self.descansar()
                cont_equip_limpos = 0

        self.log("Terminando o expediente")

    # Funcionário limpa os equipamentos.
    def limpar_equipamento(self):
        sleep(init.tempo_limpeza_equipamento * init.unidade_de_tempo)
        '''
            IMPLEMENTE AQUI:
        '''
        # Errado?
        self.equipamento.limpo = True

    # Funcionário entrega um equipamento para um cliente.
    def entrega_equipamento(self):
        '''
            IMPLEMENTE AQUI:
        '''
        equip = self.equipamento.pegar_equipamento(self.equipamento)
        
        self.log("Entregou "+self.equipamento.nome+" para um cliente.")

        return equip

    # Funcionário recebe um equipamento.
    def recebe_equipamento(self, equip):
        '''
            IMPLEMENTE AQUI:
        '''

        self.log("Recebeu "+self.equipamento.nome+" de um cliente.")

    # Funcionário descansa durante um tempo
    def descansar(self):
        self.log("Hora do intervalo de descanso.")
        sleep(init.tempo_descanso * init.unidade_de_tempo)
        self.log("Fim do intervalo de descanso.")