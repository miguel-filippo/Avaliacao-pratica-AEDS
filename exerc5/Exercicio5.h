#ifndef Exercicio5_H_INCLUDED
#define Exercicio5_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* A matriz é composta por listas ligadas, que podem ser percorridas através de suas colunhas ou através de suas linhas. 
Logo, a matriz contem duas listas ligadas que nao contem valores (uma para as linhas e outra para as colunas), nas quais, cada nó, armazena 
um ponteiro para a lista ligada da linha/coluna da matriz que contém os valores (E também um ponteiro para a próxima linha/coluna válida). 
Assim como foi mostrado nos slides do curso para Matrizes esparsas implementadas com "Lista ligada cruzada".
Logo, para essa implementação, cada nó comtem um atributo chamado typeOfNode, que indica se esse nó faz parte da lista ligada com valores ou 
da lista ligada sem os valores (apenas com os ponteiros para as listas ligadas das linhas/colunas com os valores).
* typeOfNode = 1 ----> Nó que contem valores da matriz.
  typeOfNode = 0 ----> Nó que contem os ponteiros para as listas ligadas com os valores.
*/

// Estrutura de um nó da lista que vai compor
typedef struct Node {
    int typeOfNode;  
    int data; // valor armazenado
    int line; 
    int column; 
    struct Node* nextLine;  // ponteiro para a proxima lista de linhas ou para o próximo nó da mesma coluna
    struct Node* nextColumn;  // // ponteiro para a proxima lista de colunas ou para o próximo nó da mesma linha 

} Node;

// Estrutura da lista duplamente ligada
typedef struct Matriz {
    Node* HeadListOfLines; // ponteiro que contém a Head da Lista de Listas para cada linha
    Node* HeadListOfCol; // ponteiro que contém a Head da Lista de Listas para cada coluna 
    int LinhaMax;
    int ColMax;
    int size;
} Matriz;

Node* criarNode(int data, int typeOfNode);

Matriz* criarMatriz();

int getSize(Matriz* matriz);

int isEmpty(Matriz* matriz);

void inserir(Matriz* matriz, int line, int col, int valor);

//void imprimir(Matriz* matriz);
void imprimir(Matriz* matriz);

void imprimir_apenas_valores(Matriz* matriz);

int buscar(Matriz* matriz, int line, int col);

int remover(Matriz* matriz,int line, int col);

float calculaEsparsidade(Matriz* matriz);

Matriz* somar(Matriz* matriz1, Matriz* matriz2);

int somaInterna(Matriz* matriz);

#endif // Exercicio5_H_INCLUDED