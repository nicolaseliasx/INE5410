from queue import Queue
import init
from threading import Thread, Semaphore
import threading

class Atracao:
    '''
        Atração representa uma atração do parque. 
        Você deve implementar os métodos que controlam a entrada e saída de
        clientes, respeitando as restrições impostas no enunciado do trabalho.
 
        Observação: Comente no código qual o objetivo de uma dada operação, 
        ou conjunto de operações, para facilitar a correção do trabalho.   
    '''        
    # Construtor da classe que representa uma atração do parque
    def __init__(self, nome_atracao, capacidade_atracao):
        self.nome = nome_atracao              # Nome da atração
        self.capacidade = capacidade_atracao  # Limite de clientes na atração
        self.dentro_atracao = []              # Simula clientes (ids) dentro da atração
        self.disponibilidade_atracao = Semaphore(capacidade_atracao)
        
        
    def entrar_atracao(self, id):
        '''
            IMPLEMENTE AQUI: Entrada do cliente na atração
        '''
        self.disponibilidade_atracao.acquire()
        self.dentro_atracao.append(id)

    def sair_atracao(self):
        '''
            IMPLEMENTE AQUI: Saída do cliente da atracao
        '''
        #LIBERA UMA VAGA
        self.disponibilidade_atracao.release()
        #self.dentro_atracao.remove()
