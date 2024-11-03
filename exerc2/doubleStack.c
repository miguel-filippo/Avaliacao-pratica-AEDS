#include "doubleStack.h"

DoubleStack* createDoubleStack(int size){
    DoubleStack* stack = (DoubleStack*)malloc(sizeof(DoubleStack));
    stack->head = 0;
    stack->tail = size - 1;
    stack->data = (int*)malloc(size*sizeof(int));
    stack->size = size;
    return stack;
}

void pushHead(DoubleStack* stack, int value){
    if (!((stack->tail - stack->head) < 0)){
        stack->data[stack->head++] = value;
    }
    else{
        printf("Erro de indice: A pilha esta cheia, nao foi possivel adicionar %d na base\n", value);
    }
}

void pushTail(DoubleStack* stack, int value){
    if (!((stack->tail - stack->head) < 0)){
        stack->data[stack->tail--] = value;
    }
    else{
        printf("Erro de indice: A pilha esta cheia, nao foi possivel adicionar %d no topo\n", value);
    }
}

int popHead(DoubleStack* stack){
    if (stack->head > 0){
        return stack->data[--stack->head];
    }
    else{
        printf("Erro de indice: A pilha esta vazia, nao foi possivel remover da base\n");
        return -1;
    }
}

int popTail(DoubleStack* stack){
    if (stack->tail < stack->size - 1){
        return stack->data[++stack->tail];
    }
    else{
        printf("Erro de indice: A pilha esta vazia, nao foi possivel remover do topo\n");
        return -1;
    }
}

int isFull(DoubleStack* stack){
    return (stack->tail - stack->head) < 0;
}

int isEmpty(DoubleStack* stack){
    return stack->head == 0 && stack->tail == stack->size - 1;
}

void printDoubleStack(DoubleStack* stack){
    printf("PilhaDupla: ");
    for (int i = 0; i < stack->size; i++){
        if (i < stack->head || i > stack->tail){
            printf("%d ", stack->data[i]);
        }
    }
    printf("\n");
}

void freeDoubleStack(DoubleStack* stack){
    free(stack->data);
    free(stack);
}
