# Aula 01 - Apresentação e Recursividade

## 1
```
Implemente uma função recursiva para calcular a potência a^n, supondo que tanto
a quanto n sejam números inteiros positivos.
```
## 2
```
Implementar função de fatorial recursiva
```
## 3
```
Implementar função que calcula fibonnaci até n recursiva
```
## 4
```
Dada um vetor de números inteiros positivos, descreva funções recursivas para :
a) Fazer a busca linear de um elemento no vetor;
b) Encontrar o menor elemento no vetor;
c) Fazer a soma dos elementos no vetor;
d) Calcular a média aritmética dos elementos no vetor;
```
## 5
```
Escreva uma função recursiva que calcula o produto de a * b, em que a e b são
inteiros maiores que zero. considere que o produto pode ser definido como a
somado a si mesmo b vezes, usando uma definição recursiva temos
a * b = a se b = 1
a * b = a * ( b – 1 ) + a se b > 1
```
# Aula 03 - Enumeração
## 1
```
Escreva uma função booleana na linguagem C que receba duas sequências e
decida se uma sequência r[1..j] é lexicograficamente menor que uma
sequência s[1..k].
```
## 2
```
Escreva uma função na linguagem C que receba duas sequências e retorna:
1 se uma sequência r[1..j] é lexicograficamente menor que uma sequência s[1..k].
0 se uma sequência r[1..j] é lexicograficamente igual que uma sequência s[1..k].
-1 se uma sequência r[1..j] é lexicograficamente maior que uma sequência s[1..k].
```
## 3
```
Escreva uma função booleana na linguagem C que receba duas sequências e
decida se uma sequência s[1..k] é uma subsequência da sequência a[1..n].
```
## 4
```
Escreva uma função booleana na linguagem C que receba duas sequências e
decida se uma sequência s[i..j] é um segmento da sequência a[1..n].
```
## 5
```
Dada uma sequência de números inteiros com n elementos, determinar quantas
subsequências de números iguais consecutivos compõem essa sequência.
Exemplos:
a) A sequência 5 2 2 3 4 4 4 4 4 1 1, é composta por 5 subsequências:
(5), (2,2), (3), (4, 4, 4, 4, 4), (1,1);
b) A sequência: 3 3 -1 -1 -1 12 12 12 3 3 é composta por 4 subsequências:
(3,3), (-1, -1, -1), (12, 12, 12), (3,3);
Escreva uma função na linguagem C que determina a quantidade de
subsequências em sequência dada.
Qual é complexidade da sua função ?
```

## 6
```
Dada uma sequência de números inteiros com n elementos, faça uma função na
linguagem C para determinar o comprimento de um segmento crescente de
comprimento máximo.
Exemplos:
Na sequência 5 10 3 2 4 7 9 8 5 o comprimento do segmento crescente
máximo é 4 (2, 4, 7, 9).
Na sequência 10 8 7 5 2 o comprimento do segmento crescente máximo é 1.
Qual é complexidade da sua função ?
```

## 7
```
Dada uma sequência a[1..n] de números inteiros, escreva um programa na
linguagem C que verifica se existem dois segmentos consecutivos iguais na
sequência, isto é, se existem i e m tais que:
a[i] a[i+1] ... a[i+m-1] = a[i+m] a[i+m+1] ... a[i+2m-1]
Imprima, caso existam, os valores de i e m.
Exemplo: Na sequência 7 9 5 4 5 4 8 6 existem i=3 e m=2
Qual é complexidade da sua função ?
```
## 8
```
Dada uma sequência de números inteiros com n elementos, escreva uma função
na linguagem C determinar um segmento de soma máxima.
Exemplo: Na sequência 5 2 -2 -7 3 14 10 -3 9 -6 4 1, a soma do
segmento é 33.
Qual é complexidade da sua função ?
```
## 9
```
Dados dois números naturais m e n e duas sequências ordenadas sem números
repetidos com m e n números inteiros, obter uma única sequência ordenada
contendo todos os elementos das sequências originais.
Qual é complexidade da sua função ?
```

# Aula 04 - Algoritmos força bruta


## 1
```

Enumerar todas as sequências possíveis de 3 dígitos, por exemplo se tivermos
os dígitos 1, 2 e 3 teríamos como resultado:
1 1 1, 1 1 2, 1 1 3, 1 2 1, 1 2 2, 1 2 3, 1 3 1, 1 3 2, 1 3 3,
2 1 1, 2 1 2, 2 1 3, 2 2 1, 2 2 2, 2 2 3, 2 3 1, 2 3 2, 2 3 3,
3 1 1, 3 1 2, 3 1 3, 3 2 1, 3 2 2, 3 2 3, 3 3 1, 3 3 2, 3 3 3

Implemente na linguagem C o algoritmo sequencias(a[1..n], i, s[1..n]),
lembre-se que na solução os vetores são indexados a partir de 1 e que n é o
índice do último elemento no vetor. Você deve fazer ajuste para que o
algoritmo funcione em C.

Para resolver o problema poderíamos escrever o algoritmo sequencias(a,i,s):
algoritmo sequencias(a[1..n], i, s[1..n])
entrada: o vetor a[1..n] com os n dígitos para gerar as sequencias,
inteiro i para controlar o nível na árvore de recursão, vetor
solução s[1..n].
saída: a impressão de todas as sequências de n elementos geradas em
s[1..n].

início
    se i > n então # temos uma sequência completa em s[1..n]
        imprima(s[1..n])
senão
    para j de 1 até n faça
        s[i] <-- a[j]
        sequencias(s,i+1,a
```


## 2
```
Suponha que agora queremos gerar todas as sequências possíveis de tamanho
3 utilizando a sequencia 1 2 3 4. Neste caso, temos que definir o vetor solução
como s[1..m], com m=3 e vetor a[1..n] com n=4.
a) Modifique o algoritmo visto para resolva agora o problema proposto.
b) Qual seria a complexidade do algoritmo ?
```

## 3
```
Dado a sequência a[1..n] escreva uma função em C que gera todas as
subsequências da sequencia a[1..n].
Exemplo: para sequencia 1 2 3 teríamos as seguintes subsequências:
1, 2, 3, 1 2, 1 3, 2 3, 1 2 3
Note que a partir da sequência a[1..n] podemos ter 2
n – 1 subsequências
distintas.
```

## Desafio
```
Uma permutação de uma sequência com números distintos é qualquer rearranjo
dos termos dessa sequência em que cada elemento da sequência apareça somente
uma vez. Considere a sequência 1 2 3, sabemos que há exatamente 6 (3!)
permutações para a sequencia:
1 2 3, 1 3 2, 2 1 3, 2 2 3, 3 1 2, 3 2 1
Problema: Dado uma sequência com n números distintos enumerar as
permutações n! permutações da sequencia
```


# Aula 05 - Backtracking

# 1
```
Escreva um algoritmo que apresenta todos os números binários de tamanho n,
se for informado ao seu algoritmo n = 3, teríamos:
000, 001, 010, 011, 100, 101, 110, 111.
```
```
Poderíamos ter utilizado o algoritmo de gerar sequencias para tamanho de s!=a, passando n como um vetor acoplado na funcao (ex: a = {0,1}), porém, esse algoritmo utiliza melhor do backtracking para a resolução

Execução desse exercício para melhor entendimento:
Chamada para n = 2
Stack:
0: s={LIXO,LIXO}

1 call
	i = 0
	s[0] = 0
	s = {0,LIXO}
	call(2nd)
	//
	s[0] = 1
	s = {1,1}
	call(5th)
2 call
	i = 1
	s[1] = 0
	s = {0,0}
	call(3rd)
	//
	s[1] = 1
	s = {0,1}
	call(4th)
3 call
	i = 2
	print(0,0)
4 call
	print(0,1)
5 call
	i = 1
	s[i] = 0
	s = {1,0}
	call(6th)
	//
	s[1] = 1
	s = {1,1}
	call(7th)
6 call
    i = 2
	print(1,0)
7 call
    i = 2
	print(1,1)
```
# 2

```
Considere uma partida de futebol entre duas equipes AxB, cujo o placar final é
MxN, em que M e N são números de gols marcados por A e B, respectivamente.
Escreva um algoritmo utilizando Backtracking que imprima todas as possíveis
sucessões de gols marcadas. Por exemplo, para um placar 3x1, temos: AAAB.
AABA, ABAA, BAAA.
```

