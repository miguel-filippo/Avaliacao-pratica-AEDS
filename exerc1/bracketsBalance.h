#ifndef BRACKETSBALANCE_H
#define BRACKETSBALANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================== PARTE DA PILHA ==================
// Definição do nó da stack
typedef struct Node {
    char data;
    struct Node* next; // Usando struct antes de Node* porque o alias ainda não foi criado (está na linha abaixo)
} Node;

// Definição da stack dinâmica
typedef struct {
    Node* top;
    int tamanho;
} Stack;

// Função para criar uma nova stack
Stack* createStack();

// Função para criar um novo nó
Node* createNode(char data);

// Função para verificar se a stack está vazia
int isStackEmpty(Stack* stack);

// Função para adicionar um elemento no topo da stack
void push(Stack* stack, char data);

// Função para remover e retornar o elemento do topo da stack
char pop(Stack* stack);

// Função para retornar a quantidade de elementos da stack
int size(Stack* stack);

// Função para retornar o topo da stack sem remover
char peekStack(Stack* stack);

// Função para limpar a stack
void clearStack(Stack* stack);

// Função para imprimir a stack
void printStack(Stack* stack);
// ====================================================

// ================== PARTE DA FILA ===================
// Definição da fila dinâmica
typedef struct {
    char* data;
    int front;
    int rear;
    int capacity;
    int size;
} Queue;

// Função para criar uma nova fila
Queue* createQueue();

// Função para adicionar um elemento no final da fila
void enqueue(Queue* queue, char data);

// Função para remover e retornar o elemento do início da fila
char dequeue(Queue* queue);

// Função para retornar o início da fila sem remover
char peekQueue(Queue* queue);

// Função para verificar se a fila está vazia
int isQueueEmpty(Queue* queue);

// Função para imprimir a fila
void printQueue(Queue* queue);

// Função para limpar a fila
void clearQueue(Queue* queue);

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ATENÇÃO, A FUNÇÃO ABAIXO É APENAS PARA FACILITAR O TESTES NA MAIN()
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

// Converte string para fila
Queue* stringToQueue(char* string);
// ====================================================

#endif // BRACKETSBALANCE_H