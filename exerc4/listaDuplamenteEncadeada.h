#ifndef LISTADUPLAMENTEENCADEADA_H_INCLUDED
#define LISTADUPLAMENTEENCADEADA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da lista duplamente ligada
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Estrutura da lista duplamente ligada
typedef struct Lista {
    Node* head;
    Node* tail;
    int size;
    int ordenado;
} Lista;

// Função para ordenar a lista
void ordenar(Lista* lista);

// Função para criar um novo nó
Node* criarNode(int data);

// Função para inicializar uma lista duplamente ligada
Lista* criarLista();

// Função para adicionar um elemento no início da lista
void insertHead(Lista* lista, int data);

// Função para adicionar um elemento no final da lista
void insertTail(Lista* lista, int data);

// Função para buscar linearmente um elemento na lista
int buscaLinear(Lista* lista, int data);

// Função para buscar de maneira binária e recursiva um elemento na lista
Node* buscaBinaria(Node* left, Node* right, int target);

// Função para buscar um elemento na lista
int busca(Lista* lista, int data);

// Função para inserir um elemento em uma posição específica da lista
void insert(Lista* lista, int data, int position);

// Função para remover um elemento da lista
void removeHead(Lista* lista);

// Função para remover um elemento da lista
void removeTail(Lista* lista);

// Função para remover um elemento da lista
void removeNode(Lista* lista, int position);

// Função para limpar a lista
void clear(Lista* lista);

// Função para verificar se a lista está vazia
int isEmpty(Lista* lista);

// Função para retornar o tamanho da lista
int getSize(Lista* lista);

// Função para imprimir a lista
void printLista(Lista* lista);

#endif // LISTADUPLAMENTEENCADEADA_H_INCLUDED
