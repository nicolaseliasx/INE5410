import init
from threading import Thread, Semaphore
from queue import Queue

class Equipamentos:
    '''
        Equipamentos representa um conjunto de equipamentos de um determinado tipo. 
        Você deve implementar os métodos que controlam a entrega e devolução de
        equipamentos, respeitando as restrições impostas no enunciado do trabalho.
    '''    
    # Construtor da classe que representa um conjunto de equipamentos
    def __init__(self, nome_equipamento, quant_equipamentos):
        self.nome = nome_equipamento
        self.quantidade = quant_equipamentos
        self.disponibilidade_equip = Semaphore(self.quantidade)
        self.dentro_atracao = []
        self.limpo = False
        
    def pegar_equipamento(self, equip):
        '''
            IMPLEMENTE AQUI: Entrega de um equipamento
        '''
        self.disponibilidade_equip.acquire()
        self.dentro_atracao.append(equip)

    def devolver_equipamento(self):
        '''
            IMPLEMENTE AQUI: Devolução de um equipamento
        '''  
        # LIBERA UMA VAGA

        self.disponibilidade_equip.release()
        #self.dentro_atracao.remove(-1)
