#ifndef LNSE_H
#define LNSE_H

typedef struct {
    int capacity;
    int *data;
    int front;
    int rear;
    int size;
} Fila;

typedef struct{
    int value;
    int next;
} Register;

typedef struct {
    int head;
    int tail;
    Register *registers;
    Fila *freePositions;
} LNSE;

// =================== Funções da Fila ===================
// Função para inicializar a fila
Fila* criarFila(int capacity);

// Função para adicionar um elemento na fila
void enqueue(Fila *fila, int data);

// Função para remover um elemento da fila
int dequeue(Fila *fila);

// Função para obter o tamanho da fila
int getSize(Fila *fila);

// Função para verificar se a fila está vazia
int isEmpty(Fila *fila);

// Função para verificar se a fila está cheia
int isFull(Fila *fila);

// Função para obter o primeiro elemento da fila
int getFront(Fila *fila);

// Função para limpar a fila
void clear(Fila *fila);

// Função para imprimir a fila
void imprimir(Fila *fila);
// =======================================================

// =================== Funções da LNSE ===================
// Função para inicializar a LNSE
LNSE* criarLNSE(int capacity);

// Função para adicionar um elemento na LNSE
char* inserirLNSE(LNSE *lnse, int x, int i);

// Função para remover um elemento da LNSE
int removerLNSE(LNSE *lnse, int i);

// Função para obter o tamanho da LNSE
int sizeLNSE(LNSE *lnse);

// Função para buscar um elemento na LNSE
int buscarLNSE(LNSE *lnse, int target);

// Função para limpar a LNSE
void clearLNSE(LNSE *lnse);

// Função para imprimir a LNSE
void imprimirLNSE(LNSE *lnse);

// Função para liberar memória da LNSE
void freeLNSE(LNSE *lnse);
// =======================================================

#endif
