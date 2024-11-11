#include <stdio.h>
#include <stdlib.h>

#include "LNSE.h"

// =================== Funções da Fila ===================
// Função para inicializar a fila
Fila* criarFila(int capacity) {

    Fila *fila = (Fila *)malloc(sizeof(Fila));

    fila->capacity = capacity;

    // cria o vetor que guardara os dados de maneira dinamica
    fila->data = (int *)malloc(capacity * sizeof(int));

    fila->front = -1;
    fila->rear = -1;
    fila->size = 0;

    return fila;
}

// Função para obter o tamanho da fila
int getSize(Fila *fila) {
    return fila->size;

    // Outras maneiras de fazer a mesma coisa
    // --------------------------------------
    // return fila->size == fila->capacity;

    // if (fila->size == fila->capacity){
    //    return 1;
    // }
    // else{
    //    return 0;
    // }
}

// Função para verificar se a fila está vazia
int isEmpty(Fila *fila) {
    return fila->size == 0;
}

// Função para verificar se a fila está cheia
int isFull(Fila *fila) {
    return fila->size == fila->capacity;
}

// Função para adicionar um elemento na fila
void enqueue(Fila *fila, int data) {
    if (fila->size >= fila->capacity) {
        printf("Erro. Overflow!");
        return;
    }

    if (fila->front == -1) {
        fila->front = 0;
        fila->rear = 0;
    } else if (fila->rear == fila->capacity - 1) {
        fila->rear = 0;
    } else {
        fila->rear = fila->rear + 1;
    }

    fila->data[fila->rear] = data;
    fila->size += 1;
}

// Função para remover um elemento da fila
int dequeue(Fila *fila) {
    if (fila->size == 0) {
        printf("Erro. Underflow!");
        return -1;
    }

    int temp = fila->data[fila->front];

    if (fila->size == 1) {
        fila->front = -1;
        fila->rear = -1;
    } else if (fila->front == fila->capacity - 1) {
        fila->front = 0;
    } else {
        fila->front = fila->front + 1;
    }

    fila->size -= 1;
    return temp;
}

// Função para obter o primeiro elemento da fila
int getFront(Fila *fila) {
    if (isEmpty(fila)) {
        printf("Fila vazia\n");
        return -1;
    }

    return fila->data[fila->front];
}

// Função para limpar a fila
void clear(Fila *fila) {
    fila->front = -1;
    fila->rear = -1;
    fila->size = 0;
}

// Função para imprimir a fila
void imprimir(Fila *fila) {

    if (isEmpty(fila)) {
        printf("\n[ ]\n");
        return;
    }

    Fila* auxFila = criarFila(fila->capacity);

    printf("\n[");
    // Seguindo as regras da fila, a unica forma de
    // acessar todos os seus valores, eh destruindo ela
    while( isEmpty(fila)!=1 ){
        int front = dequeue(fila);

        // Salva na fila auxiliar para recuperar depois
        enqueue(auxFila, front);

        printf(" %d", front);
    }
    printf(" ]\n");

    // Recupera a fila
    while( isEmpty(auxFila)!=1 ){
        int auxValor = dequeue(auxFila);

        // Recupera o valor na fila principal
        enqueue(fila, auxValor);
    }

    free(auxFila);
}
// =======================================================

// =================== Funções da LNSE ===================
// Função para inicializar a LNSE
LNSE* criarLNSE(int capacity) {
    LNSE *lnse = (LNSE *)malloc(sizeof(LNSE));

    lnse->head = -1;
    lnse->tail = -1;
    lnse->registers = (Register *)malloc(capacity * sizeof(Register));

    for (int i = 0; i < capacity; i++) {
        lnse->registers[i].value = -1;
        lnse->registers[i].next = -1;
    }

    lnse->freePositions = criarFila(capacity);

    // Inicializa a fila de posições livres
    for (int i = 0; i < capacity; i++) {
        enqueue(lnse->freePositions, i);
    }

    return lnse;
}

int sizeLNSE(LNSE *lnse) {
    int size = 0;
    int pos = lnse->head;

    while (pos != -1) {
        size++;
        pos = lnse->registers[pos].next;
    }

    return size;
}

// Função para adicionar um elemento na LNSE
char* inserirLNSE(LNSE *lnse, int x, int i) {
    if (isEmpty(lnse->freePositions)) {
        return "LNSE Error: A lista está cheia.";
    } else if (i < 0 || i > sizeLNSE(lnse)) {
        return "LNSE Error: index fora do limite.";
    }

    int pos = dequeue(lnse->freePositions);

    // Salva o VALOR no vetor real.
    lnse->registers[pos].value = x;

    // Lida com a lógica de encadeamento da LNSE
    if (lnse->head == -1) {
        lnse->head = pos;
        lnse->tail = pos;
    } else {
        if (i == 0) {
            lnse->registers[pos].next = lnse->head;
            lnse->head = pos;
        } else if (i == sizeLNSE(lnse)) {
            lnse->registers[lnse->tail].next = pos;
            lnse->tail = pos;
        } else {
            int temp = lnse->head;
            for (int j = 0; j < i - 1; j++) {
                temp = lnse->registers[temp].next;
            }

            lnse->registers[pos].next = lnse->registers[temp].next;
            lnse->registers[temp].next = pos;
        }
    }

    return "Elemento inserido com sucesso.";
}

// Função para remover um elemento da LNSE
int removerLNSE(LNSE *lnse, int i) {
    if (lnse->head == -1) {
        printf("LNSE Error: Underflow!\n");
        return -1;
    } else if (i < 0 || i >= sizeLNSE(lnse)) {
        printf("LNSE Error: index out of boundaries.\n");
        return -1;
    }

    if (i == 0) {
        int value = lnse->registers[lnse->head].value;
        lnse->head = lnse->registers[lnse->head].next;

        enqueue(lnse->freePositions, lnse->head);

        return value;
    }

    int tempPos = lnse->head;

    for (int j = 0 ; j < i - 1; j++) {
        tempPos = lnse->registers[tempPos].next;
    }

    int value = lnse->registers[lnse->registers[tempPos].next].value;

    lnse->registers[tempPos].next = lnse->registers[lnse->registers[tempPos].next].next;

    enqueue(lnse->freePositions, lnse->registers[tempPos].next);

    return value;
}

// Função para imprimir a LNSE
void imprimirLNSE(LNSE *lnse) {
    int pos = lnse->head;

    printf("[ ");
    while (pos != -1) {
        printf("%d ", lnse->registers[pos].value);
        pos = lnse->registers[pos].next;
    }
    printf("]\n");
}

// Função para buscar um elemento na LNSE
int buscarLNSE(LNSE *lnse, int target) {
    int pos = lnse->head;

    while (pos != -1) {
        if (lnse->registers[pos].value == target) {
            return pos;
        }

        pos = lnse->registers[pos].next;
    }

    return -1;
}

// Função para limpar a LNSE
void clearLNSE(LNSE *lnse) {
    lnse->head = -1;
    lnse->tail = -1;

    // Define os valores dos registradores para o estado padrão
    for (int i = 0; i < lnse->freePositions->capacity; i++) {
        lnse->registers[i].value = -1;
        lnse->registers[i].next = -1;
    }

    // Limpa a fila de posições livres preenchendo-a novamente
    for (int i = 0; i < lnse->freePositions->capacity  ; i++) {
        enqueue(lnse->freePositions, i);
    }
}

// Função para liberar a memória alocada
void freeLNSE(LNSE *lnse) {
    free(lnse->registers);
    free(lnse->freePositions);
    free(lnse);
}
