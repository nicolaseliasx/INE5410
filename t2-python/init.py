from queue import Queue
from threading import Semaphore, Lock, Condition
from time import sleep
from random import randint
import sys, argparse

from cliente import *
from funcionario import *
from atracao import *
from equipamentos import *

# Limites de tempo para criação de clientes e uso das atrações
tempo_cliente_min           = 5
tempo_cliente_max           = 15
tempo_atracao_min           = 10
tempo_atracao_max           = 20                           

# Atrações do parque
capacidade_patinacao        = 6
capacidade_teleferico       = 12
capacidade_montanha_sul     = 8
capacidade_montanha_norte   = 5 
nome_atracoes               = ["pista de patinação", "teleférico", "pista esqui e snowboard","pistas bobsled e trenó"]
capacidade_atracoes         = [capacidade_patinacao, capacidade_teleferico, capacidade_montanha_sul, capacidade_montanha_norte]
atracoes                    = [Atracao(nome_atracoes[0], capacidade_atracoes[0]),
                                Atracao(nome_atracoes[1], capacidade_atracoes[1]),
                                Atracao(nome_atracoes[2], capacidade_atracoes[2]),
                                Atracao(nome_atracoes[3], capacidade_atracoes[3])] 

# Equipamentos do parque
quant_equip_protecao        = 40
quant_patins                = 8
quant_esquis                = 5
quant_snowboards            = 4
quant_bobsleds              = 2
quant_trenos                = 6 
nome_equipamentos           = ["equip. proteção", "patins", "esquis", "snowboard", "bobsled", "trenó"]
quant_equipamentos          = [quant_equip_protecao, quant_patins, quant_esquis, quant_snowboards, 
                               quant_bobsleds, quant_trenos]
#coloquei aqui ara conseguir acessar
equipamentos                = [Equipamentos(nome_equipamentos[0], quant_equipamentos[0]),
                                Equipamentos(nome_equipamentos[1], quant_equipamentos[1]),
                                Equipamentos(nome_equipamentos[2], quant_equipamentos[2]),
                                Equipamentos(nome_equipamentos[3], quant_equipamentos[3]),
                                Equipamentos(nome_equipamentos[4], quant_equipamentos[4]),
                                Equipamentos(nome_equipamentos[5], quant_equipamentos[5])] 

# Tempo total de simulação. Encerrado esse tempo, não crie mais clientes.
tempo_total                 = 1000

# Uma unidade de tempo de simulação. Quanto menor, mais rápida a execução.
unidade_de_tempo            = 0.1 # 100ms

# Parâmetros de funcionamento do funcionário
tempo_limpeza_equipamento   = 4
# ALTERADO 5/03
funcionarios                = [] # Lista com todos os funcionários do parque
num_equip_turno             = 50 # Número de equipamentos limpos a cada turno
tempo_descanso              = 10 # Tempo de descanso entre dois turnos de trabalho

# Defina aqui outras varíaveis e estruturas globais necessárias para implementação do programa

sem_limpeza = Semaphore(0)

sem_1_descida_norte = Semaphore(1)
mutex_1_descida_norte = Lock()

mutex_duplas = Lock()


# Criação dos funcionários
for i in range(1,7):
    func = Funcionario(i,equipamentos[i-1])
    funcionarios.append(func)

if __name__ == "__main__":
    # Verifica a versão do python
    if sys.version_info < (3, 0):
        sys.stdout.write('Utilize python3 para desenvolver este trabalho\n')
        sys.exit(1)

    # Processa os argumentos de linha de comando
    parser = argparse.ArgumentParser()
    parser.add_argument("--unidade_de_tempo", "-u", help="valor da unidade de tempo de simulação")
    parser.add_argument("--tempo_total", "-t", help="tempo total de simulação")
    parser.add_argument("--tempo_cliente_min", "-tcmin", help="tempo mínimo para entrada de clientes")
    parser.add_argument("--tempo_cliente_max", "-tcmax", help="tempo máximo para entrada de clientes")
    parser.add_argument("--tempo_atracao_min", "-tamin", help="tempo mínimo para uso de uma atração")
    parser.add_argument("--tempo_atracao_max", "-tamax", help="tempo máximo para uso de uma atração")
    parser.add_argument("--tempo_trabalho", "-ttrab", help="tempo de cada turno de trabalho do funcionário")
    parser.add_argument("--tempo_descanso", "-tdesc", help="tempo de descanso do funcionário entre turnos de trabalho")

    args = parser.parse_args()
    if args.unidade_de_tempo:
        unidade_de_tempo = float(args.unidade_de_tempo)
    if args.tempo_total:
        tempo_total = int(args.tempo_total)
    if args.tempo_cliente_min:
        tempo_cliente_min = int(args.tempo_cliente_min)
    if args.tempo_cliente_max:
        tempo_cliente_max = int(args.tempo_cliente_max)
    if args.tempo_atracao_min:
        tempo_atracao_min = int(args.tempo_atracao_min)
    if args.tempo_atracao_max:
        tempo_atracao_max = int(args.tempo_atracao_max)
    if args.tempo_trabalho:
        tempo_trabalho = int(args.tempo_trabalho)
    if args.tempo_descanso:
        tempo_descanso = int(args.tempo_descanso)

    # Tempo desde a abertura do parque
    tempo = 0

    # Varíaveis locais usadas pelo programa
    clientes = []                 # Lista com todos os clientes que entraram no parque
    cont_clientes = 0             # Contador de clientes que entraram no parque
    # IMPLEMENTE AQUI: crie outras varíaveis, se necessário
    



    # MOVIDAS DIRETO PRO ARRAY, POR ALGUM MOTIVO O ARRAY ESTAVA CHEGANDO NO CLIENTE VAZIO
    # Criação das atrações
    #for i in range(1,5):
        #atr = Atracao(nome_atracoes[i-1], capacidade_atracoes[i-1])
        #atracoes.append(atr)

    #lista ficando sempre vazia
    #for i in range(1,7):
        #equip = Equipamentos(nome_equipamentos[i-1], quant_equipamentos[i-1])
        #equipamentos.append(equip)
    
    # Inicio
    for i in range(1,7):
        funcionarios[i-1].start()
  
    # Enquanto o tempo total de simuação não for atingido
    while tempo < tempo_total:
        # IMPLEMENTE AQUI: Criação de um cliente
        cont_clientes += 1
        cliente = Cliente(cont_clientes)
        cliente.start()
        clientes.append(cliente)

        # Aguarda um tempo aleatório antes de criar o próximo cliente
        intervalo = randint(tempo_cliente_min, tempo_cliente_max)  
        sleep(intervalo * unidade_de_tempo)     
        # Atualiza a variável tempo considerando o intervalo de criação dos cliente
        tempo += intervalo

    # Faça o funcionário parar de trabalhar assim que terminar o que estiver fazendo  
    for i in range(1,7):
        funcionarios[i-1].trabalhando = False

    # Aguarde a finalização (término) de todos os clientes e funcionários 
    # antes de finalizar a execução do programa.

    # COMO FINALIZAR O PROGRAMA?

    for cliente in clientes:
        cliente.join()

    for i in range(1,7):
        funcionarios[i-1].join()