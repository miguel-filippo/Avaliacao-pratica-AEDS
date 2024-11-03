#ifndef DOUBLESTACK_H
#define DOUBLESTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int head;
    int tail;
    int* data;
    int size;
}DoubleStack;

DoubleStack* createDoubleStack(int size);

void pushHead(DoubleStack* stack, int value);

void pushTail(DoubleStack* stack, int value);

int popHead(DoubleStack* stack);

int popTail(DoubleStack* stack);

int isFull(DoubleStack* stack);

int isEmpty(DoubleStack* stack);

void printDoubleStack(DoubleStack* stack);

void freeDoubleStack(DoubleStack* stack);

#endif // DOUBLESTACK_H
