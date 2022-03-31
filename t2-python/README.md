# Trabalho 2 de INE5410
O Trabalho 2 da disciplina de Programação Concorrente (INE5410) consiste em desenvolver um sistema concorrente em Python que simula o funcionamento de um parque indoor de esportes de inverno, chamado Winter Park, que será construído na região serrana de Santa Catarina. Para que as autoridades locais emitam as licenças de funcionamento do parque, foi solicitado aos construtores que comprovem, por meio de simulações, qual o número máximo de clientes que podem ingressar no parque sem que ocorram filas e superlotação. Sua empresa foi contratada para construir este simulador, e foi decidido pelo seu gerente de projeto que o simulador será programado em Python. 

Os clientes, ao chegar ao parque, devem primeiramente pegar um kit de equipamentos de proteção, devidamente higienizados, contendo capacete, macacão e luvas, já que a temperatura dentro do parque é de -5ºC. Após se vestirem, os clientes podem se dirigir às atrações do parque.

No parque existem 4 atrações diferentes:

pista de patinação no gelo: situada na parte inferior do parque, com capacidade limitada de clientes por medida de segurança;
teleférico: conduz os clientes até o alto da montanha em cadeiras suspensas individuais.
pista de esqui e snowboard: pista localizada no lado sul da montanha, com capacidade limitada de clientes simultâneos;
pistas de trenó e bobsled: pistas situadas no lado norte da montanha, nas quais é permitida a descida de somente um trenó ou bobsled por vez em cada pista. 
Caso uma atração esteja lotada, os clientes devem esperar em uma fila para ter acesso à atração.

Após visitarem uma das atrações, os clientes devem decidir de forma aleatória se permanecerão na atração, se irão para outra atração ou se sairão  do parque. 

Os seguintes equipamentos são emprestados aos clientes do parque:

equipamentos de proteção: macacão, luva e capacete; devem ser usados durante todo o tempo de permanência no parque e devolvidos na saída;
patins: utilizados na pista de patinação (suponha que o tamanho dos patins é ajustável, ou seja, eles servirão em qualquer cliente); 
jogo de esquis: usados para descer o lado sul da montanha (também ajustáveis, com tamanho único);
pranchas de snowboard: idem anterior;
trenó (skeleton): equipamento de uso individual, para descer as pistas do lado norte da montanha (os iniciantes descem sentados confortavelmente no trenó, enquanto os mais experientes deitam de bruços no trenó e se jogam de cabeça); 
bobsled: equipamento com capacidade para duas pessoas, usado para descer as pistas do lado norte.
Existe um número limitado de equipamentos, que são emprestados aos clientes pelos funcionários do parque. Caso o cliente necessite de um equipamento que não está disponível em um determinado momento, ele deve aguardar em uma fila. Clientes que tiverem descido a pista de esqui e snowboard devem permanecer com os equipamentos caso desejem subir a montanha no teleférico e descer novamente a pista, devendo devolver os equipamentos somente quando quiserem ir para outra área do parque; já os trenós e bobsleds devem ser devolvidos após cada descida, sendo necessário pegar outro equipamento cada vez que o cliente quiser descer a montanha. 

Ao serem devolvidos, os equipamentos usados passam por um processo de higienização para que possam ser emprestados para outro cliente. Há um funcionário responsável pela higienização de cada tipo de equipamento. 

Tenha em mente que a sua solução, além de observar as regras descritas acima, deverá evitar que ocorram deadlocks e starvation sem limitar a concorrência entre threads.

O código-fonte fornecido deverá ser utilizado como base para a implementação da sua solução. Não será permitido remover as definições existentes, porém você poderá definir novas funções, variáveis e classes, se necessário. O código-fonte já inclui comandos para imprimir na tela as etapas da execução do programa. Você deve criar as variáveis globais necessárias para controlar o uso dos equipamentos e o acesso às atrações, e proteger estas variáveis globais de condições de corrida.

# Estrutura do Projeto
O código base contém três arquivos que você deve complementar para atender aos requisitos do trabalho:

init.py: Contém as variáveis globais que configuram a simulação. Essas variáveis são configuradas durante o início do programa e devem ser consideradas constantes durante a execução. Você pode ter acesso a essas informações através da importação import init e utilizar da seguinte forma: init.nome_var. Neste arquivo também devem ser adicionadas outras declarações necessárias para que seu código funcione conforme especificado. Além disso, nesse arquivo você deve instanciar as threads que representam os funcionários e os clientes do parque.

- cliente.py: É a classe que implementa o comportamento dos clientes. O método run() do cliente chama os outros métodos que precisam ter sua implementação concluída de modo que o cliente se comporte de acordo com a especificação.

- funcionario.py: Esse arquivo contém a classe que deve implementar o comportamento dos funcionários que fazem o empréstimo e devolução dos equipamentos e os higienizam. A função run() já está definida e seu código chama os demais métodos que devem executar o comportamento esperado. 

- equipamentos.py: Essa classe representa um conjunto de equipamentos de um determinado tipo. Implemente aqui o controle de acesso aos equipamentos.

- atracoes.py: Classe que representa as atrações do parque. Adicione a essa classe o controle de acesso às atrações.

Observação: É importante que vocês comentem o código, descrevendo qual o objetivo almejado em cada método e/ou conjunto de operações. Isso auxiliará na correção dos trabalhos e permitirá um melhor entendimento do próprio código pela dupla, algo extremamente útil quando desenvolvemos código em conjunto com outras pessoas. O código fornecido já imprime várias mensagens na tela, mas vocês podem imprimir outras informações durante o desenvolvimento que considerem úteis para acompanhar passo a passo a execução do programa.

# Execução do Programa
Você deve utilizar obrigatoriamente a versão 3 do python (python3) para executar o trabalho. A interface para configurar a simulação já está definida, deixando apenas a implementação dos aspectos de concorrência em aberto. Para executar, basta rodar a seguinte linha de código no terminal:

python3 init.py

O código base aceita alguns argumentos que modificam a velocidade de execução do programa. Para consultá-las, execute o comando:

python3 init.py --help

#Entrega do Trabalho
O trabalho deverá ser realizado em duplas e o número de grupos está limitado em 25. Defina sua dupla conversando com seus colegas antecipadamente e, somente após a definição da dupla, crie um grupo no Github Classroom. A escolha dos grupos, o desenvolvimento e a entrega do trabalho deverão ser feitos via Github Classroom. Um pequeno guia sobre o Github Classroom e o Git foi disponibilizado no Moodle. Leia atentamente o guia antes de fazer a escolha dos grupos e começar a atividade. O último commit realizado na branch master do repositório criado via Github Classroom até a data limite para submissão (09/03/2022 às 23:59:59) será considerado para fins de avaliação.

# Relatório
Além do código-fonte, você deverá disponibilizar no repositório um documento no formato PDF contendo as respostas para as seguintes perguntas:

1. Descreva as estratégias que foram utilizadas na sua implementação para controlar o acesso aos seguintes recursos:
a) pista de patinação;
b) teleférico;
c) pista de esqui/snowboard;
d) pistas de trenó/bobsled;
e) patins;
f) pranchas de snowboard;
g) esquis;
h) trenós;
i) bobsleds.

2. Descreva se existe alguma possibilidade de deadlock ou starvation na execução da simulação.

3. Suponha que, no lugar de threads, fossem usados processos para implementar os clientes e funcionários. Haveria algum ganho no desempenho do programa? 
