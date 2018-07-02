O algoritmo deverá retornar os valores das variáveis básicas e não básicas e o valor da função objetivo.
O algoritmo deverá receber uma matriz A contendo os coeficientes das restrições, um vetor b contendo
os valores das demandas e um vetor c contendo os custos das variáveis na função objetivo, além das
variáveis básicas iniciais. A entrada dos dados deve ser feita através da leitura de um arquivo .txt no
formato:

1 2 3 4 5 1 0 0
6 7 8 9 1 0 1 0
1 7 2 4 5 0 0 1

100 60 20

10 30 20 45 62 0 0 0

6 7 8

Sendo o primeiro conjunto de dados os valores da matriz A, o segundo o vetor de demandas b e o
terceiro o vetor de custos c. O último conjunto de valores indica quem são as variáveis básicas (x6, x7 e
x
8).
O tamanho do conjunto de dados é variável, ou seja, o número de linhas e colunas da matriz A poderá
variar indefinidamente, de acordo com o problema tratado pelo usuário, bem como a quantidade de
dados dos demais vetores.
O aluno deverá entregar o código impresso. Na data da entrega, os alunos deverão também apresentá-lo
ao professor no laboratório de programação II, bloco IV. Portanto, antes da data de entrega, os alunos
deverão ir até o laboratório e testar o algoritmo implementado, para que, durante a aula, não haja
nenhum problema. Esta apresentação será apenas para o professor que irá conversar individualmente
com cada aluno sobre o algoritmo implementado.# simplex_c-
