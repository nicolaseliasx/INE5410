from threading import Thread
from time import sleep
from random import randint

import init
from atracao import *
from equipamentos import *


class Cliente(Thread):
    '''
        Os clientes (frequentadores do parque) realizam as seguintes ações:
        - Vestir os equipamentos de proteção (macacão, luvas, capacete)
        - Ir a uma das atrações:
            - Pista de patinação no gelo:
                - Pegar patins
                - Aguardar vaga na pista
                - Patinar
            - Teleférico:
                - Pagar uma cadeira livre
                - Subir a montanha
                - Ir para uma das pistas ou permanecer no teleférico
            - Pista de snowboad:
                - Pegar uma prancha
                - Aguardar vaga
                - Descer a montanha
                - Devolver equipamento, caso deixe a atração
            - Pista de esqui:
                - Pegar esquis
                - Aguardar vaga
                - Descer a montanha
                - Devolver equipamento, caso deixe a atração
            - Pistas de trenó (skeleton):
                - Pegar trenó
                - Aguardar pista livre
                - Descer a montanha
                - Devolver o equipamento
            - Pistas de bobsled:
                - Formar dupla
                - Pegar bobsled
                - Aguardar pista livre 
                - Descer a montanha
                - Devolver o equipamento
        - Decidir aleatoriamente se permanece, se vai para outra atração ou vai embora

        Cada uma dessas ações corresponde a um método do cliente. A sua responsabilidade 
        é desenvolver os comportamentos dentro dos métodos do cliente de modo que ele se
        comporte conforme a especificação contida no Moodle.

        Esses métodos são chamados no método run() da classe Cliente.
 
        Observação: Comente no código qual o objetivo de uma dada operação, 
        ou conjunto de operações, para facilitar a correção do trabalho.           
    '''
    # Construtor do cliente
    # blah blah ALTERADO em 5/03 (correção do comentário)
    def __init__(self, id):
        self.id     = id

        super().__init__(name=("Cliente " + str(id)))
        # NOVO 

    # Função que imprime mensagens de log
    def log(self, mensagem):
        espacos = (16 - len(self.name)) * ' '
        print('['+ self.name + '] ' + espacos + mensagem + '\n', end='')

    # Representação do cliente nas mensagens de log
    def __repr__(self):
        return self.name

    # Comportamento do cliente
    def run(self):
        '''
            NÃO ALTERE A ORDEM DAS CHAMADAS ABAIXO.
        '''
        self.log("Entrou no Winter Park.")

        self.pegar_equip_protecao()

        while True:
            if randint(1,3) == 1:
                # Vai para pista de patinação
                self.pegar_patins()
                self.aguardar_lugar_pista()
                while True:
                    self.patinar()
                    if randint(1,3) == 1:
                        break
                self.devolver_patins()
            else:
                # Pega o teleférico para subir a montanha
                self.pegar_teleferico()
                self.aguardar_subida()
                if randint(1,5) == 1:
                    # Desce de teleférico
                    self.aguardar_descida()
                    self.sair_teleferico()
                else:
                    self.sair_teleferico()
                    if randint(1,2) == 1:
                    # Vai para o lado sul - esqui e snowboard
                        if randint(1,2) == 1:
                            # Esquiar
                            self.pegar_esquis()
                            while True:
                                self.aguardar_lugar_montanha_sul()  
                                self.descer_esquiando()  
                                if randint(1,2) == 1:
                                    self.pegar_teleferico()
                                    self.aguardar_subida()
                                    self.sair_teleferico()             # ALTERADO 2/03         
                                else:
                                    self.devolver_esquis()
                                    break
                        else:
                            # Sandboard
                            self.pegar_snowboard()
                            while True:
                                self.aguardar_lugar_montanha_sul()  
                                self.descer_snowboard()   
                                if randint(1,2) == 1:
                                    self.pegar_teleferico()
                                    self.aguardar_subida()
                                    self.sair_teleferico()             # ALTERADO 2/03         
                                else:
                                    self.devolver_snowboard()
                                    break                                             
                    else:
                        # Vai para o lado norte - trenó e bobsled
                        if randint(1,3) == 1:
                            # Bobsled
                            while True:                         # ALTERADO 5/03
                                self.formar_dupla()             # ALTERADO 5/03
                                self.pegar_bobsled()            # ALTERADO 5/03
                                self.aguardar_pista_bobsled()  
                                self.descer_bobsled()  
                                self.devolver_bobsled()
                                if randint(1,2) == 1:
                                    self.pegar_teleferico()
                                    self.aguardar_subida()
                                    self.sair_teleferico()      # ALTERADO 2/03               
                                else:
                                    break                        
                        else:
                            # Trenó   
                            while True:                         # ALTERADO 5/03
                                self.pegar_treno()              # ALTERADO 5/03
                                self.aguardar_pista_treno()  
                                self.descer_treno()  
                                self.devolver_treno()
                                if randint(1,2) == 1:
                                    self.pegar_teleferico()
                                    self.aguardar_subida()
                                    self.sair_teleferico()      # ALTERADO 2/03               
                                else:
                                    break                   

            if randint(1,5) == 1: 
                # Devolve o kit de equipamentos de proteção
                self.devolver_equip_protecao()
                # Vai embora
                self.log("Saiu do Winter Park.")
                return

    # Simula o tempo de uso de uma atração
    def tempo_atracao(self):
        sleep(randint(init.tempo_atracao_min, init.tempo_atracao_max) * init.unidade_de_tempo)
        
    # Cliente pega um kit com os equipamentos de proteção
    def pegar_equip_protecao(self):
        '''
            IMPLEMENTE AQUI:
            O cliente pega um kit com os equipamentos de proteção.
        '''
        # Chamando metodos


        self.equip_atual = init.funcionarios[0].entrega_equipamento()
        
        self.log("Pegou um kit com equipamentos de proteção.")
        
    # Cliente devolve um kit com os equipamentos de proteção
    def devolver_equip_protecao(self):
        '''
            IMPLEMENTE AQUI:
            O cliente devolve um kit com os equipamentos de proteção.
        '''

        
        init.funcionarios[0].recebe_equipamento(self.equip_atual)
        self.log("Devolveu um kit com equipamentos de proteção.")


    # Cliente pega um par de patins para usar a pista de patinação
    def pegar_patins(self):
        '''
            IMPLEMENTE AQUI:
            O cliente pega um par de patins para patinar no gelo.
        '''
    

        self.equip_atual = init.funcionarios[1].entrega_equipamento()

        self.log("Pegou um par de patins.")

    # Cliente pega uma prancha de snowboard
    def patinar(self):
        self.log("Está patinando.")
        self.tempo_atracao()

        init.atracoes[0].sair_atracao()

        

    # Cliente devolver os patins que estava usando
    def devolver_patins(self):
        '''
            IMPLEMENTE AQUI:
            O cliente devolve os patins que usou na pista de patinação.
        '''
    
        init.funcionarios[1].recebe_equipamento(self.equip_atual)
        self.log("Devolveu um par de patins.")

    # Cliente aguarda que haja lugar na pista de patinação         
    def aguardar_lugar_pista(self):
        '''
            IMPLEMENTE AQUI:
            O cliente deve aguardar que haja uma vaga para entrar na pista de patinação.
        '''
        
        init.atracoes[0].entrar_atracao(self.id)

        self.log("Entrou na pista de patinação.")
        self.patinar()#nesse metodo ta o semaforo que libera uma vaga quandoa caba

    # Cliente aguarda um lugar no teleférico
    def pegar_teleferico(self):
        '''
            IMPLEMENTE AQUI:
            O cliente deve aguardar que haja uma cadeira vaga para andar no teleférico.
        '''
        # PEGA UMA VAGA DO TELEFERICO
        init.atracoes[1].entrar_atracao(self.id)


        self.log("Pegou cadeira no teleférico.")
        self.aguardar_subida()
        self.aguardar_descida()

    # Cliente deve aguardar a subida do teleférico
    def aguardar_subida(self):
        self.tempo_atracao() 
        self.log("Chegou ao topo da montanha de teleférico.")

    # Cliente deve aguardar a descida do teleférico 
    def aguardar_descida(self):
        self.tempo_atracao()     
        self.log("Desceu a montanha de teleférico.")

     # Cliente libera seu lugar no teleférico
    def sair_teleferico(self):
        '''
            IMPLEMENTE AQUI:
            O cliente libera a cadeira que usou para andar no teleférico.
        '''
        self.log("Liberou uma cadeira no teleférico.")

        # AUMENTA 1 CAPACIDADE DO TELEFERICO
        init.atracoes[1].sair_atracao()
        
    # Cliente pega esquis
    def pegar_esquis(self):
        '''
            IMPLEMENTE AQUI:
            O cliente pega um par de esquis para usar.
        '''

        self.equip_atual = init.funcionarios[2].entrega_equipamento()

        self.log("Pegou esquis.")

    # Cliente aguarda para poder esquiar na montanha
    def aguardar_lugar_montanha_sul(self):
        '''
            IMPLEMENTE AQUI:
            Aguardar que haja uma vaga para esquiar.
        '''  

        # PEGA UMA VAGA DA MONTANHA SUL
        init.atracoes[2].entrar_atracao(self.id)


        self.log("Conseguiu lugar na montanha sul.")
      

    # Cliente desce a montanha esquiando
    def descer_esquiando(self):
        self.log("Começa a descer a montanha esquiando.")
        self.tempo_atracao()
        self.log("Terminou de descer a montanha esquiando.")


        init.atracoes[2].sair_atracao()

     # Cliente devolve os esquis
    def devolver_esquis(self):
        '''
            IMPLEMENTE AQUI:
            O cliente pega um par de esquis para usar.
        ''' 
        
        init.funcionarios[2].recebe_equipamento(self.equip_atual) 
        self.log("Devolveu os esquis.")
        
    # Cliente pega uma prancha de snowboard
    def pegar_snowboard(self):
        '''
            IMPLEMENTE AQUI:
            O cliente pega uma prancha de snowboard.
        '''

        self.equip_atual = init.funcionarios[3].entrega_equipamento()
        self.log("Pegou um snowboard.")
        
    # Cliente desce a montanha com uma prancha de snowboard
    def descer_snowboard(self):
        self.log("Começou a descer a pista de snowboard.")       
        self.tempo_atracao()
        self.log("Desceu a pista de snowboard.")

        init.atracoes[2].sair_atracao()

    # Cliente devolve uma prancha de snowboard
    def devolver_snowboard(self):
        '''
            IMPLEMENTE AQUI:
            O cliente devolve uma prancha de snowboard.
        '''
        
        init.funcionarios[3].recebe_equipamento(self.equip_atual)
        self.log("Devolveu um snowboard.")

    # Cliente aguarda formação da dupla
    def formar_dupla(self):
        '''
            IMPLEMENTE AQUI:
            O cliente aguarda que outro cliente forme uma dupla com ele.
        '''


        #APENAS UMA DECIDA DE CADA VEZ

        # NAO SEI OQUE FAZ ESSE METODO AQUI
        # DIVIDIR POR DOIS QUANTIDADE DE PESSOAS QUE PODEM DESCER DE BOB (QUANTIDADE DA MONTANHA NORTE)?

        # um se junta ao outro formando uma dupla
        init.mutex_duplas.acquire()
        init.capacidade_montanha_norte -= 1
        init.mutex_duplas.release()
        
        self.log("Formou uma dupla para descer a montanha no bobsled.")
        

    # Cliente aguarda um bobsled livre para descer a montanha
    def pegar_bobsled(self):
        '''
            IMPLEMENTE AQUI:
            O cliente aguarda que haja um bobsled livre para descer a montanha.
        '''
        
        #self.bobsled = Equipamentos(init.nome_equipamentos[4], init.quant_bobsleds)

        # COLOCAR SEMAFORO + MUTEX PRA ACESSAR CORRETAMENTE AQUI 666666666666666666666666666666

        self.equip_atual = init.funcionarios[4].entrega_equipamento()
        self.log("Pegou um bobsled.")

    # Cliente aguarda uma pista de bobsled livre para descer a montanha
    def aguardar_pista_bobsled(self):
        self.log("Aguarda por uma pista de bobsled.")
        '''
            IMPLEMENTE AQUI:
            O cliente aguarda que haja uma pista de bobsled livre para descer a montanha.
        '''
        # SEMAFORO QTDD DE VAGAS MONTANHA NORTE
        # 2 ACQUIRE POR SE TRATAR DE UMA DUPLA
        #-------------------------------------------------#-------------------------------------------------
        init.sem_1_descida_norte.acquire()
        init.mutex_1_descida_norte.acquire()

        init.atracoes[2].entrar_atracao(self.id)

        init.sem_1_descida_norte.release()
        init.mutex_1_descida_norte.release()

        self.log("Conseguiu uma pista de bobsled.")

     # Cliente desce a montanha de bobsled
    def descer_bobsled(self):
        self.log("Começou a descer a pista de bobsled.")
        '''
            IMPLEMENTE AQUI:
            O cliente desce a pista de bobsled.
        '''
        # LIBERA DUAS VAGAS
        # 2 RELEASE POR SE TRATAR DE UMA DUPLA
        #-------------------------------------------------#-------------------------------------------------
        init.sem_1_descida_norte.acquire()
        init.mutex_1_descida_norte.acquire()

        init.atracoes[2].sair_atracao()

        init.sem_1_descida_norte.release()
        init.mutex_1_descida_norte.release()
        
        self.log("Terminou de descer a pista de bobsled.")       
 
   # Cliente devolve o bobsled que usou para descer a montanha
    def devolver_bobsled(self):
        '''
            IMPLEMENTE AQUI:
            O cliente devolveu o bobsled usado para descer a montanha.
        '''
        # COLOCAR SEMAFORO + MUTEX PRA ACESSAR CORRETAMENTE AQUI 666666666666666666666666666666
        init.funcionarios[4].recebe_equipamento(self.equip_atual)
        self.log("Devolveu um bobsled.")

    # Cliente aguarda um trenó livre para descer a montanha
    def pegar_treno(self):
        '''
            IMPLEMENTE AQUI:
            O cliente aguarda que haja um trenó livre para descer a montanha.
        '''
        #self.treno = Equipamentos(init.nome_equipamentos[5], init.quant_trenos)

        self.equip_atual = init.funcionarios[5].entrega_equipamento()
        self.log("Pegou um trenó.")

    # Cliente aguarda uma pista de trenó livre para descer a montanha
    def aguardar_pista_treno(self):
        self.log("Aguarda por uma pista de trenó.")
        '''
            IMPLEMENTE AQUI:
            O cliente aguarda que haja uma pista de trenó livre para descer a montanha.
        '''
        # OBTEM UMA VAGA
        #-------------------------------------------------#-------------------------------------------------
        init.sem_1_descida_norte.acquire()
        init.mutex_1_descida_norte.acquire()

        init.atracoes[3].entrar_atracao(self.id)

        init.sem_1_descida_norte.release()
        init.mutex_1_descida_norte.release()

        self.log("Conseguiu uma pista de trenó.")

     # Cliente desce a montanha de trenó
    def descer_treno(self):
        self.log("Começou a descer a pista de trenó.")
        self.tempo_atracao()
        self.log("Terminou de descer a pista de trenó.") 

        # LIBERA UMA VAGA
        #-------------------------------------------------#-------------------------------------------------
        init.sem_1_descida_norte.acquire()
        init.mutex_1_descida_norte.acquire()

        init.atracoes[3].sair_atracao()

        init.sem_1_descida_norte.release()
        init.mutex_1_descida_norte.release()
 
   # Cliente devolve o trenó que usou para descer a montanha
    def devolver_treno(self):
        '''
            IMPLEMENTE AQUI:
            O cliente devolveu o trenó usado para descer a montanha.
        '''
        init.funcionarios[5].recebe_equipamento(self.equip_atual)
        self.log("Devolveu um trenó.")